#include <lua.hpp>
#include <iostream>
#include <sstream>
#include <exception>
#include <cmath>
#include <algorithm>

#include "color.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

std::wstring lstr(std::wstring str, int length, wchar_t c) {
	if (str.length() >= length)
		return str;
	return std::wstring(length - str.length(), c) + str;
}

std::wstring getRGBhex(int r, int g, int b) {
	if (r < 0 || r>255)
		return L"";
	if (g < 0 || g>255)
		return L"";
	if (b < 0 || b>255)
		return L"";

	std::wstring hex = L"0x";
	hex += lstr(DecToHex(r).substr(2), 2, L'0');
	hex += lstr(DecToHex(g).substr(2), 2, L'0');
	hex += lstr(DecToHex(b).substr(2), 2, L'0');
	return hex;
}
int getRGBhex(int num, wchar_t mode) {
	std::wstring hex = DecToHex(num);
	if (hex.substr(0, 2) == L"0x")
		hex = hex.substr(2);

	if (hex.length() < 6)
		hex = std::wstring(6 - hex.length(), L'0') + hex;
	else if (hex.length() > 6)
		return 0;


	switch (mode) {
	case L'r':
	case L'R':
		return HexToDec(hex.substr(0, 2));
	case L'g':
	case L'G':
		return HexToDec(hex.substr(2, 2));
	case L'b':
	case L'B':
		return HexToDec(hex.substr(4, 2));
	default:
		return -1;
	}
}


double hx(int x, double max, double min) {
	double kx = (double)x;
	return kx / 60.0 * (max - min) + min;
}

int RGBtoHSV(int _r, int _g, int _b, wchar_t mode) {
	if (_r < 0 || _r>255)
		return -1;
	if (_g < 0 || _g>255)
		return -1;
	if (_b < 0 || _b>255)
		return -1;

	double h = 0;
	double s = 0;
	double v = 0;

	double r = _r;
	double g = _g;
	double b = _b;
	double max = std::max({ r, g, b });
	double min = std::min({ r, g, b });

	if (r == g && g == b) {
		h = 0;
	}
	else if (max == r) {
		h = 60 * ((g - b) / (max - min));
	}
	else if (max == g) {
		h = 60 * ((b - r) / (max - min)) + 120.0;
	}
	else if (max == b) {
		h = 60 * ((r - g) / (max - min)) + 240.0;
	}

	if (h < 0)
		h += 360;

	s = (max - min) / max * 100;
	v = max / 255.0 * 100;

	switch (mode) {
	case L'h':
	case L'H':
		return (int)round(h);
	case L's':
	case L'S':
		return (int)round(s);
	case L'v':
	case L'V':
		return (int)round(v);
	default:
		return -1;
	}

}
int HSVtoRGB(int _h, int _s, int _v, wchar_t mode) {
	if (_h < 0 || _h>360)
		return -1;
	if (_s < 0 || _s>100)
		return -1;
	if (_v < 0 || _v>100)
		return -1;
	if (_h == 360)
		_h = 0;

	double r = 0;
	double g = 0;
	double b = 0;

	double hd = ((double)_h / 60.0);
	hd = hd - std::floor(hd);// h/60ÇÃè¨êîïîï™ÇéÊìæ
	double sd = (double)_s / 100.0;
	double vd = (double)_v / 100.0;

	double ka = vd * 255;
	double kb = vd * (1 - sd) * 255.0;
	double kc = vd * (1 - sd * hd) * 255.0;
	double kd = vd * (1 - sd * (1 - hd)) * 255.0;

	if (_s == 0) {
		r = ka; g = ka; b = ka;
	}
	else if (0 <= _h && _h < 60) {
		r = ka; g = kd; b = kb;
	}
	else if (60 <= _h && _h < 120) {
		r = kc; g = ka; b = kb;
	}
	else if (120 <= _h && _h < 180) {
		r = kb; g = ka; b = kd;
	}
	else if (180 <= _h && _h < 240) {
		r = kb; g = kc; b = ka;
	}
	else if (240 <= _h && _h < 300) {
		r = kd; g = kb; b = ka;
	}
	else if (300 <= _h && _h < 360) {
		r = ka; g = kb; b = kc;
	}

	switch (mode) {
	case L'r':
	case L'R':
		return (int)round(r);
	case L'g':
	case L'G':
		return (int)round(g);
	case L'b':
	case L'B':
		return (int)round(b);
	default:
		return -1;
	}
}

