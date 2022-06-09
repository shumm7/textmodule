#pragma once
#include "textmodule_lua.hpp"

std::pair<lua_Integer, lua_Integer> string_template_find(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Integer init, lua_Boolean plain);
std::pair<lua_Integer, lua_Integer> string_template_find(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Integer init, lua_Boolean plain);

lua_Sstring string_template_sub(lua_State* L, lua_Sstring text, lua_Integer start, lua_Integer end);
lua_Wstring string_template_sub(lua_State* L, lua_Wstring text, lua_Integer start, lua_Integer end);

lua_Sstring string_template_gsub(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Sstring repl, lua_Integer num);
lua_Wstring string_template_gsub(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Wstring repl, lua_Integer num);

size_t string_template_len(lua_State* L, lua_Sstring text);
size_t string_template_len(lua_State* L, lua_Wstring text);

lua_Sstring string_template_reverse(lua_State* L, lua_Sstring text);
lua_Wstring string_template_reverse(lua_State* L, lua_Wstring text);

lua_Sstring string_template_upper(lua_State* L, lua_Sstring text);
lua_Wstring string_template_upper(lua_State* L, lua_Wstring text);

lua_Sstring string_template_lower(lua_State* L, lua_Sstring text);
lua_Wstring string_template_lower(lua_State* L, lua_Wstring text);

lua_Sstring string_template_match(lua_State* L, lua_Sstring text, lua_Sstring pattern, lua_Integer start);
lua_Wstring string_template_match(lua_State* L, lua_Wstring text, lua_Wstring pattern, lua_Integer start);

std::vector<unsigned char> string_template_byte(lua_State* L, lua_Sstring text, lua_Integer i, lua_Integer j);
std::vector<wchar_t> string_template_byte(lua_State* L, lua_Wstring text, lua_Integer i, lua_Integer j);

lua_Sstring string_template_char(lua_State* L, std::vector<unsigned char> chars);
lua_Wstring string_template_char(lua_State* L, std::vector<wchar_t> chars);

lua_Sstring string_template_rep(lua_State* L, lua_Sstring s, lua_Integer n);
lua_Wstring string_template_rep(lua_State* L, lua_Wstring s, lua_Integer n);

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx);

luaL_Buffer* string_template_dump(lua_State* L);