#include <ctype.h>

#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/event.h>

#include "httpd.h"

#include "module/log/log.h"
#include "module/vm/vm.h"
#include "module/vm/util.h"
#include "module/net/http_util.h"

static struct evhttp *http = NULL;
static struct event_base* base = NULL;
static lua_State* L = NULL;

static void _start()
{
	if (L == NULL) return;
	if (http == NULL) return;
	if (base != NULL) event_base_dispatch(base);
}

static void _close_httpd()
{
	if (L != NULL) {
		lua_close(L);
		L = NULL;
	}

	if (http != NULL) {
		evhttp_free(http);
		http = NULL;
	}

	if (base != NULL) {
		event_base_free(base);
		base = NULL;
	}
}

static void http_handler(struct evhttp_request *req, void *arg)
{
	if (L == NULL) return;

	lua_getglobal(L, "http_request_handler");
	http_request_to_lua_table(req, L);

	if (lua_pcall(L, 1, 2, 0) != 0) {
		log_debug("%s",  lua_tostring(L, -1));
		evhttp_send_error(req, HTTP_INTERNAL, "Internal Server Error");
		return;
	}

	int is_true = lua_toboolean(L, -2);
	if (is_true) {
		struct evbuffer* evb = evbuffer_new();
		evbuffer_add_printf(evb, lua_tostring(L, -1));
		evhttp_send_reply(req, HTTP_OK, "OK", evb);
		evbuffer_free(evb);
	}
	else {
		evhttp_send_error(req, HTTP_INTERNAL, "Internal Server Error");
	}
}

static void reg_lua_http(lua_State* L);

static void _init_httpd()
{
	//TODO: hook signal

	evhttp_set_gencb(http, http_handler, NULL);

	reg_lua_http(L);
}

void init_httpd()
{
	log_debug("starting httpd......");

	L = init_vm();
	if (L == NULL) {
		log_debug("init httpd script vm fail......");
		return;
	}

	base = event_base_new();
	if (base == NULL) {
		log_debug("init libevent fail......");
		return;
	}

	http = evhttp_new(base);
	if (http == NULL) {
		log_debug("init http fail......");
		_close_httpd();
		return;
	}

	char* ip = "0.0.0.0";
	int port = 3000;
	struct evhttp_bound_socket* httpcon = evhttp_bind_socket_with_handle(http, ip, port);
	if (httpcon == NULL) {
	//if (evhttp_bind_socket(http, ip, port) != 0) {
		log_debug("http bind(%s:%d) fail......", ip, port);
		_close_httpd();
		return;
	}

	log_debug("http socket %d", (int)evhttp_bound_socket_get_fd(httpcon));

	_init_httpd();

	log_debug("httpd init ok, runing......");
	_start();
}

void close_httpd()
{
	log_debug("shutdowning httpd......");
	_close_httpd();
}

static int _is_ip(const char* ip)
{
	int len = strlen(ip);
	if (len < 1) return 0;
	int i;
	for (i = 0; i < len; ++i) {
		char c = ip[i];
		if (!isdigit(c) && c != '.') return 0;
	}
	return 1;
}

static void http_request_cb(struct evhttp_request* req, void* arg)
{
	log_debug("ok!!!!!!!!!!request %d", evhttp_request_get_response_code(req));
}

int lua_http_request_get(lua_State* L)
{
	if (lua_gettop(L) < 3) {
		lua_pushboolean(L, 0);
		return 1;
	}
	const char* ip = lua_tostring(L, 1);
	if (!_is_ip(ip)) {
		lua_pushboolean(L, 0);
		return 1;
	}
	int port = lua_tonumber(L, 2);
	const char* uri = lua_tostring(L, 3);

	struct evhttp_request* req = http_request_new(
			base, ip, port, http_request_cb,
			EVHTTP_REQ_GET, uri, NULL);

	if (req == NULL) lua_pushboolean(L, 0);
	else lua_pushboolean(L, 1);

	return 1;
}

int lua_http_request_post(lua_State* L)
{
	if (lua_gettop(L) < 3) {
		lua_pushboolean(L, 0);
		return 1;
	}
	const char* ip = lua_tostring(L, 1);
	if (!_is_ip(ip)) {
		lua_pushboolean(L, 0);
		return 1;
	}
	int port = lua_tonumber(L, 2);
	const char* uri = lua_tostring(L, 3);

	struct evhttp_request* req = http_request_new(
			base, ip, port, http_request_cb,
			EVHTTP_REQ_POST, uri, NULL);

	if (req == NULL) lua_pushboolean(L, 0);
	else lua_pushboolean(L, 1);

	return 1;
}

int dump_base(lua_State* L)
{
	FILE* fd = fopen("log/dump.log", "a+");
	if (fd) {
		event_base_dump_events(base, fd);
		fclose(fd);
	}
	return 0;
}

int test_array(lua_State* L)
{
	if (lua_table_is_array(L)) lua_pushboolean(L, 1);
	else lua_pushboolean(L, 0);
	return 1;
}

const struct luaL_Reg lua_http_lib[] = {
		{"encode_uri", lua_http_uri_encode},
		{"decode_uri", lua_http_uri_decode},
		{"post", lua_http_request_post},
		{"get", lua_http_request_get},
		{"dump", dump_base},
		{"encode_header", lua_http_uri_header_encode},
		{"decode_header", lua_http_uri_header_decode},
		{"is_array", test_array},
		{NULL, NULL}
};

static void reg_lua_http(lua_State* L)
{
	luaL_register(L, "http", lua_http_lib);
}
