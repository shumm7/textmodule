#include <lua.hpp>
#include <iostream>
#include <regex>

#include "string.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

int string_find(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
			return 0;
		}

		std::wstring text = lua_towstring(L, 1);
		std::wstring pattern = lua_towstring(L, 2);

		std::wsmatch results;
		bool l = std::regex_search(text, results, std::wregex(pattern));

		if (l) {
			lua_pushinteger(L, results.position() + 1);
			lua_pushinteger(L, results.position() + results.length());
			return 2;
		}
		else {
			return 0;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_sub(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TNUMBER) {
			return 0;
		}

		std::wstring text = lua_towstring(L, 1);
		int start = lua_tointeger(L, 2) - 1;
		int end;
		bool mode_last = false;

		if (lua_type(L, 3) == LUA_TNUMBER) {
			end = lua_tointeger(L, 3) - 1;
		}
		else if (lua_type(L, 3) != LUA_TNIL) {
			end = text.length() - 1;
		}
		else {
			return 0;
		}

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
		if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING || lua_type(L, 3) != LUA_TSTRING) {
			return 0;
		}

		std::wstring text = lua_towstring(L, 1);
		std::wstring pattern = lua_towstring(L, 2);
		std::wstring repl = lua_towstring(L, 3);
		int num;

		if (lua_type(L, 4) == LUA_TNUMBER) {
			num = lua_tointeger(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNIL || lua_type(L, 4) == LUA_TNONE) {
			num = 1;
		}
		else {
			return 0;
		}

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
			lua_pushwstring(L, text);
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_len(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}
		std::wstring text = lua_towstring(L, 1);

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
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}
		std::wstring text = lua_towstring(L, 1);
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
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}

		std::wstring text = lua_towstring(L, 1);
		std::wstring ret;
		for (unsigned int i = 0; i < text.length(); i++)
		{
			ret += toupper(text[i]);
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_lower(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}

		std::wstring text = StrToWstr(lua_tostring(L, 1));
		std::wstring ret;
		for (unsigned int i = 0; i < text.length(); i++)
		{
			ret += tolower(text[i]);
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_match(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}
		if (lua_type(L, 2) != LUA_TSTRING) {
			return 0;
		}
		std::wstring text = lua_towstring(L, 1);
		std::wstring pattern = lua_towstring(L, 2);

		int start;
		if (lua_type(L, 3) == LUA_TNUMBER) {
			start = lua_tointeger(L, 3) - 1;
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			start = 0;
		}
		else {
			return 0;
		}

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
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_byte(lua_State* L) {
	try {
		if (lua_type(L, 1) != LUA_TSTRING) {
			return 0;
		}
		std::wstring text = lua_towstring(L, 1);
		int i;
		int j;
		int length = text.length();

		if (lua_type(L, 2) == LUA_TNUMBER) {
			i = lua_tointeger(L, 2) - 1;
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			i = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			j = lua_tointeger(L, 3) - 1;
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			j = i;
		}
		else {
			return 0;
		}

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
			int tp = lua_type(L, cnt);

			if (tp == LUA_TNUMBER) {
				list.push_back(lua_tonumber(L, cnt));
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
		if (lua_type(L, 1) != LUA_TSTRING || lua_type(L, 2) != LUA_TSTRING) {
			return 0;
		}

		std::wstring s = lua_towstring(L, 1);
		std::wstring pattern = lua_towstring(L, 2);
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
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int string_split(lua_State* L) {
	try {
		std::wstring str;
		std::wstring pattern;
		int n;

		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TSTRING) {
			pattern = lua_towstring(L, 2);
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			n = lua_tonumber(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			n = -1;
		}
		else {
			return 0;
		}

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
		std::wstring s;
		int n;
		std::wstring ret;

		if (lua_type(L, 1) == LUA_TSTRING) {
			s = lua_towstring(L, 1);
		}
		else {
			return 0;
		}
		if (lua_type(L, 2) == LUA_TNUMBER) {
			n = lua_tointeger(L, 2);
		}
		else {
			return 0;
		}

		if (n < 1) {
			lua_pushwstring(L, L"");
			return 1;
		}


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

void luaReg_string(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_STRING_REG);
		lua_setfield(L, -2, name);
	}
}