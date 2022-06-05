#pragma once
#include <lua.hpp>

int utf16_new(lua_State* L);
int utf16___tostring(lua_State* L);
int utf16___type(lua_State* L);

void luaReg_utf16(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_UTF16_TABLE_REG[]{
	{"__call", utf16_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF16_REG[]{
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF16_META_REG[]{
	{"__tostring", utf16___tostring},
	{"__type", utf16___type},
	{nullptr, nullptr}
};