#include "table.hpp"
#include <lua.hpp>
#include <iostream>
#include "textmodule_lua.hpp"

int table_new(lua_State* L) {
	try {
		int n = lua_gettop(L);
		if (n == 1) {
			if (tm_callmetan(L, 1, "__table"))
				return 1;
		}

		lua_newtable(L);
		for (int i = 0; i < n; i++) {
			lua_pushinteger(L, i + 1);
			lua_pushvalue(L, i + 1);
			lua_settable(L, -3);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_TABLE_REG[] = {
	{"new", table_new},
	{ nullptr, nullptr }
};

void luaReg_table(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_TABLE_REG);
		lua_setfield(L, -2, name);
	}
}