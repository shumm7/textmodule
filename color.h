#pragma once
/*
int color_RGB(lua_State* L);
int color_HSV(lua_State* L);
int color_convert(lua_State* L);
*/

void luaReg_color(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COLOR_REG[] = {
	//{"RGB", color_RGB},
	//{"HSV", color_HSV},
	//{"convert", color_convert},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COLOR_MAIN_REG[] = {
	//{"RGB", color_RGB},
	//{"HSV", color_HSV},
	{ nullptr, nullptr }
};