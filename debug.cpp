#include "debug.hpp"

#include <lua.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

#include <windows.h>

static luaL_Reg TEXTMODULE_DEBUG_REG[] = {
	{ nullptr, nullptr }
};

void luaReg_debug(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_DEBUG_REG);
		lua_setfield(L, -2, name);
	}
}