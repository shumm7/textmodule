#include <lua.hpp>
#include <iostream>
#include "textmodule_string.h"
#include "textmodule_exception.h"

std::wstring lua_towstring(lua_State* L, int idx) {
	return StrToWstr(lua_tostring(L, idx));
}

std::wstring tm_towstring(lua_State* L, int idx) {
	return StrToWstr(luaL_checkstring(L, idx));
}

const char* tm_tostring(lua_State* L, int idx) {
	return luaL_checkstring(L, idx);
}

int tm_tointeger(lua_State* L, int idx) {
	return luaL_checkinteger(L, idx);
}

float tm_tofloat(lua_State* L, int idx) {
	return static_cast<float>(luaL_checknumber(L, idx));
}

double tm_todouble(lua_State* L, int idx) {
	return static_cast<double>(luaL_checknumber(L, idx));
}

double tm_tonumber(lua_State* L, int idx) {
	return tm_todouble(L, idx);
}

unsigned long tm_tounsigned(lua_State* L, int idx) {
	return static_cast<unsigned long>(luaL_checkinteger(L, idx));
}


void lua_pushwstring(lua_State* L, std::wstring s) {
	lua_pushstring(L, WstrToStr(s).c_str());
}

void lua_pushsstring(lua_State* L, std::string s) {
	lua_pushstring(L, s.c_str());
}

int tm_tointeger_s(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");
	if (tp == LUA_TNONE) {
		return 0;
	}
	else {
		return lua_tointeger(L, idx);
	}
}

int tm_tointeger_s(lua_State* L, int idx, int def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tointeger(L, idx);
	}
}

double tm_tonumber_s(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return 0;
	}
	else {
		return lua_tonumber(L, idx);
	}
}

double tm_tonumber_s(lua_State* L, int idx, double def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tonumber(L, idx);
	}
}

const char* tm_tostring_s(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return "";
	}
	else {
		return lua_tostring(L, idx);
	}
}

const char* tm_tostring_s(lua_State* L, int idx, const char* def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tostring(L, idx);
	}
}

std::wstring tm_towstring_s(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return L"";
	}
	else {
		return lua_towstring(L, idx);
	}
}

std::wstring tm_towstring_s(lua_State* L, int idx, std::wstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_towstring(L, idx);
	}
}

bool tm_toboolean_s(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TBOOLEAN, idx, "boolean/none expected");

	if (tp == LUA_TNONE) {
		return false;
	}
	else {
		return lua_toboolean(L, idx);
	}
}

bool tm_toboolean_s(lua_State* L, int idx, bool def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TBOOLEAN, idx, "boolean/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_toboolean(L, idx);
	}
}

bool luaL_checkmetatable(lua_State* L, int ud, const char* tname) {
	if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
		lua_getfield(L, LUA_REGISTRYINDEX, tname);  /* get correct metatable */
		if (lua_rawequal(L, -1, -2)) {  /* does it have the correct mt? */
			lua_pop(L, 2);
			return true;
		}
	}
	return false;
}