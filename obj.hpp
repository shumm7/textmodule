#pragma once
#include <lua.hpp>

#define FIGURE_BACKGROUND "�w�i"
#define FIGURE_CIRCLE "�~"
#define FIGURE_SQUARE "�l�p�`"
#define FIGURE_TRIANGLE "�O�p�`"
#define FIGURE_PENTAGON "�܊p�`"
#define FIGURE_HEXAGON "�Z�p�`"
#define FIGURE_STAR "���^"

int obj_remove_ctrl(lua_State* L);
int obj_find_ctrl(lua_State* L);
int obj_cbool(lua_State* L);
void luaReg_obj(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_OBJ_REG[] = {
	{"remove_ctrl", obj_remove_ctrl},
	{"find_ctrl", obj_find_ctrl},
	{"cbool", obj_cbool},
	{nullptr, nullptr}
};