#pragma once
#include <iostream>
#include "textmodule_lua.hpp"

std::wstring c_get_color_hex(st_rgba* val);
std::wstring c_get_color_hex(double r, double g, double b, double a);
std::wstring c_get_color_hex(double r, double g, double b);
std::wstring c_get_pixel_hex(st_rgba32* val);
std::wstring c_get_pixel_hex(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
std::wstring c_get_pixel_hex(unsigned char r, unsigned char g, unsigned char b);

void c_color_to_pixel(st_rgba32* ret, st_rgba* val);
void c_color_to_pixel(st_rgba32* ret, double r, double g, double b, double a);
void c_color_to_pixel(st_rgba32* ret, double r, double g, double b);

void c_pixel_to_color(st_rgba* ret, st_rgba32* val);
void c_pixel_to_color(st_rgba* ret, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void c_pixel_to_color(st_rgba* ret, unsigned char r, unsigned char g, unsigned char b);

void c_hex_to_pixel(st_rgba32* ret, int num, unsigned char a);
void c_hex_to_pixel(st_rgba32* ret, std::wstring num, unsigned char a);
void c_hex_to_pixel(st_rgba32* ret, int num);
void c_hex_to_pixel(st_rgba32* ret, std::wstring num);

double c_color_norm(st_rgba* value);
double c_pixel_norm(st_rgba32* value);

void c_clamp_color(st_rgba* value);
void c_clamp_color(st_rgba* ret, st_rgba* value);