#include "util.h"

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
