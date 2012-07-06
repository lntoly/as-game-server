#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "module/log/log.h"

static int traceback (lua_State *L) {
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

lua_State* init_vm()
{
	log_debug("initing script vm......");
	lua_State* L = luaL_newstate();
	if (L == NULL) {
		log_error("init script vm fail......");
		return NULL;
	}
	luaL_openlibs(L);

	int status = luaL_loadfile(L, "./init.lua");
	if (status != 0) {
		log_error("loadfile fail: %s", lua_tostring(L, -1));
		close_vm(L);
		return NULL;
	}

	int base = lua_gettop(L);
	lua_pushcfunction(L, traceback);
	lua_insert(L, base);
	if (lua_pcall(L, 0, LUA_MULTRET, base)) {
		log_error("loadfile fail: %s", lua_tostring(L, -1));
		close_vm(L);
		return 0;
	}

	lua_remove(L, base);

	log_debug("script vm init ok......");
	return L;
}

void close_vm(lua_State* L)
{
	if (L != NULL) lua_close(L);
}
