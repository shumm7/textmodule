#include "textmodule_lua.hpp"

#include <lua.hpp>
#include <iostream>

#include <unicode/datefmt.h>
#include <unicode/dtfmtsym.h>
#include <unicode/gregocal.h>
#include <unicode/timezone.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>
#include <unicode/dtptngen.h>
#include <unicode/dtitvfmt.h>

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <chrono>

#include <complex>
#include <Eigen/Geometry>
#include <Eigen/Dense>

#include <Windows.h>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include "textmodule_string.hpp"
#include "textmodule_math.hpp"
#include "textmodule_time.hpp"
#include "textmodule_exception.hpp"

#define abs_index(L, i)         ((i) > 0 || (i) <= LUA_REGISTRYINDEX ? (i) : lua_gettop(L) + (i) + 1)

// Wstring
lua_Wstring lua_towstring(lua_State* L, int idx) {
	return StrToWstr(lua_tostring(L, idx));
}

lua_Wstring tm_towstring(lua_State* L, int idx) {
	return StrToWstr(luaL_checkstring(L, idx));
}

lua_Wstring tm_towstring_s(lua_State* L, int idx, lua_Wstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_towstring(L, idx);
	}
}

lua_Wstring tm_towstring_s(lua_State* L, int idx) {
	return tm_towstring_s(L, idx, L"");
}

lua_Wstring lua_tolwstring(lua_State* L, int idx, size_t* len) {
	return StrToWstr(lua_tolstring(L, idx, len));
}

lua_Wstring tm_tolwstring(lua_State* L, int idx, size_t* len) {
	return StrToWstr(luaL_checklstring(L, idx, len));
}

lua_Wstring tm_tolwstring_s(lua_State* L, int idx, size_t* len, lua_Wstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tolwstring(L, idx, len);
	}
}

lua_Wstring tm_tolwstring_s(lua_State* L, int idx, size_t* len) {
	return tm_tolwstring_s(L, idx, len, L"");
}

void lua_pushwstring(lua_State* L, lua_Wstring s) {
	lua_pushstring(L, WstrToStr(s).c_str());
}

void lua_pushlwstring(lua_State* L, lua_Wstring s, size_t l) {
	lua_pushlstring(L, WstrToStr(s).c_str(), l);
}

// Sstring
lua_Sstring lua_tosstring(lua_State* L, int idx) {
	return lua_tostring(L, idx);
}

lua_Sstring tm_tosstring(lua_State* L, int idx) {
	return luaL_checkstring(L, idx);
}

lua_Sstring tm_tosstring_s(lua_State* L, int idx, lua_Sstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tostring(L, idx);
	}
}

lua_Sstring tm_tosstring_s(lua_State* L, int idx) {
	return tm_tosstring_s(L, idx, "");
}

lua_Sstring lua_tolsstring(lua_State* L, int idx, size_t* len) {
	return lua_tolstring(L, idx, len);
}

lua_Sstring tm_tolsstring(lua_State* L, int idx, size_t* len) {
	return luaL_checklstring(L, idx, len);
}

lua_Sstring tm_tolsstring_s(lua_State* L, int idx, size_t* len, lua_Sstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tolstring(L, idx, len);
	}
}

lua_Sstring tm_tolsstring_s(lua_State* L, int idx, size_t* len) {
	return tm_tolsstring_s(L, idx, len, "");
}

void lua_pushsstring(lua_State* L, lua_Sstring s) {
	lua_pushstring(L, s.c_str());
}

void lua_pushlsstring(lua_State* L, lua_Sstring s, size_t l) {
	lua_pushlstring(L, s.c_str(), l);
}

// Ustring
lua_Ustring lua_toustring(lua_State* L, int idx) {
	return StrToUstr(lua_tostring(L, idx));
}

lua_Ustring tm_toustring(lua_State* L, int idx) {
	return StrToUstr(luaL_checkstring(L, idx));
}

lua_Ustring tm_toustring_s(lua_State* L, int idx, lua_Ustring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_toustring(L, idx);
	}
}

lua_Ustring tm_toustring_s(lua_State* L, int idx) {
	return tm_toustring_s(L, idx, lua_Ustring(""));
}

void lua_pushustring(lua_State* L, lua_Ustring s) {
	lua_pushstring(L, UstrToStr(s).c_str());
}


// String
lua_String tm_tostring(lua_State* L, int idx) {
	return luaL_checkstring(L, idx);
}

lua_String tm_tostring_s(lua_State* L, int idx, lua_String def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tostring(L, idx);
	}
}

lua_String tm_tostring_s(lua_State* L, int idx) {
	return tm_tostring_s(L, idx, "");
}

lua_String tm_tolstring(lua_State* L, int idx, size_t* len) {
	return luaL_checklstring(L, idx, len);
}

lua_String tm_tolstring_s(lua_State* L, int idx, size_t* len, lua_String def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tolstring(L, idx, len);
	}
}

lua_String tm_tolstring_s(lua_State* L, int idx, size_t* len) {
	return tm_tolstring_s(L, idx, len, "");
}


// String table
lua_SJIS lua_tosjis(lua_State* L, int idx) {
	lua_SJIS ret;

	int cnt = 1;
	while(1) {
		lua_rawgeti(L, idx, cnt);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			break;
		}
		unsigned char c = tm_tonumber(L, -1);
		ret += (char)c;
		lua_pop(L, 1);

		cnt++;
	}

	return ret;
}

lua_SJIS tm_tosjis(lua_State* L, int idx) {
	luaL_argcheck(L, lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_SJIS), idx, "string (shift-jis) expected");
	return lua_tosjis(L, idx);
}

lua_SJIS tm_tosjis_s(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TSTRING)
		return lua_tostring(L, idx);
	else if (lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_SJIS))
		return tm_tosjis(L, idx);
	else {
		luaL_argerror(L, idx, "string/string (shift-jis) expected");
		return "";
	}
}

void lua_pushsjis(lua_State* L, lua_SJIS str) {
	int len = str.length();

	lua_newtable(L);
	for (int i = 0; i < len; i++) {
		lua_settablevalue(L, i+1, (unsigned char)str[i]);
	}

	luaL_getmetatable(L, TEXTMODULE_STRING_SJIS);
	lua_setmetatable(L, -2);
}

