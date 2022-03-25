#include <lua.hpp>
#include "debug.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"

void luaReg_debug(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_DEBUG_REG);
		lua_setfield(L, -2, name);
	}
}