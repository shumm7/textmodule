#pragma once
#include <iostream>
#include <vector>
#include <lua.hpp>

typedef struct ColorItem {
	std::wstring color = L"";
	std::wstring name = L"";
	std::wstring japanese = L"";
	std::wstring english = L"";
};
typedef std::vector<ColorItem> ColorList;

int colorlist_getlist(lua_State* L);
int colorlist_search(lua_State* L);
int colorlist_makepalette(lua_State* L);
int colorlist_loadpalette(lua_State* L);

void luaReg_colorlist(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COLORLIST_REG[] = {
	{"getlist", colorlist_getlist},
	{"search", colorlist_search},
	{"makepalette", colorlist_makepalette},
	{"loadpalette", colorlist_loadpalette},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLORLIST_META_REG[] = {
	{"search", colorlist_search},
	{"makepalette", colorlist_makepalette},
	{"loadpalette", colorlist_loadpalette},
	{ nullptr, nullptr }
};