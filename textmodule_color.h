#pragma once
#define TEXTMODULE_COLORLIST "ColorList"
#define TEXTMODULE_COLOR "st_rgba*"
#define TEXTMODULE_PIXEL "st_rgba32*"
#define TEXTMODULE_IMAGE "st_imgpixel*"
#define color_check(L, n) (reinterpret_cast<st_rgba*>(luaL_checkudata(L, n, TEXTMODULE_COLOR)))
#define pixel_check(L, n) (reinterpret_cast<st_rgba32*>(luaL_checkudata(L, n, TEXTMODULE_PIXEL)))
#define image_check(L, n) (reinterpret_cast<st_imgpixel*>(luaL_checkudata(L, n, TEXTMODULE_IMAGE)))

typedef struct { double r; double g; double b; double a; }st_rgba;
typedef struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; }st_rgba32;
typedef struct { unsigned char b; unsigned char g; unsigned char r; unsigned char a; }st_imgpixel;

std::wstring c_get_color_hex(st_rgba* val);
std::wstring c_get_color_hex(double r, double g, double b, double a);
std::wstring c_get_color_hex(double r, double g, double b);
std::wstring c_get_pixel_hex(st_rgba32* val);
std::wstring c_get_pixel_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
std::wstring c_get_pixel_hex(uint8_t r, uint8_t g, uint8_t b);

void c_color_to_pixel(st_rgba32* ret, st_rgba* val);
void c_color_to_pixel(st_rgba32* ret, double r, double g, double b, double a);
void c_color_to_pixel(st_rgba32* ret, double r, double g, double b);

void c_pixel_to_color(st_rgba* ret, st_rgba32* val);
void c_pixel_to_color(st_rgba* ret, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void c_pixel_to_color(st_rgba* ret, uint8_t r, uint8_t g, uint8_t b);

void c_hex_to_pixel(st_rgba32* ret, int num, uint8_t a);
void c_hex_to_pixel(st_rgba32* ret, std::wstring num, uint8_t a);
void c_hex_to_pixel(st_rgba32* ret, int num);
void c_hex_to_pixel(st_rgba32* ret, std::wstring num);

double c_color_norm(st_rgba* value);
double c_pixel_norm(st_rgba32* value);

void c_clamp_color(st_rgba* value);
void c_clamp_color(st_rgba* ret, st_rgba* value);