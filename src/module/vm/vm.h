/*
 * vm.h
 *
 *  Created on: 2012-7-4
 *      Author: Administrator
 */

#ifndef LUA_VM_H_
#define LUA_VM_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

lua_State* init_vm();
void close_vm(lua_State*);

#endif /* LUA_VM_H_ */
