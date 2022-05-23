#pragma once
#include <lua.hpp>

int clipboard_get(lua_State* L);
int clipboard_set(lua_State* L);
int clipboard_clear(lua_State* L);

void luaReg_clipboard(lua_State* L, const char* name, bool reg);
void luaGlobal_clipboard(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_CLIPBOARD_REG[] = {
	{"get", clipboard_get},
	{"set", clipboard_set},
	{"clear", clipboard_clear},
	{ nullptr, nullptr }
};