#include "string.hpp"

#include <lua.hpp>
#include <iostream>
#include <regex>
#include <vector>

#include "mecab.hpp"
#include "tmstring.hpp"

#include "sjis.hpp"
#include "utf8.hpp"
#include "utf16.hpp"
#include "utf32.hpp"
#include "eucjp.hpp"

#include "textmodule_strtmp.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_math.hpp"

int string_find(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__find"))
			return 2;

		auto c = string_template_find<lua_Wstring>(L, tm_towstring(L, 1), tm_towstring(L, 2), tm_tointeger_s(L, 3, 1), tm_toboolean_s(L, 4, false));

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

int string_sub(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__sub"))
			return 1;

		lua_Wstring text = tm_towstring(L, 1);
		lua_pushwstring(L, string_template_sub<lua_Wstring>(L, text, tm_tointeger(L, 2) - 1, tm_tointeger_s(L, 3, text.length()) - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_gsub(lua_State* L) {
	try {
		int st = lua_gettop(L);
		if (tm_callmetan(L, 1, "__gsub"))
			return 1;

		lua_pushwstring(L, string_template_gsub<lua_Wstring>(L, tm_towstring(L, 1), tm_towstring(L, 2), tm_towstring(L, 3), tm_tointeger_s(L, 4, 1)));
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

int string_len(lua_State* L) {
	try {
		if (tm_callmeta(L, 1, "__len"))
			return 1;

		lua_pushnumber(L, string_template_len<lua_Wstring>(L, tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_reverse(lua_State* L) {
	try {
		if (tm_callmeta(L, 1, "__reverse"))
			return 1;

		lua_pushwstring(L, string_template_reverse<lua_Wstring>(L, tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_upper(lua_State* L) {
	try {
		if (tm_callmeta(L, 1, "__upper"))
			return 1;

		lua_pushwstring(L, string_template_upper<lua_Wstring>(L, tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_lower(lua_State* L) {
	try {
		if (tm_callmeta(L, 1, "__lower"))
			return 1;

		lua_pushwstring(L, string_template_lower<lua_Wstring>(L, tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_match(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__match"))
			return 1;

		lua_pushwstring(L, string_template_match<lua_Wstring>(L, tm_towstring(L, 1), tm_towstring(L, 2), tm_tointeger_s(L, 3, 1) - 1));
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

int string_byte(lua_State* L) {
	try {
		int st = lua_gettop(L);
		if (tm_callmetan(L, 1, "__byte"))
			return lua_gettop(L) - st;

		auto c = string_template_byte<lua_Wstring>(L, tm_towstring(L, 1), tm_tointeger_s(L, 2, 1) - 1, tm_tointeger_s(L, 3, 1) - 1);
		for (int i = 0; i < c.size(); i++)
			lua_pushnumber(L, c.at(i));
		return c.size();
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_char(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__char"))
			return 1;

		int n = lua_gettop(L);
		std::vector<wchar_t> chars;
		for (int i = 0; i < n; i++)
			chars.push_back(tm_tonumber(L, i + 1));

		lua_pushwstring(L, string_template_char<lua_Wstring>(L, chars));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_gmatch_aux(lua_State* L) {
	try {
		lua_Wstring s = lua_towstring(L, lua_upvalueindex(1));
		lua_Wstring pattern = lua_towstring(L, lua_upvalueindex(2));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(3));
		std::wsmatch m;

		int len = s.length();
		int c = 0;
		for (int i = 0; i < len; i++) {
			if (std::regex_search(s, m, std::wregex(pattern))) {
				if (c == idx) {
					lua_pushinteger(L, idx + 1);
					lua_replace(L, lua_upvalueindex(3));
					lua_pushwstring(L, m.str());
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

int string_gmatch(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__gmatch"))
			return 1;

		luaL_checkstring(L, 1);
		luaL_checkstring(L, 2);
		lua_settop(L, 2);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, string_gmatch_aux, 3);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_rep(lua_State* L) {
	try {
		int st = lua_gettop(L);
		if (tm_callmetan(L, 1, "__rep"))
			return 1;

		lua_pushwstring(L, string_template_rep<lua_Wstring>(L, tm_towstring(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_format(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__format"))
			return 1;

		lua_pushsstring(L, string_template_format(L, tm_tosstring(L, 1), 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_dump(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__dump"))
			return 1;

		luaL_pushresult(string_template_dump(L));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_STRING_REG[] = {
	{"find", string_find},
	{"sub", string_sub},
	{"gsub", string_gsub},
	{"len", string_len},
	{"reverse", string_reverse},
	{"upper", string_upper},
	{"lower", string_lower},
	{"match", string_match},
	{"byte", string_byte},
	{"char", string_char},
	{"gmatch", string_gmatch},
	{"rep", string_rep},
	{"format", string_format},
	{"dump", string_dump},
	{ nullptr, nullptr }
};

void luaReg_string(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);

		//string tmstring mecab
		luaL_register(L, NULL, TEXTMODULE_STRING_REG);
		luaReg_tmstring(L);
		luaReg_mecab(L);

		//string table
		luaReg_sjis(L);
		luaReg_utf8(L);
		luaReg_utf16(L);
		luaReg_utf32(L);
		luaReg_eucjp(L);

		lua_setfield(L, -2, name);
	}
}