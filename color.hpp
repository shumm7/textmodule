#pragma once
#include <lua.hpp>

int color_new(lua_State* L);

int color____tostring(lua_State* L);
int color____add(lua_State* L);
int color____sub(lua_State* L);
int color____mul(lua_State* L);
int color____div(lua_State* L);
int color____lt(lua_State* L);
int color____le(lua_State* L);
int color____index(lua_State* L);
int color____newindex(lua_State* L);
int color____type(lua_State* L);

int color_r(lua_State* L);
int color_g(lua_State* L);
int color_b(lua_State* L);
int color_a(lua_State* L);

int color_opposite(lua_State* L);
int color_comp(lua_State* L);
int color_average(lua_State* L);
int color_max(lua_State* L);
int color_min(lua_State* L);
int color_clamp(lua_State* L);
int color_pixel(lua_State* L);

void luaReg_color(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COLOR_REG[] = {
	{"new", color_new},

	{"r", color_r},
	{"g", color_g},
	{"b", color_b},
	{"a", color_a},

	{"opposite", color_opposite},
	{"comp", color_comp},
	{"average", color_average},
	{"max", color_max},
	{"min", color_min},
	{"clamp", color_clamp},
	{"pixel", color_pixel},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_COLOR_META_REG[] = {
	{"__tostring", color____tostring},
	{"__add", color____add},
	{"__sub", color____sub},
	{"__mul", color____mul},
	{"__div", color____div},
	{"__lt", color____lt},
	{"__le", color____le},
	{"__index", color____index},
	{"__newindex", color____newindex},
	{"__type", color____type},

	{"r", color_r},
	{"g", color_g},
	{"b", color_b},
	{"a", color_a},

	{"opposite", color_opposite},
	{"comp", color_comp},
	{"average", color_average},
	{"max", color_max},
	{"min", color_min},
	{"clamp", color_clamp},
	{"pixel", color_pixel},

	{nullptr, nullptr}
};