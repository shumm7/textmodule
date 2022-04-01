#pragma once
#include <iostream>
#include <vector>
#include "textmodule_color.h"

typedef struct ColorItem {
	std::wstring color = L"";
	std::wstring name = L"";
	std::wstring japanese = L"";
	std::wstring english = L"";
};
typedef std::vector<ColorItem> ColorList;

int color_getlist(lua_State* L);
int color_search(lua_State* L);
int color_makepalette(lua_State* L);
int color_loadpalette(lua_State* L);

void luaReg_color(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COLOR_REG[] = {
	{"getlist", color_getlist},
	{"search", color_search},
	{"makepalette", color_makepalette},
	{"loadpalette", color_loadpalette},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLOR_META_REG[] = {
	{"search", color_search},
	{"makepalette", color_makepalette},
	{"loadpalette", color_loadpalette},
	{ nullptr, nullptr }
};