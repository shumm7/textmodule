#pragma once
#include <lua.hpp>

int device_key(lua_State* L);
int device_joystick(lua_State* L);
int device_mouse(lua_State* L);
int device_version(lua_State* L);

void luaReg_device(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_DEVICE_REG[] = {
	{"key", device_key},
	{"joystick", device_joystick},
	{"mouse", device_mouse},
	{"version", device_version},
	{ nullptr, nullptr }
};