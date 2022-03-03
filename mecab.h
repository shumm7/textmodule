#include <lua.hpp>
#include <iostream>

int mecab_node(lua_State* L);
int mecab_yomi_hiragana(lua_State* L);
int mecab_yomi_katakana(lua_State* L);
int mecab_words(lua_State* L);

static luaL_Reg TEXTMODULE_MECAB_REG[]{
	{"node", mecab_node},
	{"yomigana", mecab_yomi_hiragana},
	{"yomi_hiragana", mecab_yomi_hiragana},
	{"yomi_katakana", mecab_yomi_katakana},
	{"words", mecab_words},
	{nullptr, nullptr}
};