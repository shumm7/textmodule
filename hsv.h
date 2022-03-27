#pragma once
#include <lua.hpp>
#include "textmodule_color.h"

#define TEXTMODULE_HSV "HSV*"
#define hsv_check(L, n) (reinterpret_cast<HSV*>(luaL_checkudata(L, n, TEXTMODULE_HSV)))

int hsv_new(lua_State* L);
int hsv____tostring(lua_State* L);
int hsv____index(lua_State* L);
int hsv____newindex(lua_State* L);
int hsv____call(lua_State* L);

int hsv_h(lua_State* L);
int hsv_s(lua_State* L);
int hsv_v(lua_State* L);
int hsv_hsv(lua_State* L);
int hsv_rgb(lua_State* L);

void luaReg_hsv(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_HSV_REG[] = {
	{"new", hsv_new},

	{"h", hsv_h},
	{"s", hsv_s},
	{"v", hsv_v},
	{"hsv", hsv_hsv},
	{"rgb", hsv_rgb},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_HSV_META_REG[] = {
	{"__tostring", hsv____tostring},
	//{"__index", hsv____index},
	{"__newindex", hsv____newindex},
	//{"__call", hsv____call},

	{"h", hsv_h},
	{"s", hsv_s},
	{"v", hsv_v},
	{"value", hsv_hsv},
	{"rgb", hsv_rgb},
	{ nullptr, nullptr }
};