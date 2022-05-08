#pragma once
#include <lua.hpp>

int pixel_new(lua_State* L);

int pixel____tostring(lua_State* L);
int pixel____add(lua_State* L);
int pixel____sub(lua_State* L);
int pixel____mul(lua_State* L);
int pixel____div(lua_State* L);
int pixel____lt(lua_State* L);
int pixel____le(lua_State* L);
int pixel____index(lua_State* L);
int pixel____newindex(lua_State* L);

int pixel_r(lua_State* L);
int pixel_g(lua_State* L);
int pixel_b(lua_State* L);
int pixel_a(lua_State* L);

int pixel_color(lua_State* L);

void luaReg_pixel(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_PIXEL_REG[] = {
	{"new", pixel_new},

	{"r", pixel_r},
	{"g", pixel_g},
	{"b", pixel_b},
	{"a", pixel_a},

	{"color", pixel_color},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_PIXEL_META_REG[] = {
	{"__tostring", pixel____tostring},
	{"__add", pixel____add},
	{"__sub", pixel____sub},
	{"__mul", pixel____mul},
	{"__div", pixel____div},
	{"__lt", pixel____lt},
	{"__le", pixel____le},
	{"__index", pixel____index},
	{"__newindex", pixel____newindex},

	{"r", pixel_r},
	{"g", pixel_g},
	{"b", pixel_b},
	{"a", pixel_a},

	{"color", pixel_color},

	{nullptr, nullptr}
};