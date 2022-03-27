#pragma once
#include <lua.hpp>

int base_getinfo(lua_State* L);
int base_debug_print(lua_State* L);
int base_exception(lua_State* L);
int base_versioncheck(lua_State* L);
void luaReg_base(lua_State* L, bool reg);

static luaL_Reg TEXTMODULE_BASE_REG[] = {
	{"getinfo", base_getinfo},
	{"debug_print", base_debug_print},
	{"exception", base_exception},
	{"versioncheck", base_versioncheck},
	{ nullptr, nullptr }
};