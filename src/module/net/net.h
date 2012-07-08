/*
 * net.h
 *
 *  Created on: 2012-7-8
 *      Author: AzureSky
 */

#ifndef NET_H_
#define NET_H_

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

struct event_base* init_net();

struct evconnlistener* net_listener(struct event_base*, const char*, int,
		evconnlistener_cb, void*, evconnlistener_errorcb);

struct bufferevent* net_connect(struct event_base*, const char*, int);

#endif /* NET_H_ */
