#pragma once
#include <lua.hpp>

int string_find(lua_State* L);
int string_sub(lua_State* L);
int string_gsub(lua_State* L);
int string_len(lua_State* L);
int string_reverse(lua_State* L);
int string_upper(lua_State* L);
int string_lower(lua_State* L);
int string_match(lua_State* L);
int string_byte(lua_State* L);
int string_char(lua_State* L);
int string_gmatch(lua_State* L);
int string_rep(lua_State* L);
int string_format(lua_State* L);
int string_dump(lua_State* L);

void luaReg_string(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_STRING_REG[] = {
	{"find", string_find},
	{"sub", string_sub},
	{"gsub", string_gsub},
	{"len", string_len},
	{"reverse", string_reverse},
	{"upper", string_upper},
	{"lower", string_lower},
	{"match", string_match},
	{"byte", string_byte},
	{"char", string_char},
	{"gmatch", string_gmatch},
	{"rep", string_rep},
	{"format", string_format},
	{"dump", string_dump},
	{ nullptr, nullptr }
};