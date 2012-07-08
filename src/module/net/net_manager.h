#ifndef NET_MANAGER_H_
#define NET_MANAGER_H_

#include <event2/bufferevent.h>
#include <event2/util.h>

void init_net_manager();
void close_net_manager();
void net_add_connect(evutil_socket_t, struct bufferevent*);
void net_del_connect(evutil_socket_t);
struct bufferevent* net_get_connect(evutil_socket_t);

#endif /* NET_MANAGER_H_ */
