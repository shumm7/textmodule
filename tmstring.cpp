#include <lua.hpp>
#include <iostream>
#include <chrono>
#include <sstream>
#include <mecab.h>

#include "tmstring.h"
#include "mecab.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

int tmstring_hiragana(lua_State* L) {
	try {
		std::wstring katakana;
		if (lua_type(L, 1) == LUA_TSTRING) {
			katakana = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		lua_pushwstring(L, toKatakana(katakana, true));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_katakana(lua_State* L) {
	try {
		std::wstring hiragana;
		if (lua_type(L, 1) == LUA_TSTRING) {
			hiragana = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		lua_pushwstring(L, toKatakana(hiragana, false));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_halfwidth(lua_State* L) {
	try {
		std::wstring fullwidth;
		bool mode;

		if (lua_type(L, 1) == LUA_TSTRING) {
			fullwidth = lua_towstring(L, 1);
		}
		else {
			return 0;
		}
		if (lua_type(L, 2) == LUA_TBOOLEAN) {
			mode = lua_toboolean(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			mode = true;
		}
		else {
			return 0;
		}

		lua_pushwstring(L, toHalfwidth(fullwidth, false, mode));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_fullwidth(lua_State* L) {
	try {
		std::wstring halfwidth;
		bool mode;

		if (lua_type(L, 1) == LUA_TSTRING) {
			halfwidth =lua_towstring(L, 1);
		}
		else {
			return 0;
		}
		if (lua_type(L, 2) == LUA_TBOOLEAN) {
			mode = lua_toboolean(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			mode = true;
		}
		else {
			return 0;
		}

		lua_pushwstring(L, toHalfwidth(halfwidth, true, mode));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_mojibake(lua_State* L) {
	try {
		std::wstring str = L"";
		std::string hex = "";
		std::string ret = "";

		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		for (unsigned int i = 0; i < str.length(); i++)
		{
			auto unicode_c = str[i];
			if (unicode_c == L'\n') {
				hex = hex + "0d0a";
			}
			else if (unicode_c == L'\t') {
				hex = hex + "09";
			}
			else if (unicode_c == L'\b') {
				hex = hex + "08";
			}
			else if (unicode_c == L'\a') {
				hex = hex + "07";
			}
			else {
				auto utf8_c = UnicodeToUTF8(unicode_c);
				hex += std::format("{:x}", utf8_c);
			}

		}

		for (unsigned int i = 0; i < hex.length() / 2; i++) {
			std::string c = hex.substr(i * 2, 2);
			ret += std::stoi(c, 0, 16);
		}

		lua_pushsstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_swapcase(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}

		std::wstring text = lua_towstring(L, 1);
		std::wstring ret;

		for (unsigned int i = 0; i < text.length(); i++)
		{
			if (text[i] >= L'a' && text[i] <= L'z')
				ret += toupper(text[i]);
			else if (text[i] >= L'A' && text[i] <= L'Z')
				ret += tolower(text[i]);
			else
				ret += text[i];
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_left(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}
		if (lua_type(L, 2) != LUA_TNUMBER) {
			return 0;
		}

		std::wstring str = lua_towstring(L, 1);
		int length = lua_tointeger(L, 2);

		if (length > str.size())
			length = str.size();

		std::wstring ret = L"";
		for (int i = 0; i < length; i++) {
			ret += str[i];
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_right(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TNUMBER) {
			return 0;
		}

		std::wstring str = lua_towstring(L, 1);
		int length = lua_tointeger(L, 2);

		if (length > str.size())
			length = str.size();

		std::wstring ret = L"";
		for (int i = 0; i < length; i++) {
			ret = str[str.size()-(i+1)] + ret;
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_cshift(lua_State* L) {
	try {
		std::string str;
		int shift;
		int pos;
		int len;

		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			shift = lua_tointeger(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
			shift = 1;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			pos = lua_tointeger(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNONE || lua_type(L, 3) == LUA_TNIL) {
			pos = 1;
		}
		else {
			return 0;
		}

		if (lua_type(L, 4) == LUA_TNUMBER) {
			len = lua_tointeger(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNONE || lua_type(L, 4) == LUA_TNIL) {
			len = 1;
		}
		else {
			return 0;
		}

		for (int i = 0; i < len; i++) {
			int p = (pos - 1) + i;
			if (p<0 || p>(str.size() - 1)) {
				break;
			}

			char s = str[p];
			s += shift;
			str[p] = s;
		}

		lua_pushsstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_wcshift(lua_State* L) {
	try {
		std::wstring str;
		int shift;
		int pos;
		int len;

		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			shift = lua_tointeger(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
			shift = 1;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			pos = lua_tointeger(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNONE || lua_type(L, 3) == LUA_TNIL) {
			pos = 1;
		}
		else {
			return 0;
		}

		if (lua_type(L, 4) == LUA_TNUMBER) {
			len = lua_tointeger(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNONE || lua_type(L, 4) == LUA_TNIL) {
			len = 1;
		}
		else {
			return 0;
		}

		for (int i = 0; i < len; i++) {
			int p = (pos - 1) + i;
			if (p<0 || p>(str.size() - 1)) {
				break;
			}

			wchar_t s = str[p];
			s += shift;
			str[p] = s;
		}

		lua_pushwstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_tmstring(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_TMSTRING_REG);
		luaL_register(L, NULL, TEXTMODULE_MECAB_REG);
		lua_setfield(L, -2, name);
	}
}