bool lua_issjis(lua_State* L, int idx) {
	return (lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_SJIS));
}

lua_UTF8 lua_toutf8(lua_State* L, int idx) {
	lua_UTF8 ret;

	int cnt = 1;
	while (1) {
		lua_rawgeti(L, idx, cnt);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			break;
		}
		unsigned char c = tm_tonumber(L, -1);
		ret += (char8_t)c;
		lua_pop(L, 1);

		cnt++;
	}

	return ret;
}

lua_UTF8 tm_toutf8(lua_State* L, int idx) {
	luaL_argcheck(L, lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF8), idx, "string (utf-8) expected");
	return lua_toutf8(L, idx);
}

lua_UTF8 tm_toutf8_s(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TSTRING)
		return StrToU8str(lua_tostring(L, idx));
	else if (lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF8))
		return tm_toutf8(L, idx);
	else {
		luaL_argerror(L, idx, "string/string (utf-8) expected");
		return u8"";
	}
}

void lua_pushutf8(lua_State* L, lua_UTF8 str) {
	int len = str.length();

	lua_newtable(L);
	for (int i = 0; i < len; i++) {
		lua_settablevalue(L, i + 1, (lua_Number)str[i]);
	}

	luaL_getmetatable(L, TEXTMODULE_STRING_UTF8);
	lua_setmetatable(L, -2);
}

bool lua_isutf8(lua_State* L, int idx) {
	return (lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF8));
}

lua_UTF16 lua_toutf16(lua_State* L, int idx) {
	lua_UTF16 ret;

	int cnt = 1;
	while (1) {
		lua_rawgeti(L, idx, cnt);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			break;
		}
		wchar_t c = tm_tonumber(L, -1);
		ret += c;
		lua_pop(L, 1);

		cnt++;
	}

	return ret;
}

lua_UTF16 tm_toutf16(lua_State* L, int idx) {
	luaL_argcheck(L, lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF16), idx, "string (utf-16) expected");
	return lua_toutf16(L, idx);
}

lua_UTF16 tm_toutf16_s(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TSTRING)
		return lua_towstring(L, 1);
	else if (lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF16))
		return tm_toutf16(L, idx);
	else {
		luaL_argerror(L, idx, "string/string (utf-16) expected");
		return L"";
	}
}

void lua_pushutf16(lua_State* L, lua_UTF16 str) {
	int len = str.length();

	lua_newtable(L);
	for (int i = 0; i < len; i++) {
		lua_settablevalue(L, i + 1, (lua_Number)str[i]);
	}

	luaL_getmetatable(L, TEXTMODULE_STRING_UTF16);
	lua_setmetatable(L, -2);
}

bool lua_isutf16(lua_State* L, int idx) {
	return (lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF16));
}

lua_UTF32 lua_toutf32(lua_State* L, int idx) {
	lua_UTF32 ret;

	int cnt = 1;
	while (1) {
		lua_rawgeti(L, idx, cnt);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			break;
		}
		unsigned int c = tm_tonumber(L, -1);
		ret += (char32_t)c;
		lua_pop(L, 1);

		cnt++;
	}

	return ret;
}

lua_UTF32 tm_toutf32(lua_State* L, int idx) {
	luaL_argcheck(L, lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF32), idx, "string (utf-32) expected");
	return lua_toutf32(L, idx);
}

lua_UTF32 tm_toutf32_s(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TSTRING)
		return StrToU32str(lua_tostring(L, 1));
	else if (lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF32))
		return tm_toutf32(L, idx);
	else {
		luaL_argerror(L, idx, "string/string (utf-32) expected");
		return U"";
	}
}

void lua_pushutf32(lua_State* L, lua_UTF32 str) {
	int len = str.length();

	lua_newtable(L);
	for (int i = 0; i < len; i++) {
		lua_settablevalue(L, i + 1, (lua_Number)str[i]);
	}

	luaL_getmetatable(L, TEXTMODULE_STRING_UTF32);
	lua_setmetatable(L, -2);
}

bool lua_isutf32(lua_State* L, int idx) {
	return (lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_UTF32));
}

lua_EUCJP lua_toeucjp(lua_State* L, int idx) {
	lua_EUCJP ret;

	int cnt = 1;
	while (1) {
		lua_rawgeti(L, idx, cnt);
		if (!lua_isnumber(L, -1)) {
			lua_pop(L, 1);
			break;
		}
		unsigned char c = tm_tonumber(L, -1);
		ret += (char)c;
		lua_pop(L, 1);

		cnt++;
	}

	return ret;
}

lua_EUCJP tm_toeucjp(lua_State* L, int idx) {
	luaL_argcheck(L, lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_EUCJP), idx, "string (euc-jp) expected");
	return lua_toeucjp(L, idx);
}

lua_EUCJP tm_toeucjp_s(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TSTRING)
		return StrToEUCstr(lua_tostring(L, 1));
	else if (lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_EUCJP))
		return tm_toeucjp(L, idx);
	else {
		luaL_argerror(L, idx, "string/string (euc-jp) expected");
		return "";
	}
}

void lua_pusheucjp(lua_State* L, lua_EUCJP str) {
	int len = str.length();

	lua_newtable(L);
	for (int i = 0; i < len; i++) {
		lua_settablevalue(L, i + 1, (unsigned char)str[i]);
	}

	luaL_getmetatable(L, TEXTMODULE_STRING_EUCJP);
	lua_setmetatable(L, -2);
}

bool lua_iseucjp(lua_State* L, int idx) {
	return (lua_istable(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_STRING_EUCJP));
}


//Number
lua_Integer tm_tointeger(lua_State* L, int idx) {
	return luaL_checkinteger(L, idx);
}

lua_Integer tm_tointeger_s(lua_State* L, int idx, lua_Integer def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tointeger(L, idx);
	}
}

lua_Integer tm_tointeger_s(lua_State* L, int idx) {
	return tm_tointeger_s(L, idx, 0);
}

lua_Number tm_todouble(lua_State* L, int idx) {
	return static_cast<double>(luaL_checknumber(L, idx));
}