int RGBtoHSL(int _r, int _g, int _b, wchar_t mode) {
	if (_r < 0 || _r>255)
		return -1;
	if (_g < 0 || _g>255)
		return -1;
	if (_b < 0 || _b>255)
		return -1;

	double h = 0;
	double s = 0;
	double l = 0;

	double r = _r;
	double g = _g;
	double b = _b;
	double max = std::max({ r, g, b });
	double min = std::min({ r, g, b });

	if (r == g && g == b) {
		h = 0;
	}
	else if (max == r) {
		h = 60 * ((g - b) / (max - min));
	}
	else if (max == g) {
		h = 60 * ((b - r) / (max - min)) + 120.0;
	}
	else if (max == b) {
		h = 60 * ((r - g) / (max - min)) + 240.0;
	}

	if (h < 0) {
		h += 360;
	}

	l = (max + min) / 2.0 * (100.0 / 255.0);

	if (r == 255 && g == 255 && b == 255) {
		s = 0;
	} 
	else if (0 <= l && l <= 50) {
		s = (max - min) / (max + min) * 100.0;
	}
	else if (50 < l && l <= 100) {
		s = (max - min) / (510.0 - (max + min)) * 100.0;
	}

	switch (mode) {
	case L'h':
	case L'H':
		return (int)round(h);
	case L's':
	case L'S':
		return (int)round(s);
	case L'l':
	case L'L':
		return (int)round(l);
	default:
		return -1;
	}
}
int HSLtoRGB(int _h, int _s, int _l, wchar_t mode) {
	if (_h < 0 || _h>360)
		return -1;
	if (_s < 0 || _s>100)
		return -1;
	if (_l < 0 || _l>100)
		return -1;
	if (_h == 360)
		_h = 0;

	double r = 0;
	double g = 0;
	double b = 0;

	double ld = 0;
	if (0 <= _l && _l < 50)
		ld = _l;
	else if (50 <= _l && _l <= 100)
		ld = static_cast<double>(100 - _l);

	double max = 2.55 * (_l + ld * (double)_s / 100.0);
	double min = 2.55 * (_l - ld * (double)_s / 100.0);

	if (0 <= _h && _h < 60) {
		r = max; g = hx(_h, max, min); b = min;
	}
	else if (60 <= _h && _h < 120) {
		r = hx(120 - _h, max, min); g = max; b = min;
	}
	else if (120 <= _h && _h < 180) {
		r = min; g = max; b = hx(_h - 120, max, min);
	}
	else if (180 <= _h && _h < 240) {
		r = min; g = hx(240 - _h, max, min); b = max;
	}
	else if (240 <= _h && _h < 300) {
		r = hx(_h - 240, max, min); g = min; b = max;
	}
	else if (300 <= _h && _h < 360) {
		r = max; g = min; b = hx(360 - _h, max, min);
	}

	switch (mode) {
	case L'r':
	case L'R':
		return (int)round(r);
	case L'g':
	case L'G':
		return (int)round(g);
	case L'b':
	case L'B':
		return (int)round(b);
	default:
		return -1;
	}
}

int CMYKtoRGB(double c, double m, double y, double k, wchar_t mode) {
	if (c < 0 || c>1)
		return -1;
	if (m < 0 || m>1)
		return -1;
	if (y < 0 || y>1)
		return -1;
	if (k < 0 || k>1)
		return -1;
	double r = 255 * (1 - c) * (1 - k);
	double g = 255 * (1 - m) * (1 - k);
	double b = 255 * (1 - y) * (1 - k);

	switch (mode) {
	case L'r':
	case L'R':
		return (int)round(r);
	case L'g':
	case L'G':
		return (int)round(g);
	case L'b':
	case L'B':
		return (int)round(b);
	default:
		return -1;
	}
}
double RGBtoCMYK(int _r, int _g, int _b, wchar_t mode) {
	if (_r < 0 || _r>255)
		return -1;
	if (_g < 0 || _g>255)
		return -1;
	if (_b < 0 || _b>255)
		return -1;

	double c = 0;
	double m = 0;
	double y = 0;
	double k = 0;

	double r = _r;
	double g = _g;
	double b = _b;
	r = r / 255.0;
	g = g / 255.0;
	b = b / 255.0;
	double max = std::max({ r, g, b });

	k = (1 - max);
	if (k == 1) {
		c = 0; m = 0; y = 0;
	}
	else{
		c = (1 - r - k) / (1 - k);
		m = (1 - g - k) / (1 - k);
		y = (1 - b - k) / (1 - k);
	}

	switch (mode) {
		case L'c':
		case L'C':
			return c;
		case L'm':
		case L'M':
			return m;
		case L'y':
		case L'Y':
			return y;
		case L'k':
		case L'K':
			return k;
		default:
			return -1;
	}
}


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

void luaReg_color(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COLOR_REG);
		lua_setfield(L, -2, name);
	}
}