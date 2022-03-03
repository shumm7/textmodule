#pragma once
int utf8_byte(lua_State* L);
int utf8_char(lua_State* L);

void luaReg_utf8(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_UTF8_REG[] = {
	{"char", utf8_char},
	{"byte", utf8_byte},
	{ nullptr, nullptr }
};