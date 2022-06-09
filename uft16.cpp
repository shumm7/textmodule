#include "utf16.hpp"
#include <iostream>

#include "textmodule_string.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"

int utf16_new(lua_State* L) {
	try {
		lua_UTF16 str;
		if (lua_type(L, 2) == LUA_TNUMBER) {
			int n = lua_gettop(L) - 1;

			for (int i = 0; i < n; i++) {
				wchar_t c = tm_tonumber(L, i + 2);
				str += c;
			}
		}
		else if (lua_isstring(L, 2))
			str = StrToWstr(tm_tosstring(L, 2));
		else if (lua_istable(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_UTF16))
			str = tm_toutf16(L, 2);
		else if (lua_istable(L, 2))
			str = lua_toutf16(L, 2);
		else
			return luaL_argerror(L, 2, "string/number/string (utf-16) expected");

		lua_pushutf16(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___tostring(lua_State* L) {
	try {
		lua_UTF16 s = tm_toutf16(L, 1);
		lua_pushwstring(L, s);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___type(lua_State* L) {
	try {
		lua_pushstring(L, "string (utf-16)");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_utf16(lua_State* L) {
	//utf16 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF16); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF16_META_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF16_META_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable


	//table utf16 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF16_TABLE); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF16_TABLE_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF16_TABLE_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}