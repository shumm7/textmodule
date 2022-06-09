#include "sjis.hpp"
#include <iostream>
#include <regex>

#include "string_aux.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
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
		else if (lua_istable(L, 2))
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

int sjis___concat(lua_State* L) {
	try {
		lua_SJIS s1 = tm_tosjis_s(L, 1);
		lua_SJIS s2 = tm_tosjis_s(L, 2);

		lua_pushsjis(L, s1 + s2);
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

int sjis_raw(lua_State* L) {
	try {
		lua_SJIS str = tm_tosjis(L, 1);

		lua_pushsstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___find(lua_State* L) {
	try {
		auto c = string_template_find(L, tm_tosjis(L, 1), tm_tosjis_s(L, 2), tm_tointeger_s(L, 3, 1), tm_toboolean_s(L, 4, false));
		if (c.first < 0)
			lua_pushnil(L);
		else
			lua_pushnumber(L, c.first);

		if (c.second < 0)
			lua_pushnil(L);
		else
			lua_pushnumber(L, c.second);

		return 2;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___sub(lua_State* L) {
	try {
		lua_Sstring text = tm_tosjis(L, 1);
		lua_pushsjis(L, string_template_sub(L, text, tm_tointeger(L, 2) - 1, tm_tointeger_s(L, 3, text.length()) - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___gsub(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_gsub(L, tm_tosjis(L, 1), tm_tosjis_s(L, 2), tm_tosjis_s(L, 3), tm_tointeger_s(L, 4, 1)));
		return 1;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___len(lua_State* L) {
	try {
		lua_pushnumber(L, string_template_len(L, tm_tosjis(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___reverse(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_reverse(L, tm_tosjis(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___upper(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_upper(L, tm_tosjis(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___lower(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_lower(L, tm_tosjis(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___match(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_match(L, tm_tosjis(L, 1), tm_tosjis_s(L, 2), tm_tointeger_s(L, 3, 1) - 1));
		return 1;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___byte(lua_State* L) {
	try {
		auto c = string_template_byte(L, tm_tosjis(L, 1), tm_tointeger_s(L, 2, 1) - 1, tm_tointeger_s(L, 3, 1) - 1);
		for (int i = 0; i < c.size(); i++)
			lua_pushnumber(L, c[i]);
		return c.size();
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___char(lua_State* L) {
	try {
		int n = lua_gettop(L);
		std::vector<unsigned char> chars;
		for (int i = 0; i < n; i++)
			chars.push_back(tm_tonumber(L, i + 1));

		lua_pushsjis(L, string_template_char(L, chars));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___gmatch_aux(lua_State* L) {
	try {
		lua_Sstring s = tm_tosjis(L, lua_upvalueindex(1));
		lua_Sstring pattern = tm_tosjis_s(L, lua_upvalueindex(2));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(3));
		std::smatch m;

		int len = s.length();
		int c = 0;
		for (int i = 0; i < len; i++) {
			if (std::regex_search(s, m, std::regex(pattern))) {
				if (c == idx) {
					lua_pushinteger(L, idx + 1);
					lua_replace(L, lua_upvalueindex(3));
					lua_pushsjis(L, m.str());
					return 1;
				}

				c++;
				s = s.substr(m.position() + 1);
			}
		}

		return 0;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___gmatch(lua_State* L) {
	try {
		luaL_argcheck(L, lua_istable(L, 1) && luaL_checkmetatable(L, 1, TEXTMODULE_STRING_SJIS), 1, "string (shift-jis) expected");
		luaL_checkstring(L, 2);
		lua_settop(L, 2);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, sjis___gmatch_aux, 3);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___rep(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_rep(L, tm_tosjis(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int sjis___format(lua_State* L) {
	try {
		lua_pushsjis(L, string_template_format(L, tm_tosjis(L, 1), 1));
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