#include <iostream>
#include <sstream>
#include <exception>
#include <cmath>
#include <algorithm>

#include "textmodule_math.h"
#include "textmodule_color.h"
#include "textmodule_string.h"

std::wstring c_lstr(std::wstring str, int length, wchar_t c) {
	if (str.length() >= length)
		return str;
	return std::wstring(length - str.length(), c) + str;
}

std::wstring c_get_pixel_hex(st_rgba32* val) {
	int r = clamp_s(val->r, 0, 255);
	int g = clamp_s(val->g, 0, 255);
	int b = clamp_s(val->b, 0, 255);

	std::wstring hex = L"0x";
	hex += c_lstr(DecToHex(r).substr(2), 2, L'0');
	hex += c_lstr(DecToHex(g).substr(2), 2, L'0');
	hex += c_lstr(DecToHex(b).substr(2), 2, L'0');
	return hex;
}

std::wstring c_get_pixel_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	st_rgba32 c = {0,0,0,0};

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c_get_pixel_hex(&c);
}

std::wstring c_get_pixel_hex(uint8_t r, uint8_t g, uint8_t b) {
	return c_get_pixel_hex(r, g, b, 0);
}

std::wstring c_get_color_hex(st_rgba* val) {
	uint8_t r = clamp_s(val->r) * 255.0;
	uint8_t g = clamp_s(val->g) * 255.0;
	uint8_t b = clamp_s(val->b) * 255.0;
	return c_get_pixel_hex(r, g, b);
}

std::wstring c_get_color_hex(double r, double g, double b, double a) {
	st_rgba c = {0,0,0,0};

	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c_get_color_hex(&c);
}

std::wstring c_get_color_hex(double r, double g, double b) {
	return c_get_pixel_hex(r, g, b, 0);
}


void c_color_to_pixel(st_rgba32* ret, st_rgba* val) {
	ret->r = (uint8_t)clamp_s((val->r) * 255.0, 0, 255);
	ret->g = (uint8_t)clamp_s((val->g) * 255.0, 0, 255);
	ret->b = (uint8_t)clamp_s((val->b) * 255.0, 0, 255);
	ret->a = (uint8_t)clamp_s((val->a) * 255.0, 0, 255);
	return;
}

void c_color_to_pixel(st_rgba32* ret, double r, double g, double b, double a) {
	st_rgba c = {0,0,0,0};
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	c_color_to_pixel(ret, &c);
	return;
}

void c_color_to_pixel(st_rgba32* ret, double r, double g, double b) {
	return c_color_to_pixel(ret, r,g,b,0);
}


void c_pixel_to_color(st_rgba* ret, st_rgba32* val) {
	ret->r = clamp_s((double)val->r / 255.0);
	ret->g = clamp_s((double)val->g / 255.0);
	ret->b = clamp_s((double)val->b / 255.0);
	ret->a = clamp_s((double)val->a / 255.0);
	return;
}

void c_pixel_to_color(st_rgba* ret, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	st_rgba32 c = {0,0,0,0};
	c.r = r;
	c.g = g;
	c.b = b;
	c.a = a;
	return c_pixel_to_color(ret, &c);
}

void c_pixel_to_color(st_rgba* ret, uint8_t r, uint8_t g, uint8_t b) {
	return c_pixel_to_color(ret, r, g, b, 0);
}


void c_hex_to_pixel(st_rgba32* ret, int num, uint8_t a) {
	num = clamp_s(num, 0x000000, 0xffffff);

	std::wstring hex = DecToHex(num);
	if (hex.substr(0, 2) == L"0x")
		hex = hex.substr(2);

	if (hex.length() < 6)
		hex = std::wstring(6 - hex.length(), L'0') + hex;

	ret->r = clamp_s(HexToDec(hex.substr(0, 2)), 0, 255);
	ret->g = clamp_s(HexToDec(hex.substr(2, 2)), 0, 255);
	ret->b = clamp_s(HexToDec(hex.substr(4, 2)), 0, 255);
	ret->a = a;
	return;
}

void c_hex_to_pixel(st_rgba32* ret, std::wstring num, uint8_t a) {
	return c_hex_to_pixel(ret, HexToDec(num), a);
}

void c_hex_to_pixel(st_rgba32* ret, int num) {
	return c_hex_to_pixel(ret, num, (uint8_t)0);
}

void c_hex_to_pixel(st_rgba32* ret, std::wstring num) {
	return c_hex_to_pixel(ret, num, (uint8_t)0);
}


double c_color_norm(st_rgba* value) {
	return std::pow(value->r, 2) + std::pow(value->g, 2) + std::pow(value->b, 2) + std::pow(value->a, 2);
}

double c_pixel_norm(st_rgba32* value) {
	st_rgba c;
	c_pixel_to_color(&c, value);
	return c_color_norm(&c);
}


void c_clamp_color(st_rgba* value) {
	value->r = clamp_s(value->r);
	value->g = clamp_s(value->g);
	value->b = clamp_s(value->b);
	value->a = clamp_s(value->a);
}

void c_clamp_color(st_rgba* ret, st_rgba* value) {
	ret->r = clamp_s(value->r);
	ret->g = clamp_s(value->g);
	ret->b = clamp_s(value->b);
	ret->a = clamp_s(value->a);
}