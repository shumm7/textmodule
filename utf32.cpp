#include "utf32.hpp"
#include <iostream>

#include "textmodule_string.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"

int utf32_new(lua_State* L) {
	try {
		lua_UTF32 str;
		if (lua_type(L, 2) == LUA_TNUMBER) {
			int n = lua_gettop(L) - 1;

			for (int i = 0; i < n; i++) {
				unsigned int c = tm_tonumber(L, i + 2);
				str += c;
			}
		}
		else if (lua_isstring(L, 2))
			str = WstrToU32str(tm_towstring(L, 2));
		else if (lua_istable(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_UTF16))
			str = tm_toutf32(L, 2);
		else if (lua_istable(L, 2))
			str = lua_toutf32(L, 2);
		else
			return luaL_argerror(L, 2, "string/number/string (utf-32) expected");

		lua_pushutf32(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf32___tostring(lua_State* L) {
	try {
		lua_UTF32 s = tm_toutf32(L, 1);
		lua_pushwstring(L, U32strToWstr(s));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf32___type(lua_State* L) {
	try {
		lua_pushstring(L, "string (utf-32)");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_utf32(lua_State* L) {
	//utf32 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF32); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF32_META_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF32_META_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable


	//utf32 (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF32_TABLE); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF32_TABLE_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF32_TABLE_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}