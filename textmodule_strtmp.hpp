#pragma once
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

template <typename String>
std::pair<lua_Integer, lua_Integer> string_template_find(lua_State* L, String text, String pattern, lua_Integer init, lua_Boolean plain) {
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
			String temp = text.substr(init);
			int pos = temp.find(pattern);
			if (pos != String::npos) {
				lua_Integer n = pos + 1 + init;
				return { n, n + pattern.length() - 1 };
			}
		}
		else {
			String temp = text.substr(text.length() - init - 1);
			int pos = temp.find(pattern);
			if (pos != String::npos) {
				lua_Integer n = pos + text.length() - init;
				return { n, n + pattern.length() - 1 };
			}
		}
	}
	else {
		std::match_results<String::const_iterator> results;
		if (!rev) {
			String temp = text.substr(init);
			bool sresult = std::regex_search(temp, results, std::basic_regex<String::value_type>(pattern));
			if (sresult) {
				lua_Integer n = results.position() + 1 + init;
				return { n, n + results.length() - 1 };
			}
		}
		else {
			String temp = text.substr(text.length() - init - 1);
			bool sresult = std::regex_search(temp, results, std::basic_regex<String::value_type>(pattern));
			if (sresult) {
				lua_Integer n = results.position() + text.length() - init;
				return { n, n + results.length() - 1 };
			}
		}
	}

	return { -1, -1 };
}

template <typename String>
String string_template_sub(lua_State* L, String text, lua_Integer start, lua_Integer end) {
	return text.substr(start, end - start + 1);
}

template <typename String>
String string_template_gsub(lua_State* L, String text, String pattern, String repl, lua_Integer num) {
	for (int i = 0; i < num; i++)
	{
		std::match_results<String::const_iterator> results;
		bool l = std::regex_search(text, results, std::basic_regex<String::value_type>(pattern));

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

template <typename String>
size_t string_template_len(lua_State* L, String text) {
	return text.length();
}

template <typename String>
String string_template_reverse(lua_State* L, String text) {
	String ret;
	for (unsigned int i = 0; i < text.length(); i++)
		ret += text.substr(text.length() - i - 1, 1);
	return ret;
}

template <typename String>
String string_template_upper(lua_State* L, String text) {
	std::transform(text.cbegin(), text.cend(), text.begin(), toupper);
	return text;
}

template <typename String>
String string_template_lower(lua_State* L, String text) {
	std::transform(text.cbegin(), text.cend(), text.begin(), tolower);
	return text;
}

template <typename String>
String string_template_match(lua_State* L, String text, String pattern, lua_Integer start) {
	text = text.substr(start);
	std::match_results<String::const_iterator> results;
	bool l = std::regex_search(text, results, std::basic_regex<String::value_type>(pattern));

	if (l)
		return results.str();
	else
		throw std::regex_error(std::regex_constants::error_ctype);
}

template <typename String>
auto string_template_byte(lua_State* L, String text, lua_Integer i, lua_Integer j) {
	int length = text.length();
	std::vector<String::value_type> ret;
	
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

template <typename String>
String string_template_char(lua_State* L, std::vector<uint32_t> chars) {
	String ret;
	for (int i = 0; i < chars.size(); i++)
		ret += chars[i];
	return ret;
}

template <typename String>
String string_template_rep(lua_State* L, String s, lua_Integer n) {
	String ret;

	for (int i = 0; i < n; i++)
		ret += s;
	return ret;
}

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx);

lua_Wstring string_template_format(lua_State* L, lua_Wstring str, int idx);

luaL_Buffer* string_template_dump(lua_State* L);