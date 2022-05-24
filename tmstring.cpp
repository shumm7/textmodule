#include "tmstring.hpp"

#include <lua.hpp>
#include <iostream>
#include <chrono>
#include <sstream>
#include <mecab.h>
#include <random>
#include <regex>
#include <format>
#include <unicode/translit.h>

#include "mecab.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"

int tmstring_hiragana(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		lua_pushustring(L, KatakanaToHiragana(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_katakana(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		lua_pushustring(L, HiraganaToKatakana(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_halfwidth(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		lua_pushustring(L, FullwidthToHalfwidth(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_fullwidth(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		lua_pushustring(L, HalfwidthToFullwidth(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_fromlatin_h(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		if(tm_toboolean_s(L, 2, false))
			lua_pushustring(L, LatinBGNToHiragana(str));
		else
			lua_pushustring(L, LatinToHiragana(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_fromlatin_k(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		if (tm_toboolean_s(L, 2, false))
			lua_pushustring(L, LatinBGNToKatakana(str));
		else
			lua_pushustring(L, LatinToKatakana(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_latin_h(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		if (tm_toboolean_s(L, 2, false))
			lua_pushustring(L, HiraganaToLatinBGN(str));
		else
			lua_pushustring(L, HiraganaToLatin(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_latin_k(lua_State* L) {
	try {
		lua_Ustring str = tm_toustring(L, 1);
		if (tm_toboolean_s(L, 2, false))
			lua_pushustring(L, KatakanaToLatinBGN(str));
		else
			lua_pushustring(L, KatakanaToLatin(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int tmstring_mojibake(lua_State* L) {
	try {
		lua_Wstring str = tm_towstring(L, 1);
		lua_Sstring hex = "";
		lua_Sstring ret = "";

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
		lua_Wstring text = tm_towstring(L, 1);
		lua_Wstring ret;

		for (int i = 0; i < text.length(); i++)
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
		lua_Wstring str = tm_towstring(L, 1);
		lua_Integer length = tm_tointeger(L, 2);
		lua_Wstring ret = L"";

		if (length > str.size())
			length = str.size();

		for (int i = 0; i < length; i++)
			ret += str[i];

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
		lua_Wstring str = tm_towstring(L, 1);
		lua_Integer length = tm_tointeger(L, 2);
		lua_Wstring ret = L"";

		if (length > str.size())
			length = str.size();

		for (int i = 0; i < length; i++)
			ret = str[str.size()-(i+1)] + ret;

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
		lua_Sstring str = tm_tostring(L, 1);
		lua_Integer shift = tm_tointeger_s(L, 2, 1);
		lua_Integer pos = tm_tointeger_s(L, 3, 1);
		lua_Integer len = tm_tointeger_s(L, 4, 1);;


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
		lua_Wstring str = tm_towstring(L, 1);
		lua_Integer shift = tm_tointeger_s(L, 2, 1);
		lua_Integer pos = tm_tointeger_s(L, 3, 1);
		lua_Integer len = tm_tointeger_s(L, 4, 1);

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
		lua_Wstring str = tm_towstring(L, 1);
		lua_Wstring filter = tm_towstring_s(L, 2);

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
		lua_Wstring str = tm_towstring(L, 1);

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
		lua_Wstring str = tm_towstring(L, 1);

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
		lua_Integer len = tm_tointeger(L, 1);
		lua_Wstring str = tm_towstring(L, 2);
		lua_Integer seed;
		lua_Wstring ret = L"";

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
			seed = tm_tointeger(L, 3);
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
		lua_Wstring str = tm_towstring(L, 1);

		lua_pushwstring(L, toRoundNumber(str, false));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_anagram(lua_State* L) {
	try {
		lua_Wstring str = tm_towstring(L, 1);
		lua_Wstring ret = L"";

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNONE) {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());

			while (str.length() > 0) {
				std::uniform_int_distribution<> dist(0, str.length() - 1);
				int key = dist(engine);
				ret += str.at(key);
				str.erase(key, 1);
			}
		}
		else if (tp == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));

			while (str.length() > 0) {
				std::uniform_int_distribution<> dist(0, str.length() - 1);
				int key = dist(engine);
				ret += str.at(key);
				str.erase(key, 1);
			}
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_gsplit_aux(lua_State* L) {
	try {
		lua_Wstring str = lua_towstring(L, lua_upvalueindex(1));
		lua_Wstring pattern = lua_towstring(L, lua_upvalueindex(2));
		lua_Integer n = lua_tointeger(L, lua_upvalueindex(3));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(4));

		std::wsmatch result;
		int count = 0;

		while (std::regex_search(str, result, std::wregex(pattern)) && (count < n || n < 1)) {
			int p = result.position();

			if (count == idx) {
				lua_pushinteger(L, idx + 1);
				lua_replace(L, lua_upvalueindex(4));
				lua_pushwstring(L, str.substr(0, p));
				return 1;
			}

			str = str.substr(p + result[0].str().length());
			count++;
		}

		if (str.length() > 0 && count==idx) {
			lua_pushinteger(L, idx + 1);
			lua_replace(L, lua_upvalueindex(4));
			lua_pushwstring(L, str);
			return 1;
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

int tmstring_gsplit(lua_State* L) {
	try {
		luaL_checkstring(L, 1);
		luaL_checkstring(L, 2);

		if (lua_type(L, 3) == LUA_TNONE)
			lua_pushinteger(L, -1);
		else
			luaL_checkinteger(L, 3);

		lua_settop(L, 3);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, tmstring_gsplit_aux, 4);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_lines(lua_State* L) {
	try {
		luaL_checkstring(L, 1);
		lua_settop(L, 1);
		lua_pushstring(L, "\n");
		lua_pushinteger(L, -1);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, tmstring_gsplit_aux, 4);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_chars_aux(lua_State* L) {
	try {
		lua_Wstring str = lua_towstring(L, lua_upvalueindex(1));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(2));

		if (idx < str.length()) {
			lua_pushinteger(L, idx + 1);
			lua_replace(L, lua_upvalueindex(2));
			std::wstring c{ str.at(idx) };
			lua_pushwstring(L, c);
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_chars(lua_State* L) {
	try {
		luaL_checkstring(L, 1);
		lua_settop(L, 1);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, tmstring_chars_aux, 2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int tmstring_count(lua_State* L) {
	try {
		lua_Wstring str = tm_towstring(L, 1);
		lua_Wstring pattern = tm_towstring(L, 2);
		bool plain = tm_toboolean_s(L, 3, false);
		int count = 0;

		if (str == L"" && pattern == L"") {
			lua_pushnumber(L, 1);
			return 1;
		}

		if (pattern == L"") {
			lua_pushnumber(L, 0);
			return 1;
		}

		if (plain) {
			while (str.find(pattern) != std::wstring::npos) {
				str = str.replace(str.find(pattern), pattern.length(), L"");
				count++;
			}
		}
		else {
			std::wsmatch match;
			while (std::regex_search(str, match, std::wregex(pattern))) {
				str = str.replace(match.position(), match.length(), L"");
				count++;
			}
		}

		lua_pushnumber(L, count);
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

		lua_settablevalue(L, "number", S_NUMBER);
		lua_settablevalue(L, "hex_digits", S_HEX_DIGITS);
		lua_settablevalue(L, "alphabet", S_ALPHABET);
		lua_settablevalue(L, "small_alphabet", S_SMALL_ALPHABET);
		lua_settablevalue(L, "capital_alphabet", S_CAPITAL_ALPHABET);
		lua_settablevalue(L, "alphabet_number", S_ALPHABET_NUMBER);
		lua_settablevalue(L, "symbol", S_SYMBOL);
		lua_settablevalue(L, "ascii", S_ASCII);
		lua_settablevalue(L, "c_hiragana", S_HIRAGANA);
		lua_settablevalue(L, "c_katakana", S_KATAKANA);
		lua_settablevalue(L, "half_katakana", S_HALF_KATAKANA);
		lua_settablevalue(L, "n_hiragana", S_HIRAGANA_N);
		lua_settablevalue(L, "iroha", S_IROHA);
		lua_settablevalue(L, "pipe", S_PIPE);
		lua_settablevalue(L, "full_number", S_FULL_NUMBER);
		lua_settablevalue(L, "full_alphabet", S_FULL_ALPHABET);
		lua_settablevalue(L, "full_small_alphabet", S_FULL_SMALL_ALPHABET);
		lua_settablevalue(L, "full_capital_alphabet", S_FULL_CAPITAL_ALPHABET);
		lua_settablevalue(L, "full_alphabet_number", S_FULL_ALPHABET_NUMBER);
		lua_settablevalue(L, "quick_brown_fox", S_QUICK_BROWN_FOX);
		lua_settablevalue(L, "lorem_ipsum", S_LOREM_IPSUM);
		lua_settablevalue(L, "polano", S_POLANO);

		lua_settablevalue(L, "empty", "");
		lua_settablevalue(L, "crlf", "\r\n");

		lua_settablevalue(L, "lf", "\n");
		lua_settablevalue(L, "cr", "\r");
		lua_settablevalue(L, "ht", "\t");
		lua_settablevalue(L, "vt", "\v");
		lua_settablevalue(L, "bs", "\b");
		lua_settablevalue(L, "bel", "\a");
		lua_settablevalue(L, "nul", "\0");
		lua_settablevalue(L, "ff", "\f");

		lua_settablevalue(L, "line_feed", "\n");
		lua_settablevalue(L, "carriage_return", "\r");
		lua_settablevalue(L, "horizontal_tabulation", "\t");
		lua_settablevalue(L, "vertical_tabulation", "\v");
		lua_settablevalue(L, "backspace", "\b");
		lua_settablevalue(L, "bell", "\a");
		lua_settablevalue(L, "null", "\0");
		lua_settablevalue(L, "form_feed", "\f");

		lua_setfield(L, -2, name);
	}
}