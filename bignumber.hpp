#pragma once
#include <lua.hpp>

int bignumber_bignumber(lua_State* L);
int bignumber___tostring(lua_State* L);
int bignumber___tonumber(lua_State* L);
int bignumber___add(lua_State* L);
int bignumber___sub(lua_State* L);
int bignumber___mul(lua_State* L);
int bignumber___div(lua_State* L);
int bignumber___mod(lua_State* L);
int bignumber___pow(lua_State* L);
int bignumber___unm(lua_State* L);
int bignumber___lt(lua_State* L);
int bignumber___le(lua_State* L);
int bignumber___eq(lua_State* L);
int bignumber___type(lua_State* L);

void luaReg_const_bignumber(lua_State* L);

static luaL_Reg TEXTMODULE_BIGNUMBER_REG[]{
	{"__call", bignumber_bignumber},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_BIGNUMBER_META_REG[]{
	{"__tostring", bignumber___tostring},
	{"__tonumber", bignumber___tonumber},
	{"__add", bignumber___add},
	{"__sub", bignumber___sub},
	{"__mul", bignumber___mul},
	{"__div", bignumber___div},
	{"__mod", bignumber___mod},
	{"__pow", bignumber___pow},
	{"__unm", bignumber___unm},
	{"__lt", bignumber___lt},
	{"__le", bignumber___le},
	{"__eq", bignumber___eq},
	{"__type", bignumber___type},
	{nullptr, nullptr}
};