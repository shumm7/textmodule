#pragma once
#include <lua.hpp>

int qrcode_encode(lua_State* L);
int qrcode_encode_string(lua_State* L);

void luaReg_qrcode(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_QRCODE_REG[] = {
	{"encode", qrcode_encode},
	{"encode_string", qrcode_encode_string},
	{ nullptr, nullptr }
};