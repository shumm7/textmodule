#pragma once
#include <lua.hpp>

int eucjp_new(lua_State* L);
int eucjp___tostring(lua_State* L);
int eucjp___type(lua_State* L);
int eucjp_raw(lua_State* L);

void luaReg_eucjp(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_EUCJP_TABLE_REG[]{
	{"__call", eucjp_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_EUCJP_REG[]{
	{"raw", eucjp_raw},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_EUCJP_META_REG[]{
	{"__tostring", eucjp___tostring},
	{"__type", eucjp___type},
	{"raw", eucjp_raw},
	{nullptr, nullptr}
};