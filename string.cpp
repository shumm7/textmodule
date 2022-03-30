#include <lua.hpp>
#include <iostream>
#include <regex>
#include <fmt/core.h>
#include <fmt/format.h>
#include <vector>

#include "string.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_math.h"

int string_find(lua_State* L) {
	try {
		std::wstring text = tm_towstring(L, 1);
		std::wstring pattern = tm_towstring(L, 2);
		int init = tm_tointeger_s(L, 3, 1);
		bool plain = tm_toboolean_s(L, 4, false);
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
				std::wstring temp = text.substr(init);
				int pos = temp.find(pattern);
				if (pos!=std::string::npos) {
					int n = pos + 1 + init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + pattern.length() - 1);
					return 2;
				}
			}
			else {
				std::wstring temp = text.substr(text.length() - init - 1);
				int pos = temp.find(pattern);
				if (pos != std::string::npos) {
					int n = pos + text.length() - init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + pattern.length() - 1);
					return 2;
				}
			}
		}
		else {
			std::wsmatch results;
			if(!rev){
				std::wstring temp = text.substr(init);
				bool sresult = std::regex_search(temp, results, std::wregex(pattern));
				if (sresult) {
					int n = results.position() + 1 + init;
					lua_pushinteger(L, n);
					lua_pushinteger(L, n + results.length() - 1);
					return 2;
				}
			}
			else {
				std::wstring temp = text.substr(text.length() - init - 1);
				bool sresult = std::regex_search(temp, results, std::wregex(pattern));
				if (sresult) {
					int n = results.position() + text.length() - init;
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
		std::wstring text = tm_towstring(L, 1);
		int start = tm_tointeger(L, 2) - 1;
		int end = tm_tointeger_s(L, 3, text.length()) - 1;

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
		std::wstring text = tm_towstring(L, 1);
		std::wstring pattern = tm_towstring(L, 2);
		std::wstring repl = tm_towstring(L, 3);
		int num = tm_tointeger_s(L, 4, 1);

		for (int i = 0; i < num; i++)
		{
			std::wsmatch results;
			bool l = std::regex_search(text, results, std::wregex(pattern));

			if (l) {
				int s = results.position();
				int l = results.length();
				text = text.replace(s, l, repl);
			}
			else {
				break;
			}
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
		std::wstring text = tm_towstring(L, 1);

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
		std::wstring text = tm_towstring(L, 1);
		std::wstring ret;
		for (unsigned int i = 0; i < text.length(); i++)
		{
			ret += text.substr(text.length() - i - 1, 1);
		}

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
		std::wstring text = tm_towstring(L, 1);
		std::wstring pattern = tm_towstring(L, 2);
		int start = tm_tointeger_s(L, 3, 1) - 1;

		text = text.substr(start);
		std::wsmatch results;
		bool l = std::regex_search(text, results, std::wregex(pattern));

		if (l) {
			lua_pushwstring(L, results.str());
			return 1;
		}
		else {
			return 0;
		}
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
			if (lua_type(L, cnt) == LUA_TNUMBER) {
				list.push_back(lua_tonumber(L, cnt));
			}
			else {
				break;
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

int string_gmatch(lua_State* L) {
	try {
		std::wstring s = tm_towstring(L, 1);
		std::wstring pattern = tm_towstring(L, 2);
		std::wsmatch m;

		luaL_dostring(L, "function _TEXTMODULE_GMATCH_IFUNC(x) local pos,length=0,#x  return function()  pos = pos + 1  if pos>length then  return nil  else  return x[pos] end end end");
		lua_getglobal(L, "_TEXTMODULE_GMATCH_IFUNC");

		lua_newtable(L);
		if (std::regex_match(s, m, std::wregex(pattern))) {
			int size = m.size();

			for (int i = 0; i < size; i++)
			{
				lua_pushinteger(L, i + 1);
				lua_pushwstring(L, m[i].str());
				lua_settable(L, -3);
			}
		}

		lua_pcall(L, 1, 1, 0);
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

int string_split(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);
		std::wstring pattern = tm_towstring(L, 2);
		int n = tm_tonumber_s(L, 3, -1);

		std::wsmatch result;
		int count = 0;

		lua_newtable(L);
		while (std::regex_search(str, result, std::wregex(pattern)) && (count < n || n < 1)) {
			int p = result.position();
			lua_pushinteger(L, count + 1);
			lua_pushwstring(L, str.substr(0, p));
			lua_settable(L, -3);

			str = str.substr(p + result[0].str().length());
			count++;
		}
		if (str.length() > 0) {
			lua_pushinteger(L, count + 1);
			lua_pushwstring(L, str);
			lua_settable(L, -3);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_rep(lua_State* L) {
	try {
		std::wstring s = tm_towstring(L, 1);
		int n = tm_tointeger(L, 2);
		std::wstring ret;

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
		std::string str = tm_tosstring(L, 1);
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
				else
					return luaL_argerror(L, i, "format must be number/boolean/string/nil");

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

void luaReg_string(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_STRING_REG);
		lua_setfield(L, -2, name);
	}
}