#include "string_aux.hpp"

#include <iostream>
#include <regex>
#include <vector>
#include <utility>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

std::pair<lua_Integer, lua_Integer> string_template_find(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Integer init, lua_Boolean plain) {
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
		return { -1, -1 };

	if (plain) {
		if (!rev) {
			lua_Sstring temp = text.substr(init);
			int pos = temp.find(pattern);
			if (pos != std::string::npos) {
				lua_Integer n = pos + 1 + init;
				return { n, n + pattern.length() - 1 };
			}
		}
		else {
			lua_Sstring temp = text.substr(text.length() - init - 1);
			int pos = temp.find(pattern);
			if (pos != std::string::npos) {
				lua_Integer n = pos + text.length() - init;
				return { n, n + pattern.length() - 1 };
			}
		}
	}
	else {
		std::smatch results;
		if (!rev) {
			lua_Sstring temp = text.substr(init);
			bool sresult = std::regex_search(temp, results, std::regex(pattern));
			if (sresult) {
				lua_Integer n = results.position() + 1 + init;
				return { n, n + results.length() - 1 };
			}
		}
		else {
			lua_Sstring temp = text.substr(text.length() - init - 1);
			bool sresult = std::regex_search(temp, results, std::regex(pattern));
			if (sresult) {
				lua_Integer n = results.position() + text.length() - init;
				return { n, n + results.length() - 1 };
			}
		}
	}

	return { -1, -1 };
}

std::pair<lua_Integer, lua_Integer> string_template_find(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Integer init, lua_Boolean plain) {
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
		return {-1, -1};

	if (plain) {
		if (!rev) {
			lua_Wstring temp = text.substr(init);
			int pos = temp.find(pattern);
			if (pos != std::string::npos) {
				lua_Integer n = pos + 1 + init;
				return {n, n + pattern.length() - 1 };
			}
		}
		else {
			lua_Wstring temp = text.substr(text.length() - init - 1);
			int pos = temp.find(pattern);
			if (pos != std::wstring::npos) {
				lua_Integer n = pos + text.length() - init;
				return { n, n + pattern.length() - 1 };
			}
		}
	}
	else {
		std::wsmatch results;
		if (!rev) {
			lua_Wstring temp = text.substr(init);
			bool sresult = std::regex_search(temp, results, std::wregex(pattern));
			if (sresult) {
				lua_Integer n = results.position() + 1 + init;
				return { n, n + results.length() - 1 };
			}
		}
		else {
			lua_Wstring temp = text.substr(text.length() - init - 1);
			bool sresult = std::regex_search(temp, results, std::wregex(pattern));
			if (sresult) {
				lua_Integer n = results.position() + text.length() - init;
				return { n, n + results.length() - 1 };
			}
		}
	}

	return {-1, -1};
}

lua_Sstring string_template_sub(lua_State* L, lua_Sstring text, lua_Integer start, lua_Integer end) {
	return text.substr(start, end - start + 1);
}

lua_Wstring string_template_sub(lua_State* L, lua_Wstring text, lua_Integer start, lua_Integer end) {
	return text.substr(start, end - start + 1);
}

lua_Sstring string_template_gsub(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Sstring repl, lua_Integer num) {
	for (int i = 0; i < num; i++)
	{
		std::smatch results;
		bool l = std::regex_search(text, results, std::regex(pattern));

		if (l) {
			int s = results.position();
			int l = results.length();
			text = text.replace(s, l, repl);
		}
		else
			break;
	}
	return text;
}

lua_Wstring string_template_gsub(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Wstring repl, lua_Integer num) {
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
	return text;
}

size_t string_template_len(lua_State* L, lua_Sstring text) {
	return text.length();
}

size_t string_template_len(lua_State* L, lua_Wstring text) {
	return text.length();
}

