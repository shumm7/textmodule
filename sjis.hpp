#pragma once
#include <lua.hpp>

int sjis_new(lua_State* L);
int sjis___concat(lua_State* L);
int sjis___tostring(lua_State* L);
int sjis___type(lua_State* L);
int sjis_raw(lua_State* L);
int sjis___find(lua_State* L);
int sjis___sub(lua_State* L);
int sjis___gsub(lua_State* L);
int sjis___len(lua_State* L);
int sjis___reverse(lua_State* L);
int sjis___upper(lua_State* L);
int sjis___lower(lua_State* L);
int sjis___match(lua_State* L);
int sjis___byte(lua_State* L);
int sjis___char(lua_State* L);
int sjis___gmatch(lua_State* L);
int sjis___rep(lua_State* L);
int sjis___format(lua_State* L);

void luaReg_sjis(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_SJIS_TABLE_REG[]{
	{"__call", sjis_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_SJIS_REG[]{
	{"raw", sjis_raw},
	{"find", sjis___find},
	{"sub", sjis___sub},
	{"gsub", sjis___gsub},
	{"len", sjis___len},
	{"reverse", sjis___reverse},
	{"upper", sjis___upper},
	{"lower", sjis___lower},
	{"match", sjis___match},
	{"byte", sjis___byte},
	{"char", sjis___char},
	{"gmatch", sjis___gmatch},
	{"rep", sjis___rep},
	{"format", sjis___format},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_SJIS_META_REG[]{
	{"__concat", sjis___concat},
	{"__tostring", sjis___tostring},
	{"__type", sjis___type},
	{"__find", sjis___find},
	{"__sub", sjis___sub},
	{"__gsub", sjis___gsub},
	{"__len", sjis___len},
	{"__reverse", sjis___reverse},
	{"__upper", sjis___upper},
	{"__lower", sjis___lower},
	{"__match", sjis___match},
	{"__byte", sjis___byte},
	{"__char", sjis___char},
	{"__gmatch", sjis___gmatch},
	{"__rep", sjis___rep},
	{"__format", sjis___format},

	{"raw", sjis_raw},
	{"find", sjis___find},
	{"sub", sjis___sub},
	{"gsub", sjis___gsub},
	{"len", sjis___len},
	{"reverse", sjis___reverse},
	{"upper", sjis___upper},
	{"lower", sjis___lower},
	{"match", sjis___match},
	{"byte", sjis___byte},
	{"char", sjis___char},
	{"gmatch", sjis___gmatch},
	{"rep", sjis___rep},
	{"format", sjis___format},
	{nullptr, nullptr}
};