lua_Number tm_tonumber(lua_State* L, int idx) {
	return tm_todouble(L, idx);
}

lua_Number tm_tonumber_s(lua_State* L, int idx, lua_Number def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tonumber(L, idx);
	}
}

lua_Number tm_tonumber_s(lua_State* L, int idx) {
	return tm_tonumber_s(L, idx, 0);
}

lua_Float tm_tofloat(lua_State* L, int idx) {
	return static_cast<float>(luaL_checknumber(L, idx));
}

lua_Unsigned tm_tounsigned(lua_State* L, int idx) {
	return static_cast<unsigned long>(luaL_checkinteger(L, idx));
}


// Bignumber
lua_Bignumber lua_tobignumber(lua_State* L, int idx) {
	return *(reinterpret_cast<lua_Bignumber*>(luaL_checkudata(L, idx, TEXTMODULE_BIGNUMBER)));
}

lua_Bignumber tm_tobignumber(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, (tp == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_BIGNUMBER)) || tp==LUA_TSTRING || tp==LUA_TNUMBER, idx, "bignumber/number expected");

	if (tp == LUA_TNUMBER) {
		lua_Bignumber c = lua_tointeger(L, idx);
		return c;
	}
	else if (tp == LUA_TSTRING) {
		lua_Bignumber s(lua_tostring(L, idx));
		return s;
	}
	else {
		return lua_tobignumber(L, idx);
	}
}

lua_Bignumber tm_tobignumber_s(lua_State* L, int idx, lua_Bignumber def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER || tp==LUA_TSTRING || (lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_BIGNUMBER)), idx, "number/bignumber/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else if(tp==LUA_TNUMBER) {
		lua_Bignumber c = lua_tonumber(L, idx);
		return c;
	}
	else if (tp == LUA_TSTRING) {
		lua_Bignumber s(lua_tostring(L, idx));
		return s;
	}
	else {
		return lua_tobignumber(L, idx);
	}
}

lua_Bignumber tm_tobignumber_s(lua_State* L, int idx) {
	return tm_tobignumber_s(L, idx, 0);
}

lua_Bignumber lua_pushbignumber(lua_State* L, lua_Bignumber value) {
	lua_Bignumber* ret = reinterpret_cast<lua_Bignumber*>(lua_newuserdata(L, sizeof(lua_Bignumber)));
	luaL_getmetatable(L, TEXTMODULE_BIGNUMBER);
	lua_setmetatable(L, -2);
	*ret = value;

	return *ret;
}

lua_Bignumber lua_pushbignumber(lua_State* L) {
	lua_pushbignumber(L, 0);
}

bool lua_isbignumber(lua_State* L, int idx) {
	return lua_isuserdata(L, idx) && luaL_checkmetatable(L, idx, TEXTMODULE_BIGNUMBER);
}


// Boolean
lua_Boolean tm_toboolean(lua_State* L, int idx) {
	if(lua_type(L, idx)!=LUA_TBOOLEAN)
		luaL_typerror(L, idx, lua_typename(L, LUA_TBOOLEAN));
	return lua_toboolean(L, idx);
}

lua_Boolean tm_toboolean_s(lua_State* L, int idx, lua_Boolean def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TBOOLEAN, idx, "boolean/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_toboolean(L, idx);
	}
}

lua_Boolean tm_toboolean_s(lua_State* L, int idx) {
	return tm_toboolean_s(L, idx, false);
}


