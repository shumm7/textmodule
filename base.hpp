#pragma once
#include <lua.hpp>

int base_getinfo(lua_State* L);
int base_showtable(lua_State* L);
int base_showmetatable(lua_State* L);
int base_maketable(lua_State* L);
int base_debug_print(lua_State* L);
int base_type(lua_State* L);
int base_print(lua_State* L);
int base_printf(lua_State* L);
int base_exception(lua_State* L);
int base_versioncheck(lua_State* L);
int base_tostring(lua_State* L);
int base_tonumber(lua_State* L);
int base_pointer(lua_State* L);
int base_getglobal(lua_State* L);
int base_setglobal(lua_State* L);
int base_pairs(lua_State* L);
int base_ipairs(lua_State* L);
int base_next(lua_State* L);

void luaReg_base(lua_State* L, bool reg);

static luaL_Reg TEXTMODULE_BASE_REG[] = {
	{"getinfo", base_getinfo},
	{"showtable", base_showtable},
	{"showmetatable", base_showmetatable},
	{"maketable", base_maketable},
	{"debug_print", base_debug_print},
	{"type", base_type},
	{"print", base_print},
	{"printf", base_printf},
	{"exception", base_exception},
	{"versioncheck", base_versioncheck},
	{"tostring", base_tostring},
	{"tonumber", base_tonumber},
	{"pointer", base_pointer},
	{"getglobal", base_getglobal},
	{"setglobal", base_setglobal},
	{"pairs", base_pairs},
	{"ipairs", base_ipairs},
	{"next", base_next},
	{ nullptr, nullptr }
};