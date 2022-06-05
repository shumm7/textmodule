#include "eucjp.hpp"
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

int eucjp_new(lua_State* L) {
	try {
		lua_EUCJP str;
		if (lua_type(L, 2) == LUA_TNUMBER) {
			int n = lua_gettop(L) - 1;

			for (int i = 0; i < n; i++) {
				unsigned char c = tm_tonumber(L, i + 2);
				str += c;
			}
		}
		else if (lua_isstring(L, 2))
			str = StrToEUCstr(tm_tosstring(L, 2));
		else if (lua_istable(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_STRING_EUCJP))
			str = tm_toeucjp(L, 2);
		else
			return luaL_argerror(L, 2, "string/number/string (euc-jp) expected");

		lua_pusheucjp(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int eucjp___tostring(lua_State* L) {
	try {
		lua_EUCJP s = tm_toeucjp(L, 1);
		lua_pushsstring(L, EUCstrToStr(s));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int eucjp___type(lua_State* L) {
	try {
		lua_pushstring(L, "string (euc-jp)");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int eucjp_raw(lua_State* L) {
	try {
		lua_EUCJP str = tm_toeucjp(L, 1);

		lua_pushsstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_eucjp(lua_State* L) {
	//eucjp (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_EUCJP); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_EUCJP_META_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_EUCJP_META_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable


	//table eucjp (metatable)
	luaL_newmetatable(L, TEXTMODULE_STRING_EUCJP_TABLE); //add metatable
	luaL_register(L, NULL, TEXTMODULE_STRING_EUCJP_TABLE_REG);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_EUCJP_TABLE_REG);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}