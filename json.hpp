#pragma once
#include <lua.hpp>
int json_parse(lua_State* L);
int json_dump(lua_State* L);
int json_lint(lua_State* L);
int json_size(lua_State* L);


void luaReg_json(lua_State* L, const char* name, bool reg);
void luaGlobal_json(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_JSON_REG[] = {
	{"parse", json_parse},
	{"dump", json_dump},
	{"lint", json_lint},
	{"size", json_size},
	{nullptr, nullptr}
};