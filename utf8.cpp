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

void luaReg_utf8(lua_State* L) {
	//utf8 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF8); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF8_META_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF8_META_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable


	//table utf8 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF8_TABLE); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF8_TABLE_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF8_TABLE_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}