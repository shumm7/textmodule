#include "bignumber.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

#include "textmodule_type.hpp"
#include "textmodule_lua.hpp"

int bignumber_bignumber(lua_State* L) {
	try {
		lua_pushbignumber(L, tm_tobignumber(L, 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___tostring(lua_State* L) {
	try {
		lua_Bignumber n = tm_tobignumber(L, 1);
		lua_pushsstring(L, n.str());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___tonumber(lua_State* L) {
	try {
		lua_Bignumber n = tm_tobignumber(L, 1);
		lua_pushnumber(L, (lua_Number)n);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___add(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) + tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___sub(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) - tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___mul(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) * tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___div(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) / tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___mod(lua_State* L) {
	try {
		lua_Bignumber ret = boost::multiprecision::fmod(tm_tobignumber(L, 1), tm_tobignumber(L, 2));
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___pow(lua_State* L) {
	try {
		lua_Bignumber ret = boost::multiprecision::pow(tm_tobignumber(L, 1), tm_tointeger(L, 2));
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___unm(lua_State* L) {
	try {
		lua_pushbignumber(L, -tm_tobignumber(L, 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___lt(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) < tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___le(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) <= tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___eq(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) == tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___type(lua_State* L) {
	try {
		lua_pushstring(L, "bignumber");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
