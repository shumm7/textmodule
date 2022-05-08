#pragma once
#include <lua.hpp>

int image_set(lua_State* L);
int image_getpixel(lua_State* L);
int image_setpixel(lua_State* L);

void luaReg_image(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_IMAGE_REG[] = {
	{"set", image_set},

	{ "getpixel", image_getpixel },
	{ "setpixel", image_setpixel },
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_IMAGE_META_REG[] = {
	{ "getpixel", image_getpixel },
	{ "setpixel", image_setpixel },
	{nullptr, nullptr}
};