#include "string.hpp"

#include <lua.hpp>
#include <iostream>
#include <regex>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <vector>

#include "tmstring.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_math.hpp"

int string_find(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Wstring pattern = tm_towstring(L, 2);
		lua_Integer init = tm_tointeger_s(L, 3, 1);
		lua_Boolean plain = tm_toboolean_s(L, 4, false);
		bool rev = false;

		if (init < 0) {
			init = (-init) - 1;
			rev = true;
			if (init >= text.length())
				init = text.length() - 1;
		}
		else if (init > 0)
			init = init - 1;

		if (init >= text.length())
			return 0;

		if (plain) {
			if (!rev) {
				lua_Wstring temp = text.substr(init);
				int pos = temp.find(pattern);
				if (pos!=std::string::npos) {
					lua_Integer n = pos + 1 + init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + pattern.length() - 1);
					return 2;
				}
			}
			else {
				lua_Wstring temp = text.substr(text.length() - init - 1);
				int pos = temp.find(pattern);
				if (pos != std::string::npos) {
					lua_Integer n = pos + text.length() - init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + pattern.length() - 1);
					return 2;
				}
			}
		}
		else {
			std::wsmatch results;
			if(!rev){
				lua_Wstring temp = text.substr(init);
				bool sresult = std::regex_search(temp, results, std::wregex(pattern));
				if (sresult) {
					lua_Integer n = results.position() + 1 + init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + results.length() - 1);
					return 2;
				}
			}
			else {
				lua_Wstring temp = text.substr(text.length() - init - 1);
				bool sresult = std::regex_search(temp, results, std::wregex(pattern));
				if (sresult) {
					lua_Integer n = results.position() + text.length() - init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + results.length() - 1);
					return 2;
				}
			}
		}
		return 0;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_sub(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Integer start = tm_tointeger(L, 2) - 1;
		lua_Integer end = tm_tointeger_s(L, 3, text.length()) - 1;

		lua_pushwstring(L, text.substr(start, end - start + 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_gsub(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Wstring pattern = tm_towstring(L, 2);
		lua_Wstring repl = tm_towstring(L, 3);
		lua_Integer num = tm_tointeger_s(L, 4, 1);

		for (int i = 0; i < num; i++)
		{
			std::wsmatch results;
			bool l = std::regex_search(text, results, std::wregex(pattern));

			if (l) {
				int s = results.position();
				int l = results.length();
				text = text.replace(s, l, repl);
			}
			else
				break;
		}
		lua_pushwstring(L, text);
		return 1;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_len(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_pushinteger(L, text.length());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_reverse(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Wstring ret;
		for (unsigned int i = 0; i < text.length(); i++)
			ret += text.substr(text.length() - i - 1, 1);

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_upper(lua_State* L) {
	try {
		lua_pushwstring(L, upperString(tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_lower(lua_State* L) {
	try {
		lua_pushwstring(L, lowerString(tm_towstring(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_match(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Wstring pattern = tm_towstring(L, 2);
		lua_Integer start = tm_tointeger_s(L, 3, 1) - 1;

		text = text.substr(start);
		std::wsmatch results;
		bool l = std::regex_search(text, results, std::wregex(pattern));

		if (l) {
			lua_pushwstring(L, results.str());
			return 1;
		}
		else
			return 0;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_byte(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);
		lua_Integer i = tm_tointeger_s(L, 2, 1) - 1;
		lua_Integer j = tm_tointeger_s(L, 3, 1) - 1;
		int length = text.length();

		if (length < 1)
			return 0;
		if (j < i)
			return 0;
		if (i >= length)
			return 0;
		if (j >= length)
			j = length - 1;

		for (int k = i; k <= j; k++)
		{
			unsigned long long c = text[k];
			lua_pushinteger(L, c);
		}
		return j - i + 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_char(lua_State* L) {
	try {
		int cnt = 1;
		std::vector<unsigned long long> list;

		while (true) {
			if (lua_type(L, cnt) == LUA_TNUMBER)
				list.push_back(lua_tonumber(L, cnt));
			else
				break;
			cnt++;
		}

		if (list.size() < 1)
			return 0;

		wchar_t temp;
		lua_Wstring ret;
		for (unsigned int i = 0; i < list.size(); i++)
		{
			temp = list[i];
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

int string_gmatch_aux(lua_State* L) {
	try {
		lua_Wstring s = lua_towstring(L, lua_upvalueindex(1));
		lua_Wstring pattern = lua_towstring(L, lua_upvalueindex(2));
		lua_Integer idx = lua_tointeger(L, lua_upvalueindex(3));
		std::wsmatch m;

		int len = s.length();
		int c = 0;
		for (int i = 0; i < len; i++) {
			if (std::regex_search(s, m, std::wregex(pattern))) {
				if (c == idx) {
					lua_pushinteger(L, idx + 1);
					lua_replace(L, lua_upvalueindex(3));
					lua_pushwstring(L, m.str());
					return 1;
				}

				c++;
				s = s.substr(m.position() + 1);
			}
		}

		return 0;
	}
	catch (std::regex_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_gmatch(lua_State* L) {
	try {
		luaL_checkstring(L, 1);
		luaL_checkstring(L, 2);
		lua_settop(L, 2);
		lua_pushinteger(L, 0);
		lua_pushcclosure(L, string_gmatch_aux, 3);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_rep(lua_State* L) {
	try {
		lua_Wstring s = tm_towstring(L, 1);
		lua_Integer n = tm_tointeger(L, 2);
		lua_Wstring ret;

		for (int i = 0; i < n; i++) {
			ret += s;
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_format(lua_State* L) {
	try {
		lua_Sstring str = tm_tosstring(L, 1);
		try {
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

			lua_pushsstring(L, fmt::vformat(str, store));
			return 1;
		}
		catch (fmt::format_error) {
			lua_pushsstring(L, str);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_dump_writer(lua_State* L, const void* b, size_t size, void* B) {
	(void)L;
	luaL_addlstring((luaL_Buffer*)B, (const char*)b, size);
	return 0;
}

int string_dump(lua_State* L) {
	luaL_Buffer b;
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_settop(L, 1);
	luaL_buffinit(L, &b);
	if (lua_dump(L, string_dump_writer, &b) != 0)
		luaL_error(L, "unable to dump given function");
	luaL_pushresult(&b);
	return 1;
}

void luaReg_string(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_STRING_REG);
		luaReg_tmstring(L);
		lua_setfield(L, -2, name);
	}
}