#include "json.hpp"

#include <iostream>
#include <lua.hpp>

#include "textmodule_lua.hpp"

int json_parse(lua_State* L) {
	try {
		lua_Json j = tm_jsonparse(tm_tosstring_s(L, 1, "{}"));
		tm_pushjson(L, &j);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int json_dump(lua_State* L) {
	try {
		lua_Json j = tm_tabletojson(L, 1);
		if(lua_isnone(L, 2))
			lua_pushsstring(L, tm_jsondump(&j));
		else
			lua_pushsstring(L, tm_jsondump(&j, lua_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int json_lint(lua_State* L) {
	try {
		lua_Json j = tm_tojson(L, 1);
		
		if (lua_isnumber(L, 2)) {
			lua_pushsstring(L, tm_jsondump(&j, lua_tonumber(L, 2)));
			return 1;
		}
		else if (lua_isnoneornil(L, 2)) {
			lua_pushsstring(L, tm_jsondump(&j));
			return 1;
		}
		else
			return luaL_argerror(L, 2, "number/nil expected");
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int json_size(lua_State* L) {
	try {
		lua_Json j = tm_tojson(L, 1);
		lua_pushnumber(L, j.size());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_JSON_REG[] = {
	{"parse", json_parse},
	{"dump", json_dump},
	{"lint", json_lint},
	{"size", json_size},
	{nullptr, nullptr}
};

void luaReg_json(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//json
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_JSON_REG);
		lua_setfield(L, -2, name);
	}
}