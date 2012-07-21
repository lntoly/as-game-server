#include "rpc_util.h"
#include "module/lua_util.h"

void rpc_dispatch(struct evbuffer* packet, lua_State* L)
{
	if (find_lua_function(L, "rpc", "dispatch")) {
		int base = lua_gettop(L);
		//TODO unpack

		int args = lua_gettop(L) - base;
		if (args < 0) args = 0;
		call_lua_script(L, args);
	}
}

static int lua_rpc_pack(lua_State* L)
{
	if (lua_gettop(L) < 2) return 0;
	return 0;
}

static const struct luaL_Reg lua_rpc_function[] = {
		{"rpc_pack", lua_rpc_pack},
		{NULL, NULL}
};

void reg_lua_rpc(lua_State* L)
{
	luaL_register(L, "_G", lua_rpc_function);
}
