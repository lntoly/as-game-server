#ifndef VM_UTIL_H_
#define VM_UTIL_H_

#include "vm.h"

int traceback (lua_State*);
int lua_table_is_array(lua_State*);
int load_lua_library(lua_State*, const char*);
int find_lua_function(lua_State*, const char*, const char*);
int find_lua_global_function(lua_State*, const char*);
int call_lua_script(lua_State*, int);

void reg_lua_common_function(lua_State*);

#endif /* VM_UTIL_H_ */
