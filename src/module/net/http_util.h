/*
 * http_util.h
 *
 *  Created on: 2012-7-5
 *      Author: Administrator
 */

#ifndef HTTP_UTIL_H_
#define HTTP_UTIL_H_

#include <event2/event.h>
#include <event2/http.h>
#include <lua.h>

typedef void (*request_cb)(struct evhttp_request *, void *);

struct evhttp* init_http(struct event_base*, request_cb, void*);

struct evhttp_request* http_request_new(struct event_base* base,
		const char* address, unsigned short port, request_cb, void*,
		void (*)(struct evhttp_connection *, void *), void*,
		enum evhttp_cmd_type type, const char* uri);

void http_request_to_lua_table(struct evhttp_request*, lua_State*);
int add_http_request_header(lua_State*, struct evhttp_request*);

void reg_lua_common_http(lua_State*);

#endif /* HTTP_UTIL_H_ */
