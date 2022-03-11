#pragma once
#include <lua.hpp>
#include <iostream>

std::wstring lua_towstring(lua_State* L, int idx);
std::wstring tm_towstring(lua_State* L, int idx);
const char* tm_tostring(lua_State* L, int idx);
int tm_tointeger(lua_State* L, int idx);
float tm_tofloat(lua_State* L, int idx);
double tm_todouble(lua_State* L, int idx);
double tm_tonumber(lua_State* L, int idx);

void lua_pushwstring(lua_State* L, std::wstring s);
void lua_pushsstring(lua_State* L, std::string s);

int tm_tointeger_s(lua_State* L, int idx);
int tm_tointeger_s(lua_State* L, int idx, int def);
double tm_tonumber_s(lua_State* L, int idx);
double tm_tonumber_s(lua_State* L, int idx, double def);
const char* tm_tostring_s(lua_State* L, int idx);
const char* tm_tostring_s(lua_State* L, int idx, const char* def);
std::wstring tm_towstring_s(lua_State* L, int idx);
std::wstring tm_towstring_s(lua_State* L, int idx, std::wstring def);
bool tm_toboolean_s(lua_State* L, int idx);
bool tm_toboolean_s(lua_State* L, int idx, bool def);