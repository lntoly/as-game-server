/*
 * event_util.h
 *
 *  Created on: 2012-7-8
 *      Author: AzureSky
 */

#ifndef EVENT_UTIL_H_
#define EVENT_UTIL_H_

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

struct event_base* init_event();

struct evconnlistener* event_listener(struct event_base*, const char*, int,
		evconnlistener_cb, void*, evconnlistener_errorcb);

struct bufferevent* event_connect(struct event_base*, const char*, int);

#endif /* EVENT_UTIL_H_ */
