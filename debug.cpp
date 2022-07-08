#include "debug.hpp"

#include <lua.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_option.hpp"

#include <windows.h>

static luaL_Reg TEXTMODULE_DEBUG_REG[] = {
	{ nullptr, nullptr }
};

void luaReg_debug(lua_State* L, lua_Option opt) {
	if (opt["debug"]) {
		tm_debuglog_apiloaded(opt, "debug");
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_DEBUG_REG);
		lua_setfield(L, -2, "debug");
	}
	else {
		tm_debuglog_apinoloaded(opt, "debug");
	}
}