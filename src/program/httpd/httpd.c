#include <ctype.h>
#include <string.h>

#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/event.h>

#include "httpd.h"

#include "module/log.h"
#include "module/lua_util.h"
#include "module/net/http_util.h"
#include "module/memory.h"

static struct evhttp *http = NULL;
static struct event_base* base = NULL;
static lua_State* L = NULL;

static void _start()
{
	if (L == NULL) return;
	if (http == NULL) return;
	if (base != NULL) event_base_dispatch(base);
}

static void close_cb(struct evhttp_connection * con, void * arg)
{
	log_debug("close request con");
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

	if (!find_lua_global_function(L, "http_request_handler")) return;

	http_request_to_lua_table(req, L);

	if (call_lua_script(L, 1) != 2) {
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

static void _reg_lua_http(lua_State* L);

static void _init_httpd()
{
	//TODO: hook signal

	_reg_lua_http(L);
	reg_lua_common_http(L);
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

	http = init_http(base, http_handler, NULL);
	if (http == NULL) {
		log_debug("init http fail......");
		_close_httpd();
		return;
	}

	char* ip = "0.0.0.0";
	int port = 3000;
	//struct evhttp_bound_socket* httpcon = evhttp_bind_socket_with_handle(http, ip, port);
	//if (httpcon == NULL) {
	if (evhttp_bind_socket(http, ip, port) != 0) {
		log_debug("http bind(%s:%d) fail......", ip, port);
		_close_httpd();
		return;
	}

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
	for (int i = 0; i < len; ++i) {
		char c = ip[i];
		if (!isdigit(c) && c != '.') return 0;
	}
	return 1;
}

struct lua_callback_info_t {
	struct apr_pool_t* pool;
	char* table;
	char* function;
};

static void http_request_cb(struct evhttp_request* req, void* arg)
{
	log_debug("ok!!!!!!!!!!request %d", evhttp_request_get_response_code(req));

	struct lua_callback_info_t* ptr = (struct lua_callback_info_t*)arg;
	log_debug("table:%s, function:%s", ptr->table, ptr->function);

	if (find_lua_function(L, ptr->table, ptr->function)) {
		call_lua_script(L, 0);
	}
	else {
	}

	pool_free(ptr->pool);
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

	size_t tblen = 0;
	const char* table = lua_tolstring(L, 4, &tblen);
	if (table == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}
	size_t funlen = 0;
	const char* function = lua_tolstring(L, 5, &funlen);
	if (function == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}

	struct apr_pool_t* pool = pool_new();
	if (pool == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}

	struct lua_callback_info_t* args = pool_palloc(pool, sizeof(struct lua_callback_info_t));
	if (args == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
		return 1;
	}

	args->pool = pool;
	args->table = pool_palloc(pool, tblen+1);
	args->function = pool_palloc(pool, funlen+1);
	if (args->table == NULL || args->function == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
		return 1;
	}

	strncpy(args->table, table, tblen);
	args->table[tblen] = '\0';
	strncpy(args->function, function, funlen);
	args->function[funlen] = '\0';

	struct evhttp_request* req = http_request_new(
			base, ip, port,
			http_request_cb, args,
			close_cb, NULL,
			EVHTTP_REQ_GET, uri);

	if (req == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
	}
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

	size_t tblen = 0;
	const char* table = lua_tolstring(L, 4, &tblen);
	if (table == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}
	size_t funlen = 0;
	const char* function = lua_tolstring(L, 5, &funlen);
	if (function == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}

	struct apr_pool_t* pool = pool_new();
	if (pool == NULL) {
		lua_pushboolean(L, 0);
		return 1;
	}

	struct lua_callback_info_t* args = pool_palloc(pool, sizeof(struct lua_callback_info_t));
	if (args == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
		return 1;
	}

	args->pool = pool;
	args->table = pool_palloc(pool, tblen+1);
	args->function = pool_palloc(pool, funlen+1);
	if (args->table == NULL || args->function == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
		return 1;
	}

	strncpy(args->table, table, tblen);
	args->table[tblen] = '\0';
	strncpy(args->function, function, funlen);
	args->function[funlen] = '\0';

	struct evhttp_request* req = http_request_new(
			base, ip, port,
			http_request_cb, args,
			close_cb, NULL,
			EVHTTP_REQ_POST, uri);

	if (req == NULL) {
		pool_free(pool);
		lua_pushboolean(L, 0);
	}
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
		{"post", lua_http_request_post},
		{"get", lua_http_request_get},
		{"dump", dump_base},
		{"is_array", test_array},
		{NULL, NULL}
};

static void _reg_lua_http(lua_State* L)
{
	luaL_register(L, "http", lua_http_lib);
}
