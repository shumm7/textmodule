#pragma once
#include <lua.hpp>

int http_get(lua_State* L);
int http_head(lua_State* L);
int http_post(lua_State* L);
int http_put(lua_State* L);
int http_delete(lua_State* L);
int http_download(lua_State* L);
int http_encode(lua_State* L);
int http_decode(lua_State* L);
int http_base64(lua_State* L);
int http_frombase64(lua_State* L);

void luaReg_http(lua_State* L, const char* name, bool reg);
void luaGlobal_http(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_HTTP_REG[] = {
	{"get", http_get},
	{"head", http_head},
	{"post", http_post},
	{"put", http_put},
	{"delete", http_delete},
	{"download", http_download},
	{"encode", http_encode},
	{"decode", http_decode},
	{"base64", http_base64},
	{"frombase64", http_frombase64},
	{ nullptr, nullptr }
};