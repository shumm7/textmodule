#pragma once
#include <lua.hpp>
#define TEXTMODULE_UTF8PATT "[\0-\x7F\xC2-\xFD][\x80-\xBF]*"

int utf8_new(lua_State* L);
int utf8___tostring(lua_State* L);
int utf8___type(lua_State* L);
int utf8_raw(lua_State* L);

void luaReg_utf8(lua_State* L);

static luaL_Reg TEXTMODULE_STRING_UTF8_TABLE_REG[]{
	{"__call", utf8_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF8_REG[]{
	{"raw", utf8_raw},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF8_META_REG[]{
	{"__tostring", utf8___tostring},
	{"__type", utf8___type},
	{"raw", utf8_raw},
	{nullptr, nullptr}
};