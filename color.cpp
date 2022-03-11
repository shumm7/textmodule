#include <lua.hpp>
#include <iostream>
#include <sstream>
#include <exception>
#include <cmath>
#include <algorithm>

#include "color.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_color.h"

/*
int color_RGB(lua_State* L) {
	try {
		int val1 = 0;
		int val2 = 0;
		int val3 = 0;
		int mode = 0;

		if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) != LUA_TNUMBER) {
			val1 = lua_tointeger(L, 1);
			if (val1 < 0 || val1>0xffffff)
				return 0;
			mode = 0;
		}
		else if (lua_type(L, 1) == LUA_TSTRING) {
			val1 = HexToDec(lua_towstring(L, 1));
			if (val1 < 0 || val1>0xffffff)
				return 0;
			mode = 0;
		}
		else if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER) {
			val1 = lua_tointeger(L, 1);
			val2 = lua_tointeger(L, 2);
			val3 = lua_tointeger(L, 3);
			mode = 1;
		}
		else {
			return 0;
		}

		if (mode == 0) {
			lua_pushinteger(L, getRGBhex(val1, L'r'));
			lua_pushinteger(L, getRGBhex(val1, L'g'));
			lua_pushinteger(L, getRGBhex(val1, L'b'));

			return 3;
		}
		else if (mode == 1) {
			lua_pushwstring(L, getRGBhex(val1, val2, val3));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
	return 0;
}

int color_HSV(lua_State* L) {
	try {
		int val1 = 0;
		int val2 = 0;
		int val3 = 0;
		int mode = 0;

		if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) != LUA_TNUMBER) {
			val1 = lua_tointeger(L, 1);
			if (val1 < 0 || val1>0xffffff)
				return 0;
			mode = 0;
		}
		else if (lua_type(L, 1) == LUA_TSTRING) {
			val1 = HexToDec(lua_towstring(L, 1));
			if (val1 < 0 || val1>0xffffff)
				return 0;
			mode = 0;
		}
		else if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) == LUA_TNUMBER && lua_type(L, 3) == LUA_TNUMBER) {
			val1 = lua_tointeger(L, 1);
			val2 = lua_tointeger(L, 2);
			val3 = lua_tointeger(L, 3);
			mode = 1;
		}
		else {
			return 0;
		}

		if (mode == 0) { //col(hex) --> h, s, v
			int _r = getRGBhex(val1, L'r');
			int _g = getRGBhex(val1, L'g');
			int _b = getRGBhex(val1, L'b');

			int h = RGBtoHSV(_r, _g, _b, L'h');
			int s = RGBtoHSV(_r, _g, _b, L's');
			int v = RGBtoHSV(_r, _g, _b, L'v');

			if (h == -1 || s == -1 || v == -1)
				return 0;

			lua_pushnumber(L, h);
			lua_pushnumber(L, s);
			lua_pushnumber(L, v);
			
			return 3;
		}
		else if (mode == 1) { //h, s, v --> col(hex)
			int r = HSVtoRGB(val1, val2, val3, L'r');
			int g = HSVtoRGB(val1, val2, val3, L'g');
			int b = HSVtoRGB(val1, val2, val3, L'b');

			if (r == -1 || g == -1 || b == -1)
				return 0;

			std::wstring c = getRGBhex(r, g, b);
			if (c == L"")
				return 0;
			lua_pushwstring(L, c);
			return 1;
		}

	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
	return 0;
}

int color_convert(lua_State* L) {
	try {
		std::wstring from;
		std::wstring to;
		if (lua_type(L, 1) == LUA_TSTRING) {
			from = lua_towstring(L, 1);
		}
		else {
			return 0;
		}
		if (lua_type(L, 2) == LUA_TSTRING) {
			to = lua_towstring(L, 2);
		}
		else {
			return 0;
		}

		int R = 0;
		int G = 0;
		int B = 0;

		if (from == L"RGB" || from == L"color" || from == L"color_string") {
			int val1;
			if (lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) != LUA_TNUMBER) {
				val1 = lua_tointeger(L, 3);
				R = getRGBhex(val1, L'r');
				G = getRGBhex(val1, L'g');
				B = getRGBhex(val1, L'b');
			}
			else if (lua_type(L, 3) == LUA_TSTRING) {
				val1 = HexToDec(StrToWstr(lua_tostring(L, 3)));
				R = getRGBhex(val1, L'r');
				G = getRGBhex(val1, L'g');
				B = getRGBhex(val1, L'b');
			}
			else if (lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER && lua_type(L, 5) == LUA_TNUMBER) {
				R = lua_tointeger(L, 3);
				G = lua_tointeger(L, 4);
				B = lua_tointeger(L, 5);
			}
			else
				return 0;
		}
		else if (from == L"HSV" || from == L"HSB") {
			if (lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER && lua_type(L, 5) == LUA_TNUMBER) {
				int h = lua_tointeger(L, 3);
				int s = lua_tointeger(L, 4);
				int v = lua_tointeger(L, 5);

				R = HSVtoRGB(h, s, v, L'r');
				G = HSVtoRGB(h, s, v, L'g');
				B = HSVtoRGB(h, s, v, L'b');
			}
			else
				return 0;
		}
		else if (from == L"HSL") {
			if (lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER && lua_type(L, 5) == LUA_TNUMBER) {
				int h = lua_tointeger(L, 3);
				int s = lua_tointeger(L, 4);
				int l = lua_tointeger(L, 5);

				R = HSLtoRGB(h, s, l, L'r');
				G = HSLtoRGB(h, s, l, L'g');
				B = HSLtoRGB(h, s, l, L'b');
			}
			else
				return 0;
		}
		else if (from == L"CMYK") {
			if (lua_type(L, 3) == LUA_TNUMBER && lua_type(L, 4) == LUA_TNUMBER && lua_type(L, 5) == LUA_TNUMBER && lua_type(L, 6) == LUA_TNUMBER) {
				double c = lua_tonumber(L, 3);
				double m = lua_tonumber(L, 4);
				double y = lua_tonumber(L, 5);
				double k = lua_tonumber(L, 6);

				R = CMYKtoRGB(c, m, y, k, L'r');
				G = CMYKtoRGB(c, m, y, k, L'g');
				B = CMYKtoRGB(c, m, y, k, L'b');
			}
			else
				return 0;
		}
		else {
			return 0;
		}


		if (R < 0 || R>255)
			return 0;
		if (G < 0 || G>255)
			return 0;
		if (B < 0 || B>255)
			return 0;

		if (to == L"RGB") {
			lua_pushnumber(L, R);
			lua_pushnumber(L, G);
			lua_pushnumber(L, B);
			return 3;
		}
		else if (to == L"color") {
			std::wstring c = getRGBhex(R, G, B);
			if (c == L"")
				return 0;
			int n = HexToDec(c);
			lua_pushnumber(L, n);
		}
		else if (to == L"color_string") {
			std::wstring c = getRGBhex(R, G, B);
			if (c == L"")
				return 0;
			lua_pushstring(L, WstrToStr(c).c_str());
			return 1;
		}
		else if (to == L"HSV" || to == L"HSB") {
			int h = RGBtoHSV(R, G, B, L'h');
			int s = RGBtoHSV(R, G, B, L's');
			int v = RGBtoHSV(R, G, B, L'v');

			if (h == -1 || s == -1 || v == -1)
				return 0;
			lua_pushnumber(L, h);
			lua_pushnumber(L, s);
			lua_pushnumber(L, v);
			return 3;
		}
		else if (to == L"HSL") {
			int h = RGBtoHSL(R, G, B, L'h');
			int s = RGBtoHSL(R, G, B, L's');
			int l = RGBtoHSL(R, G, B, L'l');

			if (h == -1 || s == -1 || l == -1)
				return 0;
			lua_pushnumber(L, h);
			lua_pushnumber(L, s);
			lua_pushnumber(L, l);
			return 3;
		}
		else if (to == L"CMYK") {
			double c = RGBtoCMYK(R, G, B, L'c');
			double m = RGBtoCMYK(R, G, B, L'm');
			double y = RGBtoCMYK(R, G, B, L'y');
			double k = RGBtoCMYK(R, G, B, L'k');

			if (c == -1 || m == -1 || y == -1 || k == -1)
				return 0;
			lua_pushnumber(L, c);
			lua_pushnumber(L, m);
			lua_pushnumber(L, y);
			lua_pushnumber(L, k);
			return 4;
		}
		else {
			return 0;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
	return 0;
}
*/
void luaReg_color(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COLOR_REG);
		lua_setfield(L, -2, name);
	}
}