// Table
void lua_settablevalue(lua_State* L, int key, lua_Number value) {
	lua_pushinteger(L, key);
	lua_pushnumber(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Integer value) {
	lua_pushinteger(L, key);
	lua_pushinteger(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Boolean value) {
	lua_pushinteger(L, key);
	lua_pushboolean(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_String value) {
	lua_pushinteger(L, key);
	lua_pushstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Sstring value) {
	lua_pushinteger(L, key);
	lua_pushsstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Wstring value) {
	lua_pushinteger(L, key);
	lua_pushwstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Bignumber value) {
	lua_pushinteger(L, key);
	lua_pushbignumber(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Complex value) {
	lua_pushinteger(L, key);
	lua_pushcomplex(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Number value) {
	lua_pushnumber(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Integer value) {
	lua_pushinteger(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Boolean value) {
	lua_pushboolean(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_String value) {
	lua_pushstring(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Sstring value) {
	lua_pushsstring(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Wstring value) {
	lua_pushwstring(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Bignumber value) {
	lua_pushbignumber(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Complex value) {
	lua_pushcomplex(L, value);
	lua_setfield(L, -2, key);
}

void lua_setfield(lua_State* L, int idx, lua_Sstring k) {
	lua_setfield(L, idx, k.c_str());
}

void lua_setfield(lua_State* L, int idx, lua_Wstring k) {
	lua_setfield(L, idx, WstrToStr(k));
}

bool lua_isarray(lua_State* L, int idx) {
	int h = lua_gettop(L);

	bool ret = true;
	double i = 1;

	lua_pushnil(L);
	while (lua_next(L, idx) != 0) {
		if (lua_type(L, -2) == LUA_TNUMBER) {
			double j = lua_tonumber(L, -2);
			if (j - i != 0) ret = false;
		}
		else ret = false;

		i++;
		lua_pop(L, 1);
	}

	lua_settop(L, h);
	return ret;
}

std::vector<lua_Number> lua_tosequence(lua_State* L, int idx, int start) {
	int i = start;
	std::vector<lua_Number> vec;

	if (!lua_istable(L, idx)) {
		luaL_argerror(L, idx, "table expected");
		return vec;
	}

	while (1) {
		lua_rawgeti(L, idx, i);
		if (lua_isnumber(L, -1))
			vec.push_back(lua_tonumber(L, -1));
		else
			break;
		i++;
	}

	return vec;
}

std::vector<lua_Number> lua_tosequence(lua_State* L, int idx) {
	return lua_tosequence(L, idx, 1);
}

std::vector<lua_Complex> lua_tocsequence(lua_State* L, int idx, int start) {
	int i = start;
	std::vector<lua_Complex> vec;

	if (!lua_istable(L, idx)) {
		luaL_argerror(L, idx, "table expected");
		return vec;
	}

	while (1) {
		lua_rawgeti(L, idx, i);
		if (lua_isnumber(L, -1) || lua_iscomplex(L, -1))
			vec.push_back(*lua_tocomplex(L, -1));
		else
			break;
		i++;
	}

	return vec;
}

std::vector<lua_Complex> lua_tocsequence(lua_State* L, int idx) {
	return lua_tocsequence(L, idx, 1);
}


// Clock
lua_Clock* lua_toclock(lua_State* L, int idx) {
	return reinterpret_cast<std::chrono::utc_clock::time_point*>(luaL_checkudata(L, idx, TEXTMODULE_CLOCK));
}

lua_Clock* tm_toclock(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_CLOCK), idx, "clock expected");
	return lua_toclock(L, idx);
}

lua_Clock* tm_toclock_s(lua_State* L, int idx, lua_Clock def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, (tp == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_CLOCK)) || tp == LUA_TNONE, idx, "clock/none expected");

	if (tp == LUA_TUSERDATA)
		return lua_toclock(L, idx);
	else if (tp == LUA_TNONE)
		return &def;
}

lua_Clock* tm_toclock_s(lua_State* L, int idx) {
	return tm_toclock_s(L, idx, std::chrono::utc_clock::now());
}

lua_Clock* lua_pushclock(lua_State* L, lua_Clock clock) {
	lua_Clock* ret = reinterpret_cast<lua_Clock*>(lua_newuserdata(L, sizeof(lua_Clock)));
	luaL_getmetatable(L, TEXTMODULE_CLOCK);
	lua_setmetatable(L, -2);
	*ret = clock;

	return ret;
}

lua_Clock* lua_pushclock(lua_State* L) {
	return lua_pushclock(L, std::chrono::utc_clock::now());
}

bool lua_isclock(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_CLOCK);
}


// Complex
lua_Complex* lua_tocomplex(lua_State* L, int idx) {
	return reinterpret_cast<std::complex<double>*>(luaL_checkudata(L, idx, TEXTMODULE_COMPLEX));
}

lua_Complex* tm_tocomplex(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, (tp == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_COMPLEX)) || tp == LUA_TNUMBER, idx, "number/complex expected");
	std::complex<double>* val = new std::complex<double>;

	if (tp == LUA_TUSERDATA) {
		val = lua_tocomplex(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->real(lua_tonumber(L, idx));
		val->imag(0);
	}

	return val;
}

lua_Complex* tm_tocomplex_s(lua_State* L, int idx, lua_Complex def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER || tp == LUA_TNONE, idx, "number/complex/none expected");
	std::complex<double>* val = new std::complex<double>;

	if (tp == LUA_TUSERDATA) {
		val = lua_tocomplex(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->real(lua_tonumber(L, idx));
		val->imag(0);
	}
	else if (tp == LUA_TNONE) {
		val->real(def.real());
		val->imag(def.imag());
	}

	return val;
}

lua_Complex* tm_tocomplex_s(lua_State* L, int idx) {
	return tm_tocomplex_s(L, idx, lua_Complex(0, 0));
}

lua_Complex* lua_pushcomplex(lua_State* L, double real, double imag) {
	std::complex<double>* ret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
	luaL_getmetatable(L, TEXTMODULE_COMPLEX);
	lua_setmetatable(L, -2);
	ret->real(real);
	ret->imag(imag);

	return ret;
}

lua_Complex* lua_pushcomplex(lua_State* L, lua_Complex complex) {
	return lua_pushcomplex(L, complex.real(), complex.imag());
}

lua_Complex* lua_pushcomplex(lua_State* L) {
	return lua_pushcomplex(L, 0, 0);
}

bool lua_iscomplex(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_COMPLEX);
}


// Quaternion
lua_Quaternion* lua_toquaternion(lua_State* L, int idx) {
	return reinterpret_cast<Quat*>(luaL_checkudata(L, idx, TEXTMODULE_QUATERNION));
}

lua_Quaternion* tm_toquaternion(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, (tp == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_QUATERNION)) || tp == LUA_TNUMBER, idx, "number/quaternion expected");
	Quat* val = new Quat();

	if (tp == LUA_TUSERDATA) {
		val = lua_toquaternion(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->w() = lua_tonumber(L, idx);
	}

	return val;
}

lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx, lua_Quaternion def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER || LUA_TNONE, idx, "number/quaternion/none expected");
	Quat* val = new Quat();

	if (tp == LUA_TUSERDATA) {
		val = lua_toquaternion(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->w() = lua_tonumber(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->w() = def.w();
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
	}

	return val;
}

lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx) {
	return tm_toquaternion_s(L, idx, lua_Quaternion(0, 0, 0, 0));
}

lua_Quaternion* lua_pushquaternion(lua_State* L, double w, double x, double y, double z) {
	Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
	luaL_getmetatable(L, TEXTMODULE_QUATERNION);
	lua_setmetatable(L, -2);

	ret->w() = w;
	ret->x() = x;
	ret->y() = y;
	ret->z() = z;

	return ret;
}

lua_Quaternion* lua_pushquaternion(lua_State* L, lua_Quaternion quaternion) {
	return lua_pushquaternion(L, quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z());
}

lua_Quaternion* lua_pushquaternion(lua_State* L) {
	return lua_pushquaternion(L, 0, 0, 0, 0);
}

bool lua_isquaternion(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_QUATERNION);
}

// Vector2
lua_Vector2* lua_tovector2(lua_State* L, int idx) {
	return reinterpret_cast<Vector2*>(luaL_checkudata(L, idx, TEXTMODULE_VECTOR2));
}

lua_Vector2* tm_tovector2(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR2), idx, "vector2 expected");
	return lua_tovector2(L, idx);
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx, lua_Vector2 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp==LUA_TNONE, idx, "vector2/none expected");
	Vector2* val = new Vector2();

	if (tp == LUA_TUSERDATA) {
		val = lua_tovector2(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
	}

	return val;
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx, double x, double y) {
	return tm_tovector2_s(L, idx, lua_Vector2(x, y));
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx) {
	return tm_tovector2_s(L, idx, lua_Vector2(0, 0));
}

