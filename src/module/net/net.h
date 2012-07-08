/*
 * net.h
 *
 *  Created on: 2012-7-8
 *      Author: AzureSky
 */

#ifndef NET_H_
#define NET_H_

#include <event2/event.h>

void init_net(struct event_base*);

int net_listener(struct event_base*, const char*, int);

#endif /* NET_H_ */
