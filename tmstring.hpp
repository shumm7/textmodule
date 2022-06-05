#pragma once
#include <lua.hpp>
#include <iostream>

int tmstring_hiragana(lua_State* L);
int tmstring_katakana(lua_State* L);
int tmstring_halfwidth(lua_State* L);
int tmstring_fullwidth(lua_State* L);
int tmstring_fromlatin_h(lua_State* L);
int tmstring_fromlatin_k(lua_State* L);
int tmstring_latin_h(lua_State* L);
int tmstring_latin_k(lua_State* L);

int tmstring_split(lua_State* L);
int tmstring_mojibake(lua_State* L);
int tmstring_swapcase(lua_State* L);
int tmstring_left(lua_State* L);
int tmstring_right(lua_State* L);
int tmstring_shift(lua_State* L);
int tmstring_wshift(lua_State* L);
int tmstring_squeeze(lua_State* L);
int tmstring_capitalize(lua_State* L);
int tmstring_capitalize_words(lua_State* L);
int tmstring_random(lua_State* L);
int tmstring_anagram(lua_State* L);
int tmstring_gsplit(lua_State* L);
int tmstring_lines(lua_State* L);
int tmstring_character(lua_State* L);
int tmstring_count(lua_State* L);

void luaReg_const_tmstring(lua_State* L);

static luaL_Reg TEXTMODULE_TMSTRING_REG[] = {
	{"hiragana", tmstring_hiragana},
	{"katakana", tmstring_katakana},
	{"halfwidth", tmstring_halfwidth},
	{"fullwidth", tmstring_fullwidth},
	{"fromlatin_h", tmstring_fromlatin_h},
	{"fromlatin_k", tmstring_fromlatin_k},
	{"latin_h", tmstring_latin_h},
	{"latin_k", tmstring_latin_k},

	{"split", tmstring_split},
	{"mojibake", tmstring_mojibake},
	{"swapcase", tmstring_swapcase},
	{"left", tmstring_left},
	{"right", tmstring_right},
	{"shift", tmstring_shift},
	{"wshift", tmstring_wshift},
	{"squeeze", tmstring_squeeze},
	{"capitalize", tmstring_capitalize},
	{"capitalize_words", tmstring_capitalize_words},
	{"random", tmstring_random},
	//{"roundnumber",  tmstring_roundnumber},
	{"anagram", tmstring_anagram},
	{"gsplit", tmstring_gsplit},
	{"lines", tmstring_lines},
	{"character", tmstring_character},
	{"count", tmstring_count},
	{ nullptr, nullptr }
};