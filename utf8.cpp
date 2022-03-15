#include <lua.hpp>
#include <iostream>
#include <vector>

#include "utf8.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

int utf8_byte(lua_State* L) {
	try {
		std::wstring text = tm_towstring(L, 1);
		int i = tm_tointeger_s(L, 2, 1) - 1;
		int j = tm_tointeger_s(L, 3, 1) - 1;
		int length = text.length();

		if (length < 1) {
			return 0;
		}
		if (j < i) {
			return 0;
		}
		if (i >= length) {
			return 0;
		}
		if (j >= length) {
			j = length - 1;
		}

		for (int k = i; k <= j; k++)
		{
			int c = text[k];
			auto r = UnicodeToUTF8(c);
			if (r != -1) {
				lua_pushinteger(L, r);
			}
			else {
				return 0;
			}

		}
		return j - i + 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int utf8_char(lua_State* L) {
	try {
		int cnt = 1;
		std::vector<unsigned long long> list;

		while (true) {
			int tp = lua_type(L, cnt);

			if (tp == LUA_TNUMBER) {
				unsigned long long r = UTF8ToUnicode(lua_tonumber(L, cnt));

				if (r != -1) {
					list.push_back(r);
				}
				else {
					return 0;
				}
			}
			else if (tp == LUA_TNIL || tp == LUA_TNONE) {
				break;
			}
			else {
				return 0;
			}

			cnt++;
		}

		if (list.size() < 1) {
			return 0;
		}

		wchar_t temp;
		std::wstring ret;
		for (unsigned int i = 0; i < list.size(); i++)
		{
			temp = (wchar_t)list[i];
			ret += temp;
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_utf8(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_UTF8_REG);

		lua_pushlstring(L, UTF8PATT, sizeof(UTF8PATT) / sizeof(char) - 1);
		lua_setfield(L, -2, "charpattern");

		lua_setfield(L, -2, name);
	}
}