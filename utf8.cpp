#include "utf8.hpp"
#include <iostream>

#include "textmodule_string.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"

int utf8_new(lua_State* L) {
	try {
		lua_UTF8 str;
		if (lua_type(L, 2)==LUA_TNUMBER) {
			int n = lua_gettop(L) - 1;

			for (int i = 0; i < n; i++) {
				unsigned char c = tm_tonumber(L, i + 2);
				str += c;
			}
		}
		else if (lua_isstring(L, 2))
			str = StrToU8str(tm_tosstring(L, 2));
		else if (lua_istable(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_UTF8))
			str = tm_toutf8(L, 2);
		else if (lua_istable(L, 2))
			str = lua_toutf8(L, 2);
		else
			return luaL_argerror(L, 2, "string/number/string (utf-8) expected");

		lua_pushutf8(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf8___concat(lua_State* L) {
	try {
		lua_UTF8 s1;
		lua_UTF8 s2;

		if (lua_type(L, 1) == LUA_TTABLE && luaL_checkmetatable(L, 1, TEXTMODULE_STRING_SJIS))
			s1 = tm_toutf8(L, 1);
		else if (lua_type(L, 1) == LUA_TSTRING)
			s1 = StrToU8str(tm_tosstring(L, 1));

		if (lua_type(L, 2) == LUA_TTABLE && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_SJIS))
			s2 = tm_toutf8(L, 2);
		else if (lua_type(L, 2) == LUA_TSTRING)
			s2 = StrToU8str(tm_tosstring(L, 2));

		lua_pushsstring(L, U8strToStr(s1 + s2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf8___tostring(lua_State* L) {
	try {
		lua_UTF8 s = tm_toutf8(L, 1);
		lua_pushsstring(L, U8strToStr(s));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf8___type(lua_State* L) {
	try {
		lua_pushstring(L, "string (utf-8)");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf8_raw(lua_State* L) {
	try {
		lua_UTF8 str = tm_toutf8(L, 1);
		lua_Sstring ret;

		for (int i = 0; i < str.length(); i++)
			ret += str[i];

		lua_pushsstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_STRING_UTF8_TABLE_REG[]{
	{"__call", utf8_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF8_REG[]{
	{"raw", utf8_raw},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF8_META_REG[]{
	{"__tostring", utf8___tostring},
	{"__type", utf8___type},
	{"raw", utf8_raw},
	{nullptr, nullptr}
};

void luaReg_utf8(lua_State* L) {
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF8, TEXTMODULE_STRING_UTF8_META_REG);
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF8_TABLE, TEXTMODULE_STRING_UTF8_TABLE_REG);

	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF8_REG);
	luaL_getmetatable(L, TEXTMODULE_STRING_UTF8_TABLE);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "utf8");
}