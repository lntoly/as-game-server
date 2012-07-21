/*
 * rpc_util.h
 *
 *  Created on: 2012-7-8
 *      Author: AzureSky
 */

#ifndef RPC_UTIL_H_
#define RPC_UTIL_H_

#include <event2/buffer.h>
#include "lua_util.h"

void init_rpc(struct event_base*);
void rpc_dispatch(struct evbuffer*, lua_State*);

void reg_lua_rpc(lua_State*);

#endif /* RPC_UTIL_H_ */
