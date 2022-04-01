#include <lua.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>

#include "base.h"
#include "textmodule.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "textmodule_option.h"
#include "textmodule_lua.h"

int base_getinfo(lua_State* L) {
	try {
		lua_Wstring t = tm_towstring(L, 1);
		lua_Integer i = tm_tointeger_s(L, 2, 1);

		if (t == L"version") {
			if (i == 1) {
				lua_pushwstring(L, getVersionNum(MODULE_VERSION));
				return 1;
			}
			else if (i == 2) {
				lua_pushinteger(L, MODULE_VERSION);
				return 1;
			}
		}
		else if (t == L"versions") {
			lua_Wstring res = getVersionNum(i);
			if (res != L"") {
				lua_pushwstring(L, res);
				return 1;
			}
			else {
				return 0;
			}

		}
		else if (t == L"name") {
			lua_pushstring(L, MODULE_NAME);
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_debug_print(lua_State* L) {
	try {
		int i = 1;
		std::wstring ret = L"";

		if (lua_type(L, i) == LUA_TNONE) {
			debug_string(ret);
			lua_pushwstring(L, ret);
			return 1;
		}

		while (lua_type(L, i)!=LUA_TNONE)
		{
			ret += StrToWstr(tm_convtostring(L, i)) + L"\t";
			i++;
		}
		ret = ret.substr(0, ret.length() - 1);
		debug_string(ret);
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_type(lua_State* L) {
	try {
		if (lua_gettop(L) <= 1) {
			lua_pushstring(L, tm_typename(L, 1));
			return 1;
		}
		else {
			int i = 1;
			std::vector<std::string> res;
			while (lua_type(L, i) != LUA_TNONE) {
				res.push_back(tm_typename(L, i));
				i++;
			}

			lua_newtable(L);
			for (int j = 0; j < (i - 1); j++)
				lua_settablevalue(L, j + 1, res.at(j));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_print(lua_State* L) {
	try {
		for (int i = 0; i < lua_gettop(L); i++) {
			std::cout << tm_convtostring(L, i + 1) << "\t";
		}
		std::cout << std::endl;
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_printf(lua_State* L) {
	try {
		lua_Sstring str = tm_tosstring(L, 1);
		fmt::dynamic_format_arg_store<fmt::format_context> store;

		int i = 2;
		while (true) {
			int tp = lua_type(L, i);

			if (tp == LUA_TNUMBER)
				store.push_back(lua_tonumber(L, i));
			else if (tp == LUA_TBOOLEAN)
				store.push_back(lua_toboolean(L, i));
			else if (tp == LUA_TSTRING)
				store.push_back(lua_tostring(L, i));
			else if (tp == LUA_TNIL)
				store.push_back("nil");
			else if (tp == LUA_TNONE)
				break;
			else
				store.push_back(lua_topointer(L, i));

			i++;
		};

		std::cout << fmt::vformat(str, store) << std::endl;
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_exception(lua_State* L) {
	if (lua_type(L, 1) == LUA_TSTRING)
		throw std::exception(lua_tostring(L, 1));
	else if (lua_type(L, 1) == LUA_TNONE)
		throw std::exception();
	return 0;
}

int base_versioncheck(lua_State* L) {
	try {
		int res = versionCheck();
		switch (res)
		{
		case VERSION_CHECK_LATEST:
			lua_pushboolean(L, true);
			break;
		case VERSION_CHECK_OUTDATED:
			lua_pushboolean(L, false);
			break;
		case VERSION_CHECK_ERROR:
			lua_pushnil(L);
			break;
		default:
			lua_pushnil(L);
			break;
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_base(lua_State* L, bool reg) {
	static luaL_Reg none[] = {
		{nullptr, nullptr}
	};

	luaL_register(L, MODULE_NAME, none);
	if (reg) {
		luaL_register(L, NULL, TEXTMODULE_BASE_REG);
	}
}