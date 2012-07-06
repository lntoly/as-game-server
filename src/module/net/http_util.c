#include "http_util.h"
#include "module/vm/vm.h"
#include "module/log/log.h"
#include "module/memory/mm.h"
#include <string.h>

static void close_cb(struct evhttp_connection * con, void * arg)
{
	log_debug("close request con");
}

struct evhttp_request* http_request_new(struct event_base* base,
		const char* address, unsigned short port, request_cb cb,
		enum evhttp_cmd_type type, const char* uri, void* arg)
{
	struct evhttp_connection *evcon = NULL;
	struct evhttp_request *req = NULL;

	evcon = evhttp_connection_base_new(base, NULL, address, port);
	if (evcon == NULL) return NULL;

	evhttp_connection_set_closecb(evcon, close_cb, NULL);

	req = evhttp_request_new(cb, arg);
	if (req == NULL) {
		evhttp_connection_free(evcon);
		return NULL;
	}

	if (evhttp_make_request(evcon, req, type, uri) != 0) {
		evhttp_request_free(req);
		evhttp_connection_free(evcon);
		return NULL;
	}
	else return req;
}

int lua_http_uri_encode(lua_State* L)
{
	if (lua_gettop(L) < 1) {
		lua_pushstring(L, "");
		return 1;
	}

	if (!lua_isstring(L, 1)) {
		lua_pushstring(L, "");
		return 1;
	}

	size_t len = 0;
	const char* uri = lua_tolstring(L, 1, &len);
	if (uri == NULL || len < 1) {
		lua_pushstring(L, "");
		return 1;
	}

	char* encode = evhttp_uriencode(uri, len, 1);
	if (encode == NULL) {
		lua_pushstring(L, "");
		return 1;
	}
	lua_pushstring(L, encode);
	E_FREE(encode);
	return 1;
}

int lua_http_uri_decode(lua_State* L)
{
	if (lua_gettop(L) < 1) {
		lua_pushstring(L, "");
		return 1;
	}

	if (!lua_isstring(L, 1)) {
		lua_pushstring(L, "");
		return 1;
	}

	size_t len = 0;
	const char* uri = lua_tolstring(L, 1, &len);
	if (uri == NULL || len < 1) {
		lua_pushstring(L, "");
		return 1;
	}

	size_t delen = 0;
	char* decode = evhttp_uridecode(uri, 1, &delen);
	if (decode == NULL) {
		lua_pushstring(L, "");
		return 1;
	}
	lua_pushlstring(L, decode, delen);
	E_FREE(decode);
	return 1;
}
