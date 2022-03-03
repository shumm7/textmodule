#pragma once
#include <lua.hpp>

int main_getinfo(lua_State* L);
int main_debug_print(lua_State* L);
int main_exception(lua_State* L);
void luaReg_base(lua_State* L, bool reg);

static luaL_Reg TEXTMODULE_MAIN_REG[] = {
	{"getinfo", main_getinfo},
	{"debug_print", main_debug_print},
	{"exception", main_exception},
	{ nullptr, nullptr }
};