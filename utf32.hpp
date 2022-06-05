#pragma once
#include <lua.hpp>

int utf32_new(lua_State* L);
int utf32___tostring(lua_State* L);
int utf32___type(lua_State* L);

void luaReg_utf32(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_UTF32_TABLE_REG[]{
	{"__call", utf32_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF32_REG[]{
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF32_META_REG[]{
	{"__tostring", utf32___tostring},
	{"__type", utf32___type},
	{nullptr, nullptr}
};