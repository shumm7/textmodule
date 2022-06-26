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
		else if (lua_istable(L, 2))
			str = lua_toeucjp(L, 2);
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

int eucjp___concat(lua_State* L) {
	try {
		lua_EUCJP s1 = tm_toeucjp_s(L, 1);
		lua_EUCJP s2 = tm_toeucjp_s(L, 2);

		lua_pusheucjp(L, s1 + s2);
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


static luaL_Reg TEXTMODULE_STRING_EUCJP_TABLE_REG[]{
	{"__call", eucjp_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_EUCJP_REG[]{
	{"raw", eucjp_raw},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_EUCJP_META_REG[]{
	{"__concat", eucjp___concat},
	{"__tostring", eucjp___tostring},
	{"__type", eucjp___type},
	{"raw", eucjp_raw},
	{nullptr, nullptr}
};

void luaReg_eucjp(lua_State* L) {
	luaL_newmetatable(L, TEXTMODULE_STRING_EUCJP, TEXTMODULE_STRING_EUCJP_META_REG);
	luaL_newmetatable(L, TEXTMODULE_STRING_EUCJP_TABLE, TEXTMODULE_STRING_EUCJP_TABLE_REG);

	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_EUCJP_REG);
	luaL_getmetatable(L, TEXTMODULE_STRING_EUCJP_TABLE);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "eucjp");
}