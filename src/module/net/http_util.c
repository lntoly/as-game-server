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

void http_request_to_lua_table(struct evhttp_request* req, lua_State* L)
{
	const struct evhttp_uri* uri = evhttp_request_get_evhttp_uri(req);
	if (uri == NULL) return;

	lua_createtable(L, 0, 5);
	lua_pushstring(L, "path");
	lua_pushstring(L, evhttp_uri_get_path(uri));
	lua_rawset(L, -3);

	lua_pushstring(L, "query");
	lua_pushstring(L, evhttp_uri_get_query(uri));
	lua_rawset(L, -3);

	lua_pushstring(L, "host");
	lua_pushstring(L, evhttp_request_get_host(req));
	lua_rawset(L, -3);

	lua_pushstring(L, "code");
	lua_pushnumber(L, evhttp_request_get_response_code(req));
	lua_rawset(L, -3);

	lua_pushstring(L, "command");
	lua_pushnumber(L, evhttp_request_get_command(req));
	lua_rawset(L, -3);
}

int add_http_request_header(lua_State* L, struct evhttp_request* req)
{
	int base = lua_gettop(L);
	if (base < 1) return 0;
	if (!lua_istable(L, base)) return 0;

	struct evkeyvalq* headers = evhttp_request_get_output_headers(req);
	lua_pushnil(L);
	while (lua_next(L, base)) {
		const char* value = lua_tostring(L, -1);
		const char* key = lua_tostring(L, -2);

		evhttp_add_header(headers, key, value);
		lua_pop(L, 1);
	}
	lua_settop(L, base);
	return 1;
}

static int lua_http_uri_encode(lua_State* L)
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

static int lua_http_uri_decode(lua_State* L)
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

static int lua_http_uri_header_encode(lua_State* L)
{
	int base = lua_gettop(L);
	if (base < 1) {
		lua_pushstring(L, "");
		return 1;
	}
	if (!lua_istable(L, base)) {
		lua_pushstring(L, "");
		return 1;
	}

	luaL_Buffer b;
	luaL_buffinit(L, &b);
	int is_head = 1;
	lua_pushnil(L);
	while (lua_next(L, base)) {
		if (is_head) is_head = 0;
		else luaL_addstring(&b, "&");

		//copy key to top
		lua_pushvalue(L, -2);
		// add key
		luaL_addvalue(&b);
		luaL_addstring(&b, "=");
		// add value
		luaL_addvalue(&b);
	}

	luaL_pushresult(&b);
	lua_replace(L, base);
	lua_settop(L, base);
	return 1;
}

static int lua_http_uri_header_decode(lua_State* L)
{
	return 0;
}

static const struct luaL_Reg lua_common_http_lib[] = {
		{"encode_uri", lua_http_uri_encode},
		{"decode_uri", lua_http_uri_decode},
		{"encode_header", lua_http_uri_header_encode},
		{"decode_header", lua_http_uri_header_decode},
		{NULL, NULL}
};

void reg_lua_common_http(lua_State* L)
{
	luaL_register(L, "http", lua_common_http_lib);
}
