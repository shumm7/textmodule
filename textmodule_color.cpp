#include <iostream>
#include <sstream>
#include <exception>
#include <cmath>
#include <algorithm>

#include "textmodule_color.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "textmodule_math.h"

#define EXCEPTION_OUT_OF_RANGE "the value is out of range"
#define EXCEPTION_OUT_OF_RANGE_HEX "the value is out of range (0x000000 to 0xffffff)"
#define EXCEPTION_OUT_OF_RANGE_RGB "the value is out of range (0x00 to 0xff)"
#define EXCEPTION_OUT_OF_RANGE_SV "the value is out of range (0 to 100)"

float check_value(float n, float min, float max, const char* message) {
	if (n < min || n>max) {
		throw std::invalid_argument(message);
	}
	return n;
}
int check_rgbvalue(int n) {
	return check_value(n, 0, 255, EXCEPTION_OUT_OF_RANGE_RGB);
}
int check_hsv_hvalue(int n) {
	if (n < 0) {
		while (n < 0)
			n += 360;
	}
	else if (n > 360) {
		while (n > 360)
			n -= 360;
	}
	return n;
}
int check_hsv_svvalue(int n) {
	return check_value(n, 0, 100, EXCEPTION_OUT_OF_RANGE_SV);
}

std::wstring lstr(std::wstring str, int length, wchar_t c) {
	if (str.length() >= length)
		return str;
	return std::wstring(length - str.length(), c) + str;
}

std::wstring getRGBhex(RGB* val) {
	int r = check_rgbvalue(val->r);
	int g = check_rgbvalue(val->g);
	int b = check_rgbvalue(val->b);

	std::wstring hex = L"0x";
	hex += lstr(DecToHex(r).substr(2), 2, L'0');
	hex += lstr(DecToHex(g).substr(2), 2, L'0');
	hex += lstr(DecToHex(b).substr(2), 2, L'0');
	return hex;
}
void getRGBhex(int num, RGB* ret) {
	std::wstring hex = DecToHex(num);
	if (hex.substr(0, 2) == L"0x")
		hex = hex.substr(2);

	if (hex.length() < 6)
		hex = std::wstring(6 - hex.length(), L'0') + hex;
	else if (hex.length() > 6)
		throw std::invalid_argument(EXCEPTION_OUT_OF_RANGE_HEX);

	ret->r = check_rgbvalue(HexToDec(hex.substr(0, 2)));
	ret->g = check_rgbvalue(HexToDec(hex.substr(2, 2)));
	ret->b = check_rgbvalue(HexToDec(hex.substr(4, 2)));
}


double hx(int x, double max, double min) {
	double kx = (double)x;
	return kx / 60.0 * (max - min) + min;
}

void RGBtoHSV(RGB* val, HSV* ret) {
	double r = check_rgbvalue(val->r);
	double g = check_rgbvalue(val->g);
	double b = check_rgbvalue(val->b);

	double h = 0;
	double s = 0;
	double v = 0;
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

	while (h < 0) {
		h += 360;
	}

	s = (max - min) / max * 100;
	v = max / 255.0 * 100;

	ret->h = check_hsv_hvalue(round(h));
	ret->s = check_hsv_hvalue(round(s));
	ret->v = check_hsv_hvalue(round(v));
}
void HSVtoRGB(HSV* val, RGB* ret) {
	double h = check_hsv_hvalue(val->h);
	double s = check_hsv_svvalue(val->s);
	double v = check_hsv_svvalue(val->v);

	double r = 0;
	double g = 0;
	double b = 0;

	double hd = (h / 60.0);
	hd = hd - std::floor(hd);// h/60ÇÃè¨êîïîï™ÇéÊìæ
	double sd = s / 100.0;
	double vd = v / 100.0;

	double ka = vd * 255;
	double kb = vd * (1 - sd) * 255.0;
	double kc = vd * (1 - sd * hd) * 255.0;
	double kd = vd * (1 - sd * (1 - hd)) * 255.0;

	if (s == 0) {
		r = ka; g = ka; b = ka;
	}
	else if (0 <= h && h < 60) {
		r = ka; g = kd; b = kb;
	}
	else if (60 <= h && h < 120) {
		r = kc; g = ka; b = kb;
	}
	else if (120 <= h && h < 180) {
		r = kb; g = ka; b = kd;
	}
	else if (180 <= h && h < 240) {
		r = kb; g = kc; b = ka;
	}
	else if (240 <= h && h < 300) {
		r = kd; g = kb; b = ka;
	}
	else if (300 <= h && h < 360) {
		r = ka; g = kb; b = kc;
	}

	ret->r = check_rgbvalue(r);
	ret->g = check_rgbvalue(g);
	ret->b = check_rgbvalue(b);
}

