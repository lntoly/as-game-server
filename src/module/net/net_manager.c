#include <apr_hash.h>
#include "net_manager.h"
#include "module/log/log.h"

static apr_hash_t* clients_con = NULL;
static apr_pool_t* hash_pool = NULL;

void init_net_manager()
{
    apr_pool_create(&hash_pool, NULL);
    clients_con = apr_hash_make(hash_pool);
}

void close_net_manager()
{
	 apr_pool_destroy(hash_pool);
}

void net_add_connect(evutil_socket_t fd, struct bufferevent* con)
{
	apr_hash_set(clients_con, (void*)&fd, sizeof(evutil_socket_t), con);

	log_debug("new a con %d", (int)fd);
}

void net_del_connect(evutil_socket_t fd)
{
	apr_hash_set(clients_con, (void*)&fd, sizeof(evutil_socket_t), NULL);

	log_debug("close a con %d", (int)fd);
}

struct bufferevent* net_get_connect(evutil_socket_t fd)
{
	return apr_hash_get(clients_con, (void*)&fd, sizeof(evutil_socket_t));
}
