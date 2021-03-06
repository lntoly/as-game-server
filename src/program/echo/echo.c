#include <event2/buffer.h>

#include "module/event_util.h"
#include "net_manager.h"
#include "module/log.h"

static struct event_base* base = NULL;

static void echo_read_cb(struct bufferevent *bev, void* args)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	struct evbuffer *output = bufferevent_get_output(bev);
	evbuffer_add_buffer(output, input);
}

static void echo_event_cb(struct bufferevent *bev, short events, void *args)
{
	if (events & BEV_EVENT_ERROR) perror("Error from bufferevent");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
		evutil_socket_t fd = bufferevent_getfd(bev);
		net_del_connect(fd);
		bufferevent_free(bev);
	}
}

static void accept_conn_cb(struct evconnlistener *listener, evutil_socket_t fd,
		struct sockaddr *address, int socklen, void* args)
{
    struct event_base* base = evconnlistener_get_base(listener);
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

    bufferevent_setcb(bev, echo_read_cb, NULL, echo_event_cb, NULL);

    bufferevent_enable(bev, EV_READ|EV_WRITE);

    net_add_connect(fd, bev);
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
        struct event_base *base = evconnlistener_get_base(listener);
        int err = EVUTIL_SOCKET_ERROR();
        fprintf(stderr, "Got an error %d (%s) on the listener. "
                "Shutting down.\n", err, evutil_socket_error_to_string(err));

        event_base_loopexit(base, NULL);
}

void init_echo(int argc, char* argv[])
{
	if (argc < 3) {
		log_print("echo server:connect to bad ip:port");
		exit(1);
	}

	init_net_manager();
	base = init_event();

	char* ip = argv[2];

	struct bufferevent* con = event_connect(base, ip);
	if (con == NULL) {
		log_debug("connect to %s fail", ip);
		exit(1);
	}
	else log_debug("connect to %s ok", ip);

	bufferevent_setcb(con, echo_read_cb, NULL, echo_event_cb, NULL);
	bufferevent_enable(con, EV_READ|EV_WRITE);

	event_base_dispatch(base);
}

void close_echo()
{
	event_base_free(base);
}
