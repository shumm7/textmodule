#include "sjis.hpp"
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"

int sjis_new(lua_State* L) {
	try {
		lua_SJIS str;
		if (lua_type(L, 2) == LUA_TNUMBER) {
			int n = lua_gettop(L) - 1;

			for (int i = 0; i < n; i++) {
				unsigned char c = tm_tonumber(L, i + 2);
				str += c;
			}
		}
		else if (lua_isstring(L, 2))
			str = tm_tosstring(L, 2);
		else if (lua_istable(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_SJIS))
			str = tm_tosjis(L, 2);
		else
			return luaL_argerror(L, 2, "string/number/string (shift-jis) expected");

		lua_pushsjis(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___tostring(lua_State* L) {
	try {
		lua_SJIS s = tm_tosjis(L, 1);
		lua_pushsstring(L, s);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___type(lua_State* L) {
	try {
		lua_pushstring(L, "string (shift-jis)");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_sjis(lua_State* L) {
	//sjis (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_SJIS); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_SJIS_META_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_SJIS_META_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable


	//table sjis (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_SJIS_TABLE); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_SJIS_TABLE_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_SJIS_TABLE_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}