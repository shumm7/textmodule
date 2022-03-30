#pragma once
#include <lua.hpp>

#define FIGURE_BACKGROUND "îwåi"
#define FIGURE_CIRCLE "â~"
#define FIGURE_SQUARE "éläpå`"
#define FIGURE_TRIANGLE "éOäpå`"
#define FIGURE_PENTAGON "å‹äpå`"
#define FIGURE_HEXAGON "òZäpå`"
#define FIGURE_STAR "êØå^"

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