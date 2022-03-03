#include <lua.hpp>
#include <iostream>
#include "textmodule_string.h"

std::wstring lua_towstring(lua_State* L, int idx) {
	return StrToWstr(lua_tostring(L, idx));
}

int lua_toint(lua_State* L, int idx) {
	return static_cast<int>(lua_tointeger(L, idx));
}

float lua_tofloat(lua_State* L, int idx) {
	return static_cast<float>(lua_tonumber(L, idx));
}

double lua_todouble(lua_State* L, int idx) {
	return static_cast<double>(lua_tonumber(L, idx));
}

void lua_pushwstring(lua_State* L, std::wstring s) {
	lua_pushstring(L, WstrToStr(s).c_str());
}

void lua_pushsstring(lua_State* L, std::string s) {
	lua_pushstring(L, s.c_str());
}