lua_Vector2* lua_pushvector2(lua_State* L, double x, double y) {
	Vector2* ret = reinterpret_cast<Vector2*>(lua_newuserdata(L, sizeof(Vector2)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR2);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	return ret;
}

lua_Vector2* lua_pushvector2(lua_State* L, lua_Vector2 vector) {
	return lua_pushvector2(L, vector.x(), vector.y());
}

lua_Vector2* lua_pushvector2(lua_State* L) {
	return lua_pushvector2(L, 0, 0);
}

bool lua_isvector2(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR2);
}

// Vector3
lua_Vector3* lua_tovector3(lua_State* L, int idx) {
	return reinterpret_cast<Vector3*>(luaL_checkudata(L, idx, TEXTMODULE_VECTOR3));
}

lua_Vector3* tm_tovector3(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR3), idx, "vector3 expected");
	return lua_tovector3(L, idx);
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx, lua_Vector3 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "vector3/none expected");
	Vector3* val = new Vector3();

	if (tp == LUA_TUSERDATA) {
		val = lua_tovector3(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
	}

	return val;
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx, double x, double y, double z) {
	return tm_tovector3_s(L, idx, lua_Vector3(x, y, z));
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx) {
	return tm_tovector3_s(L, idx, lua_Vector3(0, 0,0));
}

lua_Vector3* lua_pushvector3(lua_State* L, double x, double y, double z) {
	Vector3* ret = reinterpret_cast<Vector3*>(lua_newuserdata(L, sizeof(Vector3)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR3);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	ret->z() = z;
	return ret;
}

lua_Vector3* lua_pushvector3(lua_State* L, lua_Vector3 vector) {
	return lua_pushvector3(L, vector.x(), vector.y(), vector.z());
}

lua_Vector3* lua_pushvector3(lua_State* L) {
	return lua_pushvector3(L, 0, 0, 0);
}

bool lua_isvector3(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR3);
}


// Vector4
lua_Vector4* lua_tovector4(lua_State* L, int idx) {
	return reinterpret_cast<Vector4*>(luaL_checkudata(L, idx, TEXTMODULE_VECTOR4));
}

lua_Vector4* tm_tovector4(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR4), idx, "vector4 expected");
	return lua_tovector4(L, idx);
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx, lua_Vector4 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "vector4/none expected");
	Vector4* val = new Vector4();

	if (tp == LUA_TUSERDATA) {
		val = lua_tovector4(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
		val->w() = def.w();
	}

	return val;
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx, double x, double y, double z, double w) {
	return tm_tovector4_s(L, idx, lua_Vector4(x,y,z,w));
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx) {
	return tm_tovector4_s(L, idx, lua_Vector4(0, 0, 0, 0));
}

lua_Vector4* lua_pushvector4(lua_State* L, double x, double y, double z, double w) {
	Vector4* ret = reinterpret_cast<Vector4*>(lua_newuserdata(L, sizeof(Vector4)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR4);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	ret->z() = z;
	ret->w() = w;
	return ret;
}

lua_Vector4* lua_pushvector4(lua_State* L, lua_Vector4 vector) {
	return lua_pushvector4(L, vector.x(), vector.y(), vector.z(), vector.w());
}

lua_Vector4* lua_pushvector4(lua_State* L) {
	return lua_pushvector4(L, 0, 0, 0, 0);
}

bool lua_isvector4(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR4);
}


// Matrix2
lua_Matrix2* lua_tomatrix2(lua_State* L, int idx) {
	return reinterpret_cast<Matrix2*>(luaL_checkudata(L, idx, TEXTMODULE_MATRIX2));
}

lua_Matrix2* tm_tomatrix2(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_MATRIX2), idx, "matrix2 expected");
	return lua_tomatrix2(L, idx);
}

lua_Matrix2* tm_tomatrix2_s(lua_State* L, int idx, lua_Matrix2 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "matrix2/none expected");
	Matrix2* val = new Matrix2();

	if (tp == LUA_TUSERDATA) {
		val = lua_tomatrix2(L, idx);
	}
	else if (tp == LUA_TNONE) {
		(*val)(0, 0) = def(0,0);
		(*val)(0, 1) = def(0,1);
		(*val)(1, 0) = def(1,0);
		(*val)(1, 1) = def(1,1);
	}

	return val;
}

lua_Matrix2* tm_tomatrix2_s(lua_State* L, int idx) {
	return tm_tomatrix2_s(L, idx, Matrix2::Zero());
}

lua_Matrix2* lua_pushmatrix2(lua_State* L, lua_Matrix2 matrix) {
	Matrix2* ret = reinterpret_cast<Matrix2*>(lua_newuserdata(L, sizeof(Matrix2)));
	luaL_getmetatable(L, TEXTMODULE_MATRIX2);
	lua_setmetatable(L, -2);

	(*ret)(0, 0) = matrix(0, 0);
	(*ret)(0, 1) = matrix(0, 1);
	(*ret)(1, 0) = matrix(1, 0);
	(*ret)(1, 1) = matrix(1, 1);
	return ret;
}

lua_Matrix2* lua_pushmatrix2(lua_State* L) {
	return lua_pushmatrix2(L, Matrix2::Zero());
}

bool lua_ismatrix2(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_MATRIX2);
}


// Matrix3
lua_Matrix3* lua_tomatrix3(lua_State* L, int idx) {
	return reinterpret_cast<Matrix3*>(luaL_checkudata(L, idx, TEXTMODULE_MATRIX3));
}

lua_Matrix3* tm_tomatrix3(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_MATRIX3), idx, "matrix3 expected");
	return lua_tomatrix3(L, idx);
}

lua_Matrix3* tm_tomatrix3_s(lua_State* L, int idx, lua_Matrix3 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "matrix3/none expected");
	Matrix3* val = new Matrix3();

	if (tp == LUA_TUSERDATA) {
		val = lua_tomatrix3(L, idx);
	}
	else if (tp == LUA_TNONE) {
		(*val)(0, 0) = def(0, 0);
		(*val)(0, 1) = def(0, 1);
		(*val)(0, 2) = def(0, 2);
		(*val)(1, 0) = def(1, 0);
		(*val)(1, 1) = def(1, 1);
		(*val)(1, 2) = def(1, 2);
		(*val)(2, 0) = def(2, 0);
		(*val)(2, 1) = def(2, 1);
		(*val)(2, 2) = def(2, 2);
	}

	return val;
}

