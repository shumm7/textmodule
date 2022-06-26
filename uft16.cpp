#include "utf16.hpp"
#include <iostream>

#include "textmodule_string.hpp"
#include "textmodule_strtmp.hpp"
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

int utf16___concat(lua_State* L) {
	try {
		lua_UTF16 s1 = tm_toutf16_s(L, 1);
		lua_UTF16 s2 = tm_toutf16_s(L, 2);

		lua_pushutf16(L, s1 + s2);
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

int utf16___find(lua_State* L) {
	try {
		auto c = string_template_find<lua_UTF16>(L, tm_toutf16(L, 1), tm_toutf16_s(L, 2), tm_tointeger_s(L, 3, 1), tm_toboolean_s(L, 4, false));
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

int utf16___sub(lua_State* L) {
	try {
		lua_UTF16 text = tm_toutf16(L, 1);
		lua_pushutf16(L, string_template_sub<lua_UTF16>(L, text, tm_tointeger(L, 2) - 1, tm_tointeger_s(L, 3, text.length()) - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___gsub(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_gsub<lua_UTF16>(L, tm_toutf16(L, 1), tm_toutf16_s(L, 2), tm_toutf16_s(L, 3), tm_tointeger_s(L, 4, 1)));
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

int utf16___len(lua_State* L) {
	try {
		lua_pushnumber(L, string_template_len<lua_UTF16>(L, tm_toutf16(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___reverse(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_reverse<lua_UTF16>(L, tm_toutf16(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___upper(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_upper<lua_UTF16>(L, tm_toutf16(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___lower(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_lower<lua_UTF16>(L, tm_toutf16(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___match(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_match<lua_UTF16>(L, tm_toutf16(L, 1), tm_toutf16_s(L, 2), tm_tointeger_s(L, 3, 1) - 1));
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

int utf16___byte(lua_State* L) {
	try {
		auto c = string_template_byte<lua_UTF16>(L, tm_toutf16(L, 1), tm_tointeger_s(L, 2, 1) - 1, tm_tointeger_s(L, 3, 1) - 1);
		for (int i = 0; i < c.size(); i++)
			lua_pushnumber(L, c.at(i));
		return c.size();
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___char(lua_State* L) {
	try {
		int n = lua_gettop(L);
		std::vector<wchar_t> chars;
		for (int i = 0; i < n; i++)
			chars.push_back(tm_tonumber(L, i + 1));

		lua_pushutf16(L, string_template_char<lua_UTF16>(L, chars));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___gmatch_aux(lua_State* L) {
	try {
		lua_UTF16 s = tm_toutf16(L, lua_upvalueindex(1));
		lua_UTF16 pattern = tm_toutf16_s(L, lua_upvalueindex(2));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(3));
		std::wsmatch m;

		int len = s.length();
		int c = 0;
		for (int i = 0; i < len; i++) {
			if (std::regex_search(s, m, std::wregex(pattern))) {
				if (c == idx) {
					lua_pushinteger(L, idx + 1);
					lua_replace(L, lua_upvalueindex(3));
					lua_pushutf16(L, m.str());
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

int utf16___gmatch(lua_State* L) {
	try {
		luaL_argcheck(L, lua_isutf16(L, 1), 1, lua_typeexception("string (utf-16)"));
		luaL_argcheck(L, lua_isutf16(L, 2) || lua_isstring(L, 2), 2, lua_typeexception(std::vector<std::string>{"string", "string (utf-16)"}));
		lua_settop(L, 2);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, utf16___gmatch_aux, 3);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___rep(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_rep<lua_UTF16>(L, tm_toutf16(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf16___format(lua_State* L) {
	try {
		lua_pushutf16(L, string_template_format(L, tm_toutf16(L, 1), 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_STRING_UTF16_TABLE_REG[]{
	{"__call", utf16_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF16_REG[]{
	{"find", utf16___find},
	{"sub", utf16___sub},
	{"gsub", utf16___gsub},
	{"len", utf16___len},
	{"reverse", utf16___reverse},
	{"upper", utf16___upper},
	{"lower", utf16___lower},
	{"match", utf16___match},
	{"byte", utf16___byte},
	{"char", utf16___char},
	{"gmatch", utf16___gmatch},
	{"rep", utf16___rep},
	{"format", utf16___format},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_STRING_UTF16_META_REG[]{
	{"__concat", utf16___concat},
	{"__tostring", utf16___tostring},
	{"__type", utf16___type},

	{"__find", utf16___find},
	{"__sub", utf16___sub},
	{"__gsub", utf16___gsub},
	{"__len", utf16___len},
	{"__reverse", utf16___reverse},
	{"__upper", utf16___upper},
	{"__lower", utf16___lower},
	{"__match", utf16___match},
	{"__byte", utf16___byte},
	{"__char", utf16___char},
	{"__gmatch", utf16___gmatch},
	{"__rep", utf16___rep},
	{"__format", utf16___format},

	{"find", utf16___find},
	{"sub", utf16___sub},
	{"gsub", utf16___gsub},
	{"len", utf16___len},
	{"reverse", utf16___reverse},
	{"upper", utf16___upper},
	{"lower", utf16___lower},
	{"match", utf16___match},
	{"byte", utf16___byte},
	{"char", utf16___char},
	{"gmatch", utf16___gmatch},
	{"rep", utf16___rep},
	{"format", utf16___format},
	{nullptr, nullptr}
};

void luaReg_utf16(lua_State* L) {
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF16, TEXTMODULE_STRING_UTF16_META_REG);
	luaL_newmetatable(L, TEXTMODULE_STRING_UTF16_TABLE, TEXTMODULE_STRING_UTF16_TABLE_REG);

	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_STRING_UTF16_REG);
	luaL_getmetatable(L, TEXTMODULE_STRING_UTF16_TABLE);
	lua_setmetatable(L, -2);
	lua_setfield(L, -2, "utf16");
}