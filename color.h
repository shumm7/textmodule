#pragma once
#include <iostream>
#include <vector>
#include "textmodule_color.h"

#define TEXTMODULE_COLORLIST "ColorList"

typedef struct ColorItem {
	std::wstring color = L"";
	std::wstring name = L"";
	std::wstring japanese = L"";
	std::wstring english = L"";
};
typedef std::vector<ColorItem> ColorList;

int color_getlist(lua_State* L);
int color_search(lua_State* L);

void luaReg_color(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COLOR_REG[] = {
	{"getlist", color_getlist},
	{"search", color_search},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLOR_META_REG[] = {
	{"search", color_search},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLOR_MAIN_REG[] = {
	//{"RGB", color_RGB},
	//{"HSV", color_HSV},
	{ nullptr, nullptr }
};