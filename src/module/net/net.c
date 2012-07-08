#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include "net.h"
#include "net_manager.h"

#include "module/log/log.h"

struct event_base* init_net()
{
	return event_base_new();
}

struct evconnlistener* net_listener(struct event_base* base, const char* address, int port,
		evconnlistener_cb accept_cb, void* args,
		evconnlistener_errorcb errorcb)
{
	if (base == NULL) return NULL;
	if (accept_cb == NULL || errorcb == NULL) return NULL;

	struct sockaddr_storage sin;
	int outlen = sizeof(sin);
	memset(&sin, 0, outlen);

	if (evutil_parse_sockaddr_port(address, (struct sockaddr*)&sin, &outlen) != 0) {
		return NULL;
	}

	struct sockaddr_in* tmp = (struct sockaddr_in*)&sin;
	tmp->sin_port = htons(port);

	struct evconnlistener* listener = evconnlistener_new_bind(base, accept_cb, args,
			LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
			-1, (struct sockaddr*)&sin, outlen);

	if (listener == NULL) return NULL;

	evconnlistener_set_error_cb(listener, errorcb);

	return listener;
}

struct bufferevent* net_connect(struct event_base* base, const char* address, int port)
{
	if (base == NULL) return NULL;

	struct sockaddr_storage sin;
	int outlen = sizeof(sin);
	memset(&sin, 0, outlen);

	if (evutil_parse_sockaddr_port(address, (struct sockaddr*)&sin, &outlen) != 0) {
		return NULL;
	}
	struct sockaddr_in* tmp = (struct sockaddr_in*)&sin;
	tmp->sin_port = htons(port);

	struct bufferevent* buf = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	if (buf == NULL) return NULL;

	if (bufferevent_socket_connect(buf, (struct sockaddr*)&sin, outlen)) {
		bufferevent_free(buf);
		return NULL;
	}
	else return buf;
}
