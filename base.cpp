#include "base.hpp"

#include <lua.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>

#include "textmodule.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_option.hpp"
#include "textmodule_lua.hpp"

static const int sentinel_ = 0;
#define sentinel        ((void *)&sentinel_)

int pairsaux(lua_State* L, const char* method, int iszero, lua_CFunction iter) {
	if (!luaL_getmetafield(L, 1, method)) {  /* no metamethod? */
		luaL_checktype(L, 1, LUA_TTABLE);  /* argument must be a table */
		lua_pushcfunction(L, iter);  /* will return generator, */
		lua_pushvalue(L, 1);  /* state, */
		if (iszero) lua_pushinteger(L, 0);  /* and initial value */
		else lua_pushnil(L);
	}
	else {
		lua_pushvalue(L, 1);  /* argument 'self' to metamethod */
		lua_call(L, 1, 3);  /* get 3 values from metamethod */
	}
	return 3;
}

int nextaux(lua_State* L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	lua_settop(L, 2);  /* create a 2nd argument if there isn't one */
	if (lua_next(L, 1))
		return 2;
	else {
		lua_pushnil(L);
		return 1;
	}
}

int ipairsaux(lua_State* L) {
	int i = luaL_checkint(L, 2);
	luaL_checktype(L, 1, LUA_TTABLE);
	i++;  /* next value */
	lua_pushinteger(L, i);
	lua_rawgeti(L, 1, i);
	return (lua_isnil(L, -1)) ? 1 : 2;
}


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

int base_showtable(lua_State* L) {
	try {
		if (!lua_istable(L, 1))
			return luaL_argerror(L, 1, "table expected");

		lua_pushnil(L);
		lua_Sstring key;
		lua_Sstring value;
		lua_Sstring ret = "";

		while (lua_next(L, 1) != 0) {
			if(ret.length()!=0)
				ret += "\n";

			if (lua_type(L, -2) == LUA_TNUMBER)
				key = WstrToStr(tostring_n(lua_tonumber(L, -2)));
			else
				key = tm_convtostring(L, -2);

			value = tm_convtostring(L, -1);
			ret += std::string("[" + key + "] " + value);

			lua_pop(L, 1);
		}

		lua_pushsstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_showmetatable(lua_State* L) {
	try {
		luaL_checkany(L, 1);
		if (!lua_getmetatable(L, 1)) {
			lua_pushnil(L);
			return 1;  /* no metatable */
		}
		luaL_getmetafield(L, 1, "__metatable");
		lua_remove(L, 1);

		lua_pushnil(L);
		lua_Sstring key;
		lua_Sstring value;
		lua_Sstring ret = "";

		while (lua_next(L, 1) != 0) {
			if (ret.length() != 0)
				ret += "\n";

			if (lua_type(L, -2) == LUA_TNUMBER)
				key = WstrToStr(tostring_n(lua_tonumber(L, -2)));
			else
				key = tm_convtostring(L, -2);

			value = tm_convtostring(L, -1);
			ret += std::string("[" + key + "] " + value);

			lua_pop(L, 1);
		}

		lua_pushsstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_maketable(lua_State* L) {
	try {
		int n = lua_gettop(L);

		lua_newtable(L);
		for (int i = 0; i < n; i++) {
			lua_pushinteger(L, i+1);
			lua_pushvalue(L, n + 1);
			lua_settable(L, -3);
		}

		return 1;
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
			return 0;
		}

		for (int i = 1; i <= lua_gettop(L); i++) {
			ret += StrToWstr(tm_convtostring(L, i)) + L"\t";
		}
		ret = ret.substr(0, ret.length() - 1);
		debug_string(ret);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_type(lua_State* L) {
	try {
		int n= lua_gettop(L);
		if (n <= 0) {
			lua_pushstring(L, tm_typename(L, 1));
			return 1;
		}


		for (int i = 0; i < n; i++)
			lua_pushstring(L, tm_typename(L, i+1));

		return n;
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
			else if (tp == LUA_TUSERDATA) {
				store.push_back(lua_topointer(L, i));
			}
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

int base_tostring(lua_State* L) {
	try {
		int s = lua_gettop(L);
		if (s < 1) {
			lua_pushstring(L, tm_convtostring(L, 1));
			return 1;
		}

		for (int i = 0; i < s; i++) {
			lua_pushstring(L, tm_convtostring(L, i+1));
		}
		return s;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_tonumber(lua_State* L) {
	try {
		luaL_checkany(L, 1);
		int base = luaL_optint(L, 2, 10);

		if (base == 10) {  /* standard conversion */
			if (luaL_callmeta(L, 1, "__tonumber"))
				return 1;

			if (lua_isnumber(L, 1)) {
				lua_pushnumber(L, lua_tonumber(L, 1));
				return 1;
			}
		}
		else {
			const char* s1 = "";
			if (luaL_callmeta(L, 1, "__tonumber")) {
				s1 = luaL_checkstring(L, -1);
			}
			else {
				s1 = luaL_checkstring(L, 1);
			}
			
			char* s2;
			unsigned long n;
			luaL_argcheck(L, 2 <= base && base <= 36, 2, "base out of range");
			n = strtoul(s1, &s2, base);
			if (s1 != s2) {  /* at least one valid digit? */
				while (isspace((unsigned char)(*s2))) s2++;  /* skip trailing spaces */
				if (*s2 == '\0') {  /* no invalid trailing characters? */
					lua_pushnumber(L, (lua_Number)n);
					return 1;
				}
			}
		}
		lua_pushnil(L);  /* else not a number */
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_pointer(lua_State* L) {
	try {
		luaL_checkany(L, 1);
		std::string s = fmt::format("{0:p}", lua_topointer(L, 1));
		lua_pushsstring(L, s);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_getglobal(lua_State* L) {
	try {
		lua_getglobal(L, tm_tostring(L, 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_setglobal(lua_State* L) {
	try {
		lua_pushvalue(L, 1);
		lua_setglobal(L, tm_tostring(L, 2));
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_pairs(lua_State* L) {
	try {
		return pairsaux(L, "__pairs", 0, nextaux);
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_ipairs(lua_State* L) {
	try {
		return pairsaux(L, "__ipairs", 1, ipairsaux);
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int base_next(lua_State* L){
	try {
		return nextaux(L);
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

static luaL_Reg TEXTMODULE_BASE_REG[] = {
	{"getinfo", base_getinfo},
	{"showtable", base_showtable},
	{"showmetatable", base_showmetatable},
	{"maketable", base_maketable},
	{"debug_print", base_debug_print},
	{"type", base_type},
	{"print", base_print},
	{"printf", base_printf},
	{"exception", base_exception},
	{"versioncheck", base_versioncheck},
	{"tostring", base_tostring},
	{"tonumber", base_tonumber},
	{"pointer", base_pointer},
	{"getglobal", base_getglobal},
	{"setglobal", base_setglobal},
	{"pairs", base_pairs},
	{"ipairs", base_ipairs},
	{"next", base_next},
	{ nullptr, nullptr }
};

void luaReg_base(lua_State* L, bool reg) {
	if (reg) {
		luaL_register(L, NULL, TEXTMODULE_BASE_REG);
	}
}