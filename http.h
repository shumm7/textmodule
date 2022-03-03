#include <lua.hpp>

int http_get(lua_State* L);
int http_post(lua_State* L);

void luaReg_http(lua_State* L, const char* name, bool reg);
void luaGlobal_http(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_HTTP_REG[] = {
	{"get", http_get},
	{"post", http_post},
	{ nullptr, nullptr }
};