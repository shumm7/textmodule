#pragma once
#include <iostream>
#include <vector>
#include <lua.hpp>

int colorlist_getlist(lua_State* L);
int colorlist_search(lua_State* L);
int colorlist_makepalette(lua_State* L);
int colorlist_loadpalette(lua_State* L);
int colorlist___type(lua_State* L);

static luaL_Reg TEXTMODULE_COLORLIST_REG[] = {
	{"getlist", colorlist_getlist},
	{"search", colorlist_search},
	{"makepalette", colorlist_makepalette},
	{"loadpalette", colorlist_loadpalette},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLORLIST_META_REG[] = {
	{"__type", colorlist___type},

	{"search", colorlist_search},
	{"makepalette", colorlist_makepalette},
	{"loadpalette", colorlist_loadpalette},
	{ nullptr, nullptr }
};