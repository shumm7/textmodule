#include <lua.hpp>
#include "textmodule_color.h"

#define TEXTMODULE_RGB "rgb*"
#define rgb_check(L, n) (reinterpret_cast<RGB*>(luaL_checkudata(L, n, TEXTMODULE_RGB)))

int rgb_new(lua_State* L);
int rgb_comp(lua_State* L);
int rgb_opposite(lua_State* L);

int rgb____tostring(lua_State* L);
int rgb____add(lua_State* L);
int rgb____sub(lua_State* L);
int rgb____mul(lua_State* L);
int rgb____lt(lua_State* L);
int rgb____le(lua_State* L);
int rgb____index(lua_State* L);
int rgb____newindex(lua_State* L);
int rgb____call(lua_State* L);

int rgb_r(lua_State* L);
int rgb_g(lua_State* L);
int rgb_b(lua_State* L);
int rgb_rgb(lua_State* L);
int rgb_hex(lua_State* L);
int rgb_number(lua_State* L);
int rgb_hsv(lua_State* L);
int rgb_hsl(lua_State* L);
int rgb_average(lua_State* L);

void luaReg_rgb(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_RGB_REG[] = {
	{"new", rgb_new},
	{"comp", rgb_comp},
	{"opposite", rgb_opposite},

	{"r", rgb_r},
	{"g", rgb_g},
	{"b", rgb_b},

	{"value", rgb_rgb},
	{"hex", rgb_hex},
	{"number", rgb_number},
	{"num", rgb_number},
	{"hsv", rgb_hsv},
	{"hsl", rgb_hsl},
	{"average", rgb_average},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_RGB_META_REG[] = {
	{"__tostring", rgb____tostring},
	{"__add", rgb____add},
	{"__sub", rgb____sub},
	{"__mul", rgb____mul},
	{"__lt", rgb____lt},
	{"__le", rgb____le},
	//{"__index", rgb____index},
	{"__newindex", rgb____newindex},
	{"__call", rgb____call},

	{"comp", rgb_comp},
	{"opposite", rgb_opposite},
	{"r", rgb_r},
	{"g", rgb_g},
	{"b", rgb_b},
	{"rgb", rgb_rgb},
	{"hex", rgb_hex},
	{"number", rgb_number},
	{"hsv", rgb_hsv},
	{"hsl", rgb_hsl},
	{"average", rgb_average},
	{ nullptr, nullptr }
};