#pragma once
#include <lua.hpp>

#define MECAB_PARAM_N 3
#define MECAB_PARAM_A MODULE_NAME
#define MECAB_PARAM_R "-r.\\textmodule\\MeCab\\etc\\mecabrc"
#define MECAB_PARAM_D "-d.\\textmodule\\MeCab\\dic\\ipadic"
#define MECAB_PARAM_O "-Ochasen"

int mecab_node(lua_State* L);
int mecab_ruby_h(lua_State* L);
int mecab_ruby_k(lua_State* L);
int mecab_yomi(lua_State* L);
int mecab_words(lua_State* L);

static luaL_Reg TEXTMODULE_MECAB_REG[]{
	{"node", mecab_node},
	{"ruby_h", mecab_ruby_h},
	{"ruby_k", mecab_ruby_k},
	{"yomi", mecab_yomi},
	{"words", mecab_words},
	{nullptr, nullptr}
};