lua_Sstring string_template_reverse(lua_State* L, lua_Sstring text) {
	lua_Sstring ret;
	for (unsigned int i = 0; i < text.length(); i++)
		ret += text.substr(text.length() - i - 1, 1);
	return ret;
}

lua_Wstring string_template_reverse(lua_State* L, lua_Wstring text) {
	lua_Wstring ret;
	for (unsigned int i = 0; i < text.length(); i++)
		ret += text.substr(text.length() - i - 1, 1);
	return ret;
}

lua_Sstring string_template_upper(lua_State* L, lua_Sstring text) {
	return upperString(text);
}

lua_Wstring string_template_upper(lua_State* L, lua_Wstring text) {
	return upperString(text);
}

lua_Sstring string_template_lower(lua_State* L, lua_Sstring text) {
	return lowerString(text);
}

lua_Wstring string_template_lower(lua_State* L, lua_Wstring text) {
	return lowerString(text);
}

lua_Sstring string_template_match(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Integer start) {
	text = text.substr(start);
	std::smatch results;
	bool l = std::regex_search(text, results, std::regex(pattern));

	if (l)
		return results.str();
	else
		throw std::regex_error(std::regex_constants::error_ctype);
}

lua_Wstring string_template_match(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Integer start) {
	text = text.substr(start);
	std::wsmatch results;
	bool l = std::regex_search(text, results, std::wregex(pattern));

	if (l)
		return results.str();
	else
		throw std::regex_error(std::regex_constants::error_ctype);
}

std::vector<unsigned char> string_template_byte(lua_State* L, lua_Sstring text, lua_Integer i, lua_Integer j) {
	int length = text.length();
	std::vector<unsigned char> ret;

	if (length < 1)
		return ret;
	if (j < i)
		return ret;
	if (i >= length)
		return ret;
	if (j >= length)
		j = length - 1;

	for (int k = i; k <= j; k++)
		ret.push_back(text[k]);
	return ret;
}

std::vector<wchar_t> string_template_byte(lua_State* L, lua_Wstring text, lua_Integer i, lua_Integer j) {
	int length = text.length();
	std::vector<wchar_t> ret;

	if (length < 1)
		return ret;
	if (j < i)
		return ret;
	if (i >= length)
		return ret;
	if (j >= length)
		j = length - 1;

	for (int k = i; k <= j; k++)
		ret.push_back(text[k]);
	return ret;
}

lua_Sstring string_template_char(lua_State* L, std::vector<unsigned char> chars) {
	lua_Sstring ret;
	for (int i = 0; i < chars.size(); i++)
		ret += chars[i];
	return ret;
}

lua_Wstring string_template_char(lua_State* L, std::vector<wchar_t> chars) {
	lua_Wstring ret;
	for (int i = 0; i < chars.size(); i++)
		ret += chars[i];
	return ret;
}

lua_Sstring string_template_rep(lua_State* L, lua_Sstring s, lua_Integer n) {
	lua_Sstring ret;

	for (int i = 0; i < n; i++)
		ret += s;
	return ret;
}

lua_Wstring string_template_rep(lua_State* L, lua_Wstring s, lua_Integer n) {
	lua_Wstring ret;

	for (int i = 0; i < n; i++)
		ret += s;
	return ret;
}

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx) {
	try {
		fmt::dynamic_format_arg_store<fmt::format_context> store;

		int i = idx + 1;
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

		return fmt::vformat(str, store);
	}
	catch (fmt::format_error) {
		return str;
	}
}

int string_dump_writer(lua_State* L, const void* b, size_t size, void* B) {
	(void)L;
	luaL_addlstring((luaL_Buffer*)B, (const char*)b, size);
	return 0;
}

luaL_Buffer* string_template_dump(lua_State* L) {
	luaL_Buffer b;
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_settop(L, 1);
	luaL_buffinit(L, &b);
	if (lua_dump(L, string_dump_writer, &b) != 0)
		luaL_error(L, "unable to dump given function");
	return &b;
}