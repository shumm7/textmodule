#pragma once
#include <lua.hpp>

void luaReg_debug(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_DEBUG_REG[] = {
	{ nullptr, nullptr }
};