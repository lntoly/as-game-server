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
		evconnlistener_cb accpet_cb, evconnlistener_errorcb errorcb)
{
	if (base == NULL) return NULL;
	if (accpet_cb == NULL || errorcb == NULL) return NULL;

	struct sockaddr_storage sin;
	int outlen = sizeof(sin);
	memset(&sin, 0, outlen);

	if (evutil_parse_sockaddr_port(address, (struct sockaddr*)&sin, &outlen) != 0) {
		log_debug("net_listener fail, ip:%s", address);
		return NULL;
	}

	struct sockaddr_in* tmp = (struct sockaddr_in*)&sin;
	tmp->sin_port = htons(port);

	struct evconnlistener* listener = evconnlistener_new_bind(base, accpet_cb, NULL,
			LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,
			-1, (struct sockaddr*)&sin, sizeof(sin));

	if (listener == NULL) return NULL;

	evconnlistener_set_error_cb(listener, errorcb);

	return listener;
}
