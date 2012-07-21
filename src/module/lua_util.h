#ifndef LUA_UTIL_H_
#define LUA_UTIL_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

lua_State* init_vm();
void close_vm(lua_State*);

int traceback (lua_State*);
int lua_table_is_array(lua_State*);
int load_lua_library(lua_State*, const char*);
int find_lua_function(lua_State*, const char*, const char*);
int find_lua_global_function(lua_State*, const char*);
int call_lua_script(lua_State*, int);

void reg_lua_common_function(lua_State*);

#endif /* LUA_UTIL_H_ */
