#pragma once
#include <iostream>

#define TEXTMODULE_COLORLIST "ColorList"
#define TEXTMODULE_RGB "RGB*"
#define TEXTMODULE_HSV "HSV*"
#define TEXTMODULE_HSL "HSL*"
#define rgb_check(L, n) (reinterpret_cast<RGB*>(luaL_checkudata(L, n, TEXTMODULE_RGB)))
#define hsv_check(L, n) (reinterpret_cast<HSV*>(luaL_checkudata(L, n, TEXTMODULE_HSV)))
#define hsl_check(L, n) (reinterpret_cast<HSL*>(luaL_checkudata(L, n, TEXTMODULE_HSL)))

typedef struct {
	unsigned char r; // 0 - 255
	unsigned char g; // 0 - 255
	unsigned char b; // 0 - 255
}RGB;

typedef struct {
	unsigned short h; // 0 - 360
	unsigned char s; // 0 - 100
	unsigned char v; // 0 - 100
}HSV;

typedef struct {
	unsigned short h; // 0 - 360
	unsigned char s; // 0 - 100
	unsigned char l; // 0 - 100
}HSL;

typedef struct {
	float c; // 0 - 100
	float m; // 0 - 100
	float y; // 0 - 100
	float k; // 0 - 100
}CMYK;

typedef struct {
	float c; // 0 - 100
	float m; // 0 - 100
	float y; // 0 - 100
}CMY;

int check_rgbvalue(int n);
int check_hsv_hvalue(int n);
int check_hsv_svvalue(int n);

std::wstring getRGBhex(RGB* val);
void getRGBhex(int num, RGB* ret);

void RGBtoHSV(RGB* val, HSV* ret);
void HSVtoRGB(HSV* val, RGB* ret);

void RGBtoHSL(RGB* val, HSL* ret);
void HSLtoRGB(HSL* val, RGB* ret);