void RGBtoHSL(RGB* val, HSL* ret) {
	double r = check_rgbvalue(val->r);
	double g = check_rgbvalue(val->g);
	double b = check_rgbvalue(val->b);

	double h = 0;
	double s = 0;
	double l = 0;

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

	ret->h = check_hsv_hvalue(round(h));
	ret->s = check_hsv_hvalue(round(s));
	ret->l = check_hsv_hvalue(round(l));
}
void HSLtoRGB(HSL* val, RGB* ret) {
	double h = check_hsv_hvalue(val->h);
	double s = check_hsv_svvalue(val->s);
	double l = check_hsv_svvalue(val->l);

	double r = 0;
	double g = 0;
	double b = 0;

	double ld = 0;
	if (0 <= l && l < 50)
		ld = l;
	else if (50 <= l && l <= 100)
		ld = 100.0 - l;

	double max = 2.55 * (l + ld * s / 100.0);
	double min = 2.55 * (l - ld * s / 100.0);

	if (0 <= h && h < 60) {
		r = max; g = hx(h, max, min); b = min;
	}
	else if (60 <= h && h < 120) {
		r = hx(120.0 - h, max, min); g = max; b = min;
	}
	else if (120 <= h && h < 180) {
		r = min; g = max; b = hx(h - 120.0, max, min);
	}
	else if (180 <= h && h < 240) {
		r = min; g = hx(240.0 - h, max, min); b = max;
	}
	else if (240 <= h && h < 300) {
		r = hx(h - 240.0, max, min); g = min; b = max;
	}
	else if (300 <= h && h < 360) {
		r = max; g = min; b = hx(360.0 - h, max, min);
	}

	ret->r = check_rgbvalue(r);
	ret->g = check_rgbvalue(g);
	ret->b = check_rgbvalue(b);
}

void RGBtoCMYK(RGB* val, CMYK* ret) {
	double r = check_rgbvalue(val->r);
	double g = check_rgbvalue(val->g);
	double b = check_rgbvalue(val->b);

	double c = 0;
	double m = 0;
	double y = 0;
	double k = 0;

	double max = std::max({ r, g, b }) / 255.0;

	k = (1 - max);
	if (k == 1) {
		c = 0; m = 0; y = 0;
	}
	else {
		c = (1 - r/255.0 - k) / (1 - k);
		m = (1 - g / 255.0 - k) / (1 - k);
		y = (1 - b / 255.0 - k) / (1 - k);
	}

	ret->c = check_hsv_svvalue(round(c * 100.0));
	ret->m = check_hsv_svvalue(round(m * 100.0));
	ret->y = check_hsv_svvalue(round(y * 100.0));
	ret->k = check_hsv_svvalue(round(k * 100.0));
}
void CMYKtoRGB(CMYK* val, RGB* ret) {
	double c = check_hsv_svvalue(val->c);
	double m = check_hsv_svvalue(val->m);
	double y = check_hsv_svvalue(val->y);
	double k = check_hsv_svvalue(val->k);

	double r = 255 * (100 - c) * (100 - k);
	double g = 255 * (100 - m) * (100 - k);
	double b = 255 * (100 - y) * (100 - k);

	ret->r = check_rgbvalue(r);
	ret->g = check_rgbvalue(g);
	ret->b = check_rgbvalue(b);
}

void RGBtoCMY(RGB* val, CMY* ret) {
	double r = check_rgbvalue(val->r);
	double g = check_rgbvalue(val->g);
	double b = check_rgbvalue(val->b);

	ret->c = check_hsv_svvalue((255.0 - r)/255.0);
	ret->m = check_hsv_svvalue((255.0 - g)/255.0);
	ret->y = check_hsv_svvalue((255.0 - b)/255.0);
}
void CMYtoRGB(CMY* val, RGB* ret) {
	double c = check_hsv_svvalue(val->c);
	double m = check_hsv_svvalue(val->m);
	double y = check_hsv_svvalue(val->y);

	ret->r = check_rgbvalue((100.0 - c) * 255.0);
	ret->g = check_rgbvalue((100.0 - m) * 255.0);
	ret->b = check_rgbvalue((100.0 - y) * 255.0);
}