#pragma once
#include <lua.hpp>
#include <iostream>

std::wstring lua_towstring(lua_State* L, int idx);
int lua_toint(lua_State* L, int idx);
float lua_tofloat(lua_State* L, int idx);
double lua_todouble(lua_State* L, int idx);

void lua_pushwstring(lua_State* L, std::wstring s);
void lua_pushsstring(lua_State* L, std::string s);