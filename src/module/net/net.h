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

struct event_base* init_net();

struct evconnlistener* net_listener(struct event_base*, const char*, int,
		evconnlistener_cb, evconnlistener_errorcb);

#endif /* NET_H_ */
