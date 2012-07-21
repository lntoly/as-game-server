#include <stdio.h>
#include <stdlib.h>

#include "vm.h"
#include "util.h"
#include "module/log.h"

lua_State* init_vm()
{
	log_debug("initing script vm......");
	lua_State* L = luaL_newstate();
	if (L == NULL) {
		log_debug("init script vm fail......");
		return NULL;
	}

	luaL_openlibs(L);
	reg_lua_common_function(L);

	if (!load_lua_library(L, "init")) {
		close_vm(L);
		return NULL;
	}

	lua_pop(L, lua_gettop(L));

	log_debug("script vm init ok......");
	return L;
}

void close_vm(lua_State* L)
{
	if (L != NULL) lua_close(L);
}
