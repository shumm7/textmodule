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

int utf32___concat(lua_State* L) {
	try {
		lua_UTF32 s1 = tm_toutf32_s(L, 1);
		lua_UTF32 s2 = tm_toutf32_s(L, 2);

		lua_pushutf32(L, s1 + s2);
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


static luaL_Reg TEXTMODULE_STRING_UTF32_TABLE_REG[]{
	{"__call", utf32_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF32_REG[]{
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF32_META_REG[]{
	{"__concat", utf32___concat},
	{"__tostring", utf32___tostring},
	{"__type", utf32___type},
	{nullptr, nullptr}
};

void luaReg_utf32(lua_State* L) {
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF32, TEXTMODULE_STRING_UTF32_META_REG);
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF32_TABLE, TEXTMODULE_STRING_UTF32_TABLE_REG);

	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF32_REG);
	luaL_getmetatable(L, TEXTMODULE_STRING_UTF32_TABLE);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "utf32");
}