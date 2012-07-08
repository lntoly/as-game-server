#include <event2/bufferevent.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include "net.h"
#include "net_manager.h"

static struct evconnlistener* listener = NULL;

void init_net(struct event_base* base)
{
	init_net_manager();
}

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

int net_listener(struct event_base* base, const char* address, int port)
{
	if (base == NULL) return 0;

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(3000);

	listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
			LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
			-1, (struct sockaddr*)&sin, sizeof(sin));

	if (listener == NULL) return 0;

	evconnlistener_set_error_cb(listener, accept_error_cb);

	return 1;
}
