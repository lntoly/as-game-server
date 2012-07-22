/*
 * test_server.c
 *
 *  Created on: 2012-7-22
 *      Author: AzureSky
 */

#include <event2/buffer.h>

#include "module/event_util.h"
#include "module/log.h"
#include "test_server.h"

static struct event_base* base = NULL;

static size_t total_size = 0;
static size_t last_size = 0;

static void timeout_cb(evutil_socket_t fd, short event, void *arg)
{
	size_t diff = total_size - last_size;
	last_size = total_size;
	diff /= 1024;
	log_print(" total %d kb, %d kb/s", diff, diff/5);

	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = 5;

	struct event* timeout = evtimer_new(base, timeout_cb, NULL);
	evtimer_add(timeout, &tv);
}

void close_test_server()
{
	event_base_free(base);
}

static void echo_read_cb(struct bufferevent *bev, void* args)
{
	struct evbuffer *input = bufferevent_get_input(bev);
	total_size += evbuffer_get_length(input);

	struct evbuffer *output = bufferevent_get_output(bev);
	evbuffer_add_buffer(output, input);
}

static void echo_event_cb(struct bufferevent *bev, short events, void *args)
{
	if (events & BEV_EVENT_ERROR) perror("Error from bufferevent");
	if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
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

    struct evbuffer *output = bufferevent_get_output(bev);

    for (int i = 0; i < 100; ++i) {
    	evbuffer_add_printf(output, "zhejiushidiyicideceshi");
    }
}

static void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
        struct event_base *base = evconnlistener_get_base(listener);
        int err = EVUTIL_SOCKET_ERROR();
        fprintf(stderr, "Got an error %d (%s) on the listener. "
                "Shutting down.\n", err, evutil_socket_error_to_string(err));

        event_base_loopexit(base, NULL);
}

void init_test_server(int argc, char* argv[])
{
	base = init_event();

	char* ip = "127.0.0.1";
	int port = 3000;
	if (event_listener(base, ip, port, accept_conn_cb, NULL, accept_error_cb) == NULL) {
		log_debug("listen fail %s:%d", ip, port);
		exit(1);
	}
	else {
		log_debug("listening %s:%d", ip, port);
	}

	struct timeval tv;
	evutil_timerclear(&tv);
	tv.tv_sec = 5;

	struct event* timeout = evtimer_new(base, timeout_cb, NULL);
	evtimer_add(timeout, &tv);

	event_base_dispatch(base);
}
