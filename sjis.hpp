#pragma once
#include <lua.hpp>

int sjis_new(lua_State* L);
int sjis___tostring(lua_State* L);
int sjis___type(lua_State* L);

void luaReg_sjis(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_SJIS_TABLE_REG[]{
	{"__call", sjis_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_SJIS_REG[]{
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_SJIS_META_REG[]{
	{"__tostring", sjis___tostring},
	{"__type", sjis___type},
	{nullptr, nullptr}
};