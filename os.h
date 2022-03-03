#pragma once
#include <lua.hpp>
int os_time(lua_State* L);
int os_date(lua_State* L);
int os_difftime(lua_State* L);
int os_clock(lua_State* L);
int os_sleep(lua_State* L);

void luaReg_os(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_OS_REG[] = {
	{"time", os_time},
	{"date", os_date},
	{"difftime", os_difftime},
	{"clock", os_clock},
	{"sleep", os_sleep},
	{ nullptr, nullptr }
};