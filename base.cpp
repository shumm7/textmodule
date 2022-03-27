#include <lua.hpp>
#include <iostream>
#include <sstream>

#include "base.h"
#include "color.h"
#include "textmodule.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "textmodule_option.h"
#include "textmodule_lua.h"

int base_getinfo(lua_State* L) {
	try {
		std::wstring t = tm_towstring(L, 1);
		int i = tm_tointeger_s(L, 2, 1);

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
			std::wstring res = getVersionNum(i);
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

		while (true)
		{
			int tp = lua_type(L, i);
			std::stringstream ss;

			switch (tp)
			{
			case LUA_TNIL:
				ret = ret + L"nil";
				break;
			case LUA_TNUMBER:
				ss << lua_tonumber(L, i);
				ret = ret + StrToWstr(ss.str());
				break;
			case LUA_TBOOLEAN:
				if (lua_toboolean(L, i))
					ret = ret + L"true";
				else
					ret = ret + L"false";
				break;
			case LUA_TSTRING:
				ret = ret + lua_towstring(L, i);
				break;
			case LUA_TTABLE:
				ret = ret + L"table";
				break;
			case LUA_TFUNCTION:
				ret = ret + L"function";
				break;
			case LUA_TUSERDATA:
				ret = ret + L"userdata";
				break;
			case LUA_TTHREAD:
				ret = ret + L"thread";
				break;
			case LUA_TLIGHTUSERDATA:
				ret = ret + L"lightuserdata";
				break;
			case LUA_TNONE:
				ret = ret.substr(0, ret.length() - 1);
				debug_string(ret);
				lua_pushwstring(L, ret);
				return 1;
			}

			ret = ret + L",";
			i++;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
	return 0;
}

int base_exception(lua_State* L) {
	if (lua_type(L, 1) == LUA_TSTRING) {
		throw std::exception(lua_tostring(L, 1));
	}
	else if (lua_type(L, 1) == LUA_TNONE) {
		throw std::exception();
	}
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
		luaL_register(L, NULL, TEXTMODULE_COLOR_MAIN_REG);
	}
}