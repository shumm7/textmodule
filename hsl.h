#pragma once
#include <lua.hpp>
#include "textmodule_color.h"

#define TEXTMODULE_HSL "HSL*"
#define hsl_check(L, n) (reinterpret_cast<HSL*>(luaL_checkudata(L, n, TEXTMODULE_HSL)))


int hsl_new(lua_State* L);
int hsl____tostring(lua_State* L);
int hsl____index(lua_State* L);
int hsl____newindex(lua_State* L);
int hsl____call(lua_State* L);

int hsl_h(lua_State* L);
int hsl_s(lua_State* L);
int hsl_l(lua_State* L);
int hsl_hsl(lua_State* L);
int hsl_rgb(lua_State* L);
int hsl_hsv(lua_State* L);

void luaReg_hsl(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_HSL_REG[] = {
	{"new", hsl_new},

	{"h", hsl_h},
	{"s", hsl_s},
	{"v", hsl_l},
	{"hsl", hsl_hsl},
	{"rgb", hsl_rgb},
	{"hsv", hsl_hsv},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_HSL_META_REG[] = {
	{"__tostring", hsl____tostring},
	//{"__index", hsl____index},
	{"__newindex", hsl____newindex},
	{"__call", hsl____call},

	{"h", hsl_h},
	{"s", hsl_s},
	{"v", hsl_l},
	{"hsv", hsl_hsl},
	{"rgb", hsl_rgb},
	{"hsv", hsl_hsv},
	{ nullptr, nullptr }
};