lua_Matrix3* tm_tomatrix3_s(lua_State* L, int idx) {
	return tm_tomatrix3_s(L, idx, Matrix3::Zero());
}

lua_Matrix3* lua_pushmatrix3(lua_State* L, lua_Matrix3 matrix) {
	Matrix3* ret = reinterpret_cast<Matrix3*>(lua_newuserdata(L, sizeof(Matrix3)));
	luaL_getmetatable(L, TEXTMODULE_MATRIX3);
	lua_setmetatable(L, -2);

	(*ret)(0, 0) = matrix(0, 0);
	(*ret)(0, 1) = matrix(0, 1);
	(*ret)(0, 2) = matrix(0, 2);
	(*ret)(1, 0) = matrix(1, 0);
	(*ret)(1, 1) = matrix(1, 1);
	(*ret)(1, 2) = matrix(1, 2);
	(*ret)(2, 0) = matrix(2, 0);
	(*ret)(2, 1) = matrix(2, 1);
	(*ret)(2, 2) = matrix(2, 2);
	return ret;
}

lua_Matrix3* lua_pushmatrix3(lua_State* L) {
	return lua_pushmatrix3(L, Matrix3::Zero());
}

bool lua_ismatrix3(lua_State* L, int idx) {
	return lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_MATRIX3);
}


// Color
lua_Color* lua_tocolor(lua_State* L, int idx) {
	return reinterpret_cast<lua_Color*>(luaL_checkudata(L, idx, TEXTMODULE_COLOR));
}

lua_Color* tm_tocolor(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_COLOR), idx, "color expected");
	return lua_tocolor(L, idx);
}

lua_Color* tm_tocolor_s(lua_State* L, int idx, lua_Color def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "color/none expected");
	lua_Color* val = new lua_Color;

	if (tp == LUA_TUSERDATA) {
		val = lua_tocolor(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->r = def.r;
		val->g = def.g;
		val->b = def.b;
		val->a = def.a;
	}

	return val;
}

lua_Color* tm_tocolor_s(lua_State* L, int idx, double r, double g, double b, double a) {
	return tm_tocolor_s(L, idx, lua_Color{ r,g,b,a });
}

lua_Color* tm_tocolor_s(lua_State* L, int idx) {
	return tm_tocolor_s(L, idx, 0, 0, 0, 0);
}

lua_Color* lua_pushcolor(lua_State* L, double r, double g, double b, double a) {
	lua_Color* ret = reinterpret_cast<lua_Color*>(lua_newuserdata(L, sizeof(lua_Color)));
	luaL_getmetatable(L, TEXTMODULE_COLOR);
	lua_setmetatable(L, -2);

	ret->r = r;
	ret->g = g;
	ret->b = b;
	ret->a = a;
	return ret;
}

lua_Color* lua_pushcolor(lua_State* L, lua_Color def) {
	return lua_pushcolor(L, def.r, def.g, def.b, def.a);
}

lua_Color* lua_pushcolor(lua_State* L, lua_Vector4 def) {
	return lua_pushcolor(L, def.x(), def.y(), def.z(), def.w());
}

lua_Color* lua_pushcolor(lua_State* L) {
	return lua_pushcolor(L, 0, 0, 0, 0);
}

//Pixel
lua_Pixel* lua_topixel(lua_State* L, int idx) {
	return reinterpret_cast<lua_Pixel*>(luaL_checkudata(L, idx, TEXTMODULE_PIXEL));
}

lua_Pixel* tm_topixel(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_PIXEL), idx, "pixel expected");
	return lua_topixel(L, idx);
}

lua_Pixel* tm_topixel_s(lua_State* L, int idx, lua_Pixel def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "pixel/none expected");
	lua_Pixel* val = new lua_Pixel;

	if (tp == LUA_TUSERDATA) {
		val = lua_topixel(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->r = def.r;
		val->g = def.g;
		val->b = def.b;
		val->a = def.a;
	}

	return val;
}

lua_Pixel* tm_topixel_s(lua_State* L, int idx, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	return tm_topixel_s(L, idx, lua_Pixel{ r,g,b,a });
}

lua_Pixel* tm_topixel_s(lua_State* L, int idx, double r, double g, double b, double a) {
	return tm_topixel_s(L, idx, (unsigned char)clamp_s(r, 0, 255), (unsigned char)clamp_s(g, 0, 255), (unsigned char)clamp_s(b, 0, 255), (unsigned char)clamp_s(a, 0, 255));
}

lua_Pixel* tm_topixel_s(lua_State* L, int idx) {
	return tm_topixel_s(L, idx, 0.0, 0.0, 0.0, 0.0);
}

lua_Pixel* lua_pushpixel(lua_State* L, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	lua_Pixel* ret = reinterpret_cast<lua_Pixel*>(lua_newuserdata(L, sizeof(lua_Pixel)));
	luaL_getmetatable(L, TEXTMODULE_PIXEL);
	lua_setmetatable(L, -2);

	ret->r = r;
	ret->g = g;
	ret->b = b;
	ret->a = a;
	return ret;
}

lua_Pixel* lua_pushpixel(lua_State* L, double r, double g, double b, double a) {
	return lua_pushpixel(L, (unsigned char)clamp_s(r, 0, 255), (unsigned char)clamp_s(g, 0, 255), (unsigned char)clamp_s(b, 0, 255), (unsigned char)clamp_s(a, 0, 255));
}

lua_Pixel* lua_pushpixel(lua_State* L, lua_Pixel def) {
	return lua_pushpixel(L, def.r, def.g, def.b, def.a);
}

lua_Pixel* lua_pushpixel(lua_State* L) {
	return lua_pushpixel(L, 0.0, 0.0, 0.0, 0.0);
}

// Image
lua_Image* lua_toimage(lua_State* L, int idx) {
	return reinterpret_cast<lua_Image*>(luaL_checkudata(L, idx, TEXTMODULE_IMAGE));
}

lua_Image* tm_toimage(lua_State* L, int idx) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_IMAGE), idx, "image expected");
	return lua_toimage(L, idx);
}

lua_Image* lua_convertcache(lua_State* L, int idx) {
	lua_Image* val = reinterpret_cast<lua_Image*>(lua_touserdata(L, idx));
	luaL_getmetatable(L, TEXTMODULE_IMAGE);
	lua_setmetatable(L, idx);

	return val;
}

// Misc
bool luaL_checkmetatable(lua_State* L, int ud, const char* tname) {
	if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
		lua_getfield(L, LUA_REGISTRYINDEX, tname);  /* get correct metatable */
		if (lua_rawequal(L, -1, -2)) {  /* does it have the correct mt? */
			lua_pop(L, 2);
			return true;
		}
		lua_pop(L, 2);
	}
	return false;
}

void luaL_newmetatable(lua_State* L, const char* name, const luaL_Reg* methods) {
	luaL_newmetatable(L, name); //add metatable
	luaL_register(L, NULL, methods);

	lua_pushstring(L, "__index"); //add __index
	lua_newtable(L);
	luaL_register(L, NULL, methods);
	lua_settable(L, -3);

	lua_pop(L, 1); //remove metatable
}

const char* tm_convtostring(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TNONE)
		return "none";
	else {
		if (luaL_callmeta(L, idx, "__tostring")) {
			const char* s = lua_tostring(L, -1);
			lua_pop(L, 1);
			return s;
		}
		const char* n = "";
		switch (lua_type(L, idx)) {
		case LUA_TSTRING:
			return lua_tostring(L, idx);
		case LUA_TNUMBER:
			lua_pushvalue(L, idx);
			n = lua_tostring(L, -1);
			lua_pop(L, 1);
			return n;
		case LUA_TBOOLEAN:
			return (lua_toboolean(L, idx) ? "true" : "false");
		case LUA_TNIL:
			return "nil";
		default:
			fmt::dynamic_format_arg_store<fmt::format_context> store;
			store.push_back(luaL_typename(L, idx));
			store.push_back(lua_topointer(L, idx));
			lua_Sstring _f = fmt::vformat("{0:s}: {1:p}", store);
			const char* f = _f.c_str();
			return f;
		}
	}
}

const char* tm_typename(lua_State* L, int idx) {
	int n = lua_gettop(L);

	if (luaL_callmeta(L, idx, "__type")) {
		if (lua_type(L, -(lua_gettop(L) - n)) == LUA_TSTRING) {
			const char* c = lua_tostring(L, -(lua_gettop(L) - n));
			lua_pop(L, lua_gettop(L) - n);
			return c;
		}
		else {
			lua_pop(L, lua_gettop(L) - n);
			luaL_argerror(L, idx, "invalid argument type of name");
			return "";
		}
	}

	return lua_typename(L, lua_type(L, idx));
}

void lua_printstack(lua_State* L)
{
	int stackSize = lua_gettop(L);

	for (int i = stackSize; i >= 1; i--) {
		int type = lua_type(L, i);
		std::cout << WstrToStr(tostring_n(i)) << "\t" << lua_typename(L, type) << "\t" << tm_convtostring(L, i) << std::endl;
	}
}

int lua_pushtmstruct(lua_State* L, std::tm* tmstruct) {
	struct tm tm = *tmstruct;

	lua_newtable(L);
	lua_pushinteger(L, tm.tm_year + 1900);
	lua_setfield(L, -2, "year");
	lua_pushinteger(L, tm.tm_mon + 1);
	lua_setfield(L, -2, "month");
	lua_pushinteger(L, tm.tm_mday);
	lua_setfield(L, -2, "day");
	lua_pushinteger(L, tm.tm_hour);
	lua_setfield(L, -2, "hour");
	lua_pushinteger(L, tm.tm_min);
	lua_setfield(L, -2, "min");
	lua_pushinteger(L, tm.tm_sec);
	lua_setfield(L, -2, "sec");
	lua_pushinteger(L, tm.tm_wday + 1);
	lua_setfield(L, -2, "wday");
	lua_pushinteger(L, tm.tm_yday + 1);
	lua_setfield(L, -2, "yday");
	lua_pushinteger(L, tm.tm_isdst);
	lua_setfield(L, -2, "isdst");

	return 1;
}

void lua_totmstruct(lua_State* L, int idx, std::tm* out) {
	luaL_checktype(L, idx, LUA_TTABLE);

	(*out).tm_isdst = time_tm_getfield(L, idx, "isdst", false);
	(*out).tm_year = time_tm_getfield(L, idx, "year", -1) - 1900;
	(*out).tm_mon = time_tm_getfield(L, idx, "month", -1) - 1;
	(*out).tm_mday = time_tm_getfield(L, idx, "day", -1);
	(*out).tm_hour = time_tm_getfield(L, idx, "hour", 12);
	(*out).tm_min = time_tm_getfield(L, idx, "min", 0);
	(*out).tm_sec = time_tm_getfield(L, idx, "sec", 0);
}

bool tm_callmeta(lua_State* L, int obj, const char* event) {
	obj = abs_index(L, obj);
	if (!luaL_getmetafield(L, obj, event))  /* no metafield? */
		return false;
	lua_pushvalue(L, obj);
	lua_call(L, 1, 1);
	return true;
}

bool tm_callmetan(lua_State* L, int obj, const char* event, int nargs, int namount) {
	/* argn: number of arguments (including itself) */
	if (nargs < 1)
		return false;
	obj = abs_index(L, obj);

	bool f;
	for (int i = 0; i < nargs; i++) {
		if (lua_type(L, obj + i) != LUA_TNONE) {
			if (luaL_getmetafield(L, obj + i, event)) {
				f = true;
				break;
			}
		}
	}

	if (!f) return false; /* no metafield? */
	if (lua_type(L, -1) != LUA_TFUNCTION) return false;

	int p = nargs;
	for (int i = 0; i < p; i++) {
		if (lua_type(L, obj + i) != LUA_TNONE)
			lua_pushvalue(L, obj + i);
	}
	lua_call(L, nargs, namount);
	return true;
}

