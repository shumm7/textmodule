#include <lua.hpp>
#include <iostream>
#include <chrono>
#include <sstream>
#include <mecab.h>
#include <random>

#include "tmstring.h"
#include "mecab.h"
#include "textmodule_exception.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

int tmstring_hiragana(lua_State* L) {
	try {
		std::wstring katakana = tm_towstring(L, 1);
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
		std::wstring hiragana = tm_towstring(L, 1);
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
		std::wstring fullwidth = tm_towstring(L, 1);
		bool mode = tm_toboolean_s(L, 2, true);

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
		std::wstring halfwidth = tm_towstring(L, 1);
		bool mode = tm_toboolean_s(L, 2, true);

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
		std::wstring str = tm_towstring(L, 1);
		std::string hex = "";
		std::string ret = "";

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
		std::wstring text = tm_towstring(L, 1);
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
		std::wstring str = tm_towstring(L, 1);
		int length = tm_tointeger(L, 2);

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
		std::wstring str = tm_towstring(L, 1);
		int length = tm_tointeger(L, 2);

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
		std::string str = tm_tostring(L, 1);
		int shift = tm_tointeger_s(L, 2, 1);
		int pos = tm_tointeger_s(L, 3, 1);
		int len = tm_tointeger_s(L, 4, 1);;


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
		std::wstring str = tm_towstring(L, 1);
		int shift = tm_tointeger_s(L, 2, 1);
		int pos = tm_tointeger_s(L, 3, 1);
		int len = tm_tointeger_s(L, 4, 1);

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

int tmstring_squeeze(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);
		std::wstring filter = tm_towstring_s(L, 2);

		for (int i = 1; i < str.length(); i++) {
			if (str[i - 1] == str[i]) {
				if (filter == L"") {
					str = str.erase(i, 1);
					i--;
				}
				else {
					for (int j = 0; j < filter.length(); j++) {
						if (filter[j] == str[i]) {
							str = str.erase(i, 1);
							i--;
							break;
						}
					}
				}
			}
		}

		lua_pushwstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_capitalize(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);

		str = lowerString(str);
		str[0] = toupper(str[0]);

		lua_pushwstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_capitalize_words(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);

		str = lowerString(str);
		str[0] = toupper(str[0]);

		for (int i = 1; i < str.length(); i++) {
			if(str[i-1]==L' ')
				str[i] = toupper(str[i]);
		}

		lua_pushwstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_random(lua_State* L) {
	try {
		int len = tm_tointeger(L, 1);
		std::wstring str = tm_towstring(L, 2);
		int seed;
		std::wstring ret = L"";

		int tp = lua_type(L, 3);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 3, "number/none expected");

		int l = str.length() - 1;
		if (l < 0)
			l = 0;

		if (tp == LUA_TNONE) {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::uniform_int_distribution<> dist(0, l);

			for (int i = 0; i < len; i++) {
				ret += str[dist(engine)];
			}
			lua_pushwstring(L, ret);
			return 1;
		}
		else if (tp == LUA_TNUMBER) {
			seed = luaL_checkinteger(L, 3);
			std::default_random_engine engine(seed);
			std::uniform_int_distribution<> dist(0, l);

			for (int i = 0; i < len; i++) {
				ret += str[dist(engine)];
			}
			lua_pushwstring(L, ret);
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_roundnumber(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);

		lua_pushwstring(L, toRoundNumber(str, false));
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

		lua_pushstring(L, S_NUMBER);
		lua_setfield(L, -2, "number");

		lua_pushstring(L, S_ALPHABET);
		lua_setfield(L, -2, "alphabet");

		lua_pushstring(L, S_SMALL_ALPHABET);
		lua_setfield(L, -2, "small_alphabet");

		lua_pushstring(L, S_CAPITAL_ALPHABET);
		lua_setfield(L, -2, "capital_alphabet");

		lua_pushstring(L, S_ALPHABET_NUMBER);
		lua_setfield(L, -2, "alphabet_number");

		lua_pushstring(L, S_SYMBOL);
		lua_setfield(L, -2, "symbol");

		lua_pushstring(L, S_ASCII);
		lua_setfield(L, -2, "ascii");

		lua_pushstring(L, S_HIRAGANA);
		lua_setfield(L, -2, "c_hiragana");

		lua_pushstring(L, S_KATAKANA);
		lua_setfield(L, -2, "c_katakana");

		lua_pushstring(L, S_HALF_KATAKANA);
		lua_setfield(L, -2, "half_katakana");

		lua_pushstring(L, S_HIRAGANA_N);
		lua_setfield(L, -2, "n_hiragana");

		lua_pushstring(L, S_IROHA);
		lua_setfield(L, -2, "iroha");

		lua_pushstring(L, S_PIPE);
		lua_setfield(L, -2, "pipe");

		lua_pushstring(L, S_FULL_NUMBER);
		lua_setfield(L, -2, "full_number");

		lua_pushstring(L, S_FULL_ALPHABET);
		lua_setfield(L, -2, "full_alphabet");

		lua_pushstring(L, S_FULL_SMALL_ALPHABET);
		lua_setfield(L, -2, "full_small_alphabet");

		lua_pushstring(L, S_FULL_CAPITAL_ALPHABET);
		lua_setfield(L, -2, "full_capital_alphabet");

		lua_pushstring(L, S_FULL_ALPHABET_NUMBER);
		lua_setfield(L, -2, "full_alphabet_number");

		lua_setfield(L, -2, name);
	}
}