#include <string.h>
#include "util.h"
#include "module/log/log.h"

int traceback (lua_State *L)
{
	if (!lua_isstring(L, 1))  /* 'message' not a string? */
		return 1;  /* keep it intact */
	lua_getfield(L, LUA_GLOBALSINDEX, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}

int lua_table_is_array(lua_State* L)
{
	int base = lua_gettop(L);
	if (base < 1) {
		return 0;
	}
	if (!lua_istable(L, base)) return 0;

	int size = luaL_getn(L, -1);
	int cnt = 0;
	lua_pushnil(L);
	while (lua_next(L, base)) {
		lua_pop(L, 1);
		if (!lua_isnumber(L, -1)) return 0;
		if (lua_tonumber(L, -1) > size) return 0;
		cnt++;
	}
	lua_settop(L, base);
	return cnt == size;
}

int load_lua_library(lua_State* L, const char* module_name)
{
	int base = lua_gettop(L);
	lua_pushcfunction(L, traceback);
	lua_getglobal(L, "require");
	lua_pushstring(L, module_name);
	if (lua_pcall(L, 1, 1, base+1)) {
		lua_settop(L, base);
		return 0;
	}
	else {
		lua_remove(L, base+1);
		return 1;
	}
}

int find_lua_function(lua_State* L, const char* module, const char* func)
{
	if (strlen(module) < 1) return 0;
	if (strlen(func) < 1) return 0;

	int base = lua_gettop(L);
	lua_pushstring(L, module);
	int module_index = lua_gettop(L);

	luaL_findtable(L, LUA_GLOBALSINDEX, "package.loaded", 1);
	lua_pushvalue(L, module_index);
	lua_rawget(L, -2);

	if (lua_isnil(L, -1)) {
		if (!load_lua_library(L, module)) {
			lua_settop(L, base);
			return 0;
		}
	}

	if (lua_istable(L, -1)) {
		lua_pushstring(L, func);
		lua_rawget(L, -2);
	}
	else {
		if (!lua_isboolean(L, -1)) {
			lua_settop(L, base);
			return 0;
		}
		int istrue = lua_toboolean(L, -1);
		lua_pop(L, 1);
		if (istrue) {
			lua_getglobal(L, func);
		}
		else {
			lua_settop(L, base);
			return 0;
		}
	}

	if (lua_isfunction(L, -1)) {
		lua_replace(L, module_index);
		lua_settop(L, module_index);
		return 1;
	}
	else {
		lua_settop(L, base);
		return 0;
	}
}

int find_lua_global_function(lua_State* L, const char* func)
{
	lua_getglobal(L, func);
	if (lua_isfunction(L, -1)) {
		return 1;
	}
	else {
		lua_pop(L, 1);
		return 0;
	}
}

int call_lua_script(lua_State* L, int args)
{
	if (args < 0) args = 0;
	int base = lua_gettop(L) - 1 - args;
	if (base < 0) return 0;

	if (lua_pcall(L, args, LUA_MULTRET, 0) != 0) {
		log_debug("%s",  lua_tostring(L, -1));
		return 0;
	}
	else {
		int ret = lua_gettop(L) - base;
		return ret < 0 ? 0 : ret;
	}
}

//-------------------- reg lua function ------------------//

static int lua_root(lua_State* L)
{
	lua_pushvalue(L, LUA_GLOBALSINDEX);
	return 1;
}

static int lua_catch(lua_State* L)
{
	lua_pushcfunction(L, traceback);
	lua_insert(L, 1);

	int args = lua_gettop(L) - 2;
	if (args < 0) args = 0;
	if (lua_pcall(L, args, LUA_MULTRET, 1)) {
		log_debug("lua catch: %s",lua_tostring(L, -1));
	}

	lua_remove(L, 1);
	return 0;
}

static int lua_this(lua_State* L)
{
	lua_Debug ar;
	int level = 0;
	if (lua_gettop(L) > 0) level = lua_tonumber(L, 1);
	if (level < 1) level = 1;
	if (!lua_getstack(L, level, &ar)) {
		lua_pushstring(L, "_G");
		return 1;
	}
	if (!lua_getinfo(L, "S", &ar)) {
		lua_pushstring(L, "_G");
		return 1;
	}

	if (ar.source[0] != '@') {
		if (strcmp(ar.what, "Lua")) {
			lua_pushstring(L, "_G");
			return 1;
		}
	}

	char* start = NULL;
	char* end = NULL;
	if (ar.short_src[0] == '.') {
		if (ar.short_src[1] == '/' || ar.short_src[1] == '\\') start = &(ar.short_src[2]);
		else start = &(ar.short_src[1]);
	}
	else start = ar.short_src;
	end = strstr(start, ".");
	size_t len = end - start;
	if (len < 1 || len > LUA_IDSIZE) {
		lua_pushstring(L, "_G");
		return 1;
	}

	luaL_Buffer b;
	luaL_buffinit(L, &b);
	int i;
	for (i = 0; i < len; ++i) {
		if (start[i] == '\\' || start[i] == '/') {
			luaL_addchar(&b, '.');
		}
		else {
			luaL_addchar(&b, start[i]);
		}
	}
	luaL_pushresult(&b);
	return 1;
}

static int lua_call_script(lua_State* L)
{
	if (lua_gettop(L) < 2) return 0;
	lua_pushcfunction(L, traceback);
	lua_insert(L, 1);

	int args = lua_gettop(L) - 3;
	if (args < 0) args = 0;
	if (find_lua_function(L, lua_tostring(L, 2), lua_tostring(L, 3))) {
		lua_replace(L, 3);
		if (lua_pcall(L, args, LUA_MULTRET, 1)) {
			return 0;
		}
		else {
			int ret = lua_gettop(L) - 2;
			return ret < 0 ? 0 : ret;
		}
	}
	else {
		log_debug("lua call_script: cannot find %s:%s", lua_tostring(L, 2), lua_tostring(L, 3));
		return 0;
	}
}

static int lua_write_file(lua_State* L)
{
	if (lua_gettop(L) < 3) {
		lua_pushboolean(L, 0);
		return 1;
	}

	size_t file_len = 0;
	const char* file = lua_tolstring(L, 1, &file_len);
	if (file_len < 1) {
		lua_pushboolean(L, 0);
		return 1;
	}

	int is_with_time = lua_toboolean(L, 2);

	size_t msg_len = 0;
	const char* msg = lua_tolstring(L, 3, &msg_len);
	if (msg_len < 1) {
		lua_pushboolean(L, 0);
		return 1;
	}

	if (is_with_time) log_file_with_time(file, msg);
	else log_file(file, msg);

	lua_pushboolean(L, 1);
	return 1;
}

static const struct luaL_Reg lua_common_function[] = {
		{"root", lua_root},
		{"catch", lua_catch},
		{"this", lua_this},
		{"call_script", lua_call_script},
		{"write_file", lua_write_file},
		{NULL, NULL}
};

void reg_lua_common_function(lua_State* L)
{
	luaL_register(L, "_G", lua_common_function);
}