bool tm_callmetan(lua_State* L, int obj, const char* event, int nargs) {
	return tm_callmetan(L, obj, event, nargs, LUA_MULTRET);
}

bool tm_callmetan(lua_State* L, int obj, const char* event) {
	int n = lua_gettop(L);
	return tm_callmetan(L, obj, event, n);
}

void lua_pushsomenil(lua_State* L, int amount) {
	for (int i = 0; i < amount; i++)
		lua_pushnil(L);
}

void lua_formatargs_store(lua_State* L, fmt::dynamic_format_arg_store<fmt::format_context>* ret, int startIdx, int endIdx) {
	for(int i=startIdx; i<=endIdx; i++){
		int tp = lua_type(L, i);

		if (tp == LUA_TNUMBER)
			ret->push_back(lua_tonumber(L, i));
		else if (tp == LUA_TBOOLEAN)
			ret->push_back(lua_toboolean(L, i));
		else if (tp == LUA_TSTRING)
			ret->push_back(lua_tostring(L, i));
		else if (tp == LUA_TNIL)
			ret->push_back("nil");
		else if (tp == LUA_TNONE)
			break;
		else if (tp == LUA_TUSERDATA) {
			if (lua_isclock(L, i)) {
				std::tm tm;
				__time64_t time_t = std::chrono::system_clock::to_time_t(std::chrono::utc_clock::to_sys(*tm_toclock(L, i)));
				_gmtime64_s(&tm, &time_t);
				ret->push_back(tm);
			}
			else
				ret->push_back(lua_topointer(L, i));
		}
		else
			ret->push_back(lua_topointer(L, i));

		i++;
	}
}


// Json utility
lua_Json tm_jsonparse(lua_Sstring str) {
	return lua_Json::parse(str);
}

lua_Sstring tm_jsondump(lua_Json* j) {
	return (*j).dump();
}

lua_Sstring tm_jsondump(lua_Json* j, int l) {
	return (*j).dump(l);
}

lua_Json tm_tabletojsonarray(lua_State* L, int idx) {
	lua_Json ret = lua_Json::array();

	int t;
	lua_Number num;

	if (!lua_istable(L, idx)) {
		luaL_argerror(L, idx, "table expected");
		return ret;
	}

	lua_pushnil(L);
	while (lua_next(L, idx) != 0) {
		switch (lua_type(L, -1)) {
		case LUA_TNIL:
		case LUA_TNONE:
			ret.push_back(nullptr);
			break;
		case LUA_TNUMBER:
			num = lua_tonumber(L, -1);
			if(isinteger(num))
				ret.push_back((int)num);
			else
				ret.push_back(num);
			break;
		case LUA_TSTRING:
			ret.push_back(lua_tosstring(L, -1));
			break;
		case LUA_TBOOLEAN:
			ret.push_back(lua_toboolean(L, -1));
			break;
		case LUA_TTABLE:
			t = lua_gettop(L);
			if (lua_isarray(L, t)) {
				ret.push_back(tm_tabletojsonarray(L, t));
			}
			else {
				ret.push_back(tm_tabletojson(L, t));
			}
			break;
		default:
			luaL_argerror(L, -1, "invalid argument type");
			break;
		}

		lua_pop(L, 1);
	}

	return ret;
}

lua_Json tm_tabletojson(lua_State* L, int idx) {
	lua_Json ret = lua_Json::object();
	int t;
	lua_Number num;

	if (!lua_istable(L, idx)) {
		luaL_argerror(L, idx, "table expected");
		return ret;
	}

	if (lua_isarray(L, idx)) {
		return tm_tabletojsonarray(L, idx);
	}

	lua_pushnil(L);
	while (lua_next(L, idx) != 0) {
		std::string key = tm_convtostring(L, -2);
		switch (lua_type(L, -1)) {
		case LUA_TNIL:
		case LUA_TNONE:
			ret.emplace(key, nullptr);
			break;
		case LUA_TNUMBER:
			num = lua_tonumber(L, -1);
			if (isinteger(num))
				ret.emplace(key, (int)num);
			else
				ret.emplace(key, num);
			break;
		case LUA_TSTRING:
			ret.emplace(key, lua_tosstring(L, -1));
			break;
		case LUA_TBOOLEAN:
			ret.emplace(key, lua_toboolean(L, -1));
			break;
		case LUA_TTABLE:
			t = lua_gettop(L);
			if (lua_isarray(L, t))
				ret.emplace(key, tm_tabletojsonarray(L, t));
			else
				ret.emplace(key, tm_tabletojson(L, t));
			break;
		default:
			luaL_argerror(L, -1, "invalid argument type");
			break;
		}

		lua_pop(L, 1);
	}

	return ret;
}

void tm_pushjson(lua_State* L, lua_Json* j) {
	lua_Json x = *j;

	if (x.is_null()) {
		lua_pushnil(L);
	}
	else if (x.is_boolean()) {
		lua_pushboolean(L, x.get<lua_Boolean>());
	}
	else if (x.is_number()) {
		lua_pushnumber(L, x.get<lua_Number>());
	}
	else if (x.is_string()) {
		lua_pushsstring(L, x.get<lua_Sstring>());
	}
	else if (x.is_object()) {
		lua_newtable(L);
		for (auto& el_o : x.items()) {
			tm_pushjson(L, &el_o.value());
			lua_setfield(L, -2, el_o.key());
		}
	}
	else if (x.is_array()) {
		lua_newtable(L);
		int key = 0;
		for (auto& el_a : x) {
			lua_pushinteger(L, key + 1);
			tm_pushjson(L, &el_a);
			lua_settable(L, -3);
			key++;
		}
	}
}

lua_Json tm_tojson(lua_State* L, int idx) {
	int tp = lua_type(L, 1);
	luaL_argcheck(L, tp == LUA_TSTRING || tp==LUA_TTABLE || tp==LUA_TNONE, 1, "string/table/none expected");

	if (tp == LUA_TSTRING)
		return tm_jsonparse(lua_tosstring(L, 1));
	else if (tp == LUA_TTABLE)
		return tm_tabletojson(L, idx);
	else
		return tm_jsonparse("{}");
}