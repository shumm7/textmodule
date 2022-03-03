#include <lua.hpp>
#include <iostream>
#include <mecab.h>
#include <exception>
#include <vector>
#include <filesystem>

#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule.h"

#pragma comment(lib, "libmecab.lib")

#define MECAB_PARAM_N 3
#define MECAB_PARAM_A MODULE_NAME
#define MECAB_PARAM_R "-r.\\textmodule\\MeCab\\etc\\mecabrc"
#define MECAB_PARAM_D "-d.\\textmodule\\MeCab\\dic\\ipadic"

void mecab_check(MeCab::Model* model) {
	if (model == nullptr) {
		throw std::exception(MeCab::getLastError());
	}
}

void mecab_check(MeCab::Tagger* tagger) {
	if (tagger == nullptr) {
		throw std::exception(MeCab::getLastError());
	}
}

void mecab_check(const MeCab::Node* node) {
	if (node == nullptr) {
		throw std::exception(MeCab::getLastError());
	}
}

const MeCab::Node* mecab_getNode(MeCab::Tagger* tagger, std::wstring w_input) {
	std::string input = WstrToStr(w_input);

	char buf[LUAL_BUFFERSIZE];
	if (input.size() < LUAL_BUFFERSIZE) {
		std::char_traits<char>::copy(buf, input.c_str(), input.size() + 1);
	}
	else {
		throw std::exception();
	}

	mecab_check(tagger);
	const MeCab::Node* node = tagger->parseToNode(buf);
	mecab_check(node);

	return node;
}

std::wstring mecab_getYomigana(MeCab::Tagger* tagger, std::wstring w_input) {
	mecab_check(tagger);

	const MeCab::Node* node = mecab_getNode(tagger, w_input);
	mecab_check(node);

	std::wstring res;
	for (; node; node = node->next) {
		std::vector<std::wstring> v = split(StrToWstr(node->feature), L',');
		if (v.size() != 1) {
			if(v[0]!=L"BOS/EOS")
				res += v[7];
		}
	}

	return res;
}

int mecab_node(lua_State* L) {
	try {
		std::wstring text;
		if (lua_type(L, 1) == LUA_TSTRING) {
			text = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		const MeCab::Node* node = mecab_getNode(tagger, text);
		mecab_check(node);

		int i = 1;
		lua_newtable(L);
		for (; node; node = node->next) {
			lua_pushinteger(L, i);
			lua_newtable(L);

			//id
			lua_pushinteger(L, node->id);
			lua_setfield(L, -2, "id");

			//surface
			lua_pushstring(L, node->surface);
			lua_setfield(L, -2, "surface");

			//feature
			{
				std::vector<std::wstring> v = split(StrToWstr(node->feature), L',');
				lua_newtable(L);
				for (int i = 0; i < v.size(); i++) {
					lua_pushinteger(L, i + 1);
					lua_pushwstring(L, v[i]);
					lua_settable(L, -3);
				}
				lua_pushinteger(L, 0);
				lua_pushstring(L, node->feature);
				lua_settable(L, -3);
			}
			lua_setfield(L, -2, "feature");

			//length
			lua_pushinteger(L, node->length);
			lua_setfield(L, -2, "length");

			//rlength
			lua_pushinteger(L, node->rlength);
			lua_setfield(L, -2, "rlength");

			//rcAttr
			lua_pushinteger(L, node->rcAttr);
			lua_setfield(L, -2, "rcAttr");

			//lcAttr
			lua_pushinteger(L, node->lcAttr);
			lua_setfield(L, -2, "lcAttr");

			//posid
			lua_pushinteger(L, node->posid);
			lua_setfield(L, -2, "posid");

			//char_type
			lua_pushinteger(L, node->char_type);
			lua_setfield(L, -2, "char_type");

			//stat
			lua_pushinteger(L, node->rlength);
			lua_setfield(L, -2, "stat");

			//isbest
			lua_pushinteger(L, node->isbest);
			lua_setfield(L, -2, "isbest");

			//alpha
			lua_pushnumber(L, node->alpha);
			lua_setfield(L, -2, "alpha");

			//beta
			lua_pushnumber(L, node->beta);
			lua_setfield(L, -2, "beta");

			//prob
			lua_pushnumber(L, node->prob);
			lua_setfield(L, -2, "prob");

			//cost
			lua_pushinteger(L, node->cost);
			lua_setfield(L, -2, "cost");

			lua_settable(L, -3);
			i++;
		}

		delete model;
		delete tagger;
		delete node;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int mecab_yomi_hiragana(lua_State* L) {
	try {
		std::wstring text;
		if (lua_type(L, 1) == LUA_TSTRING) {
			text = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		std::wstring yomiKatakana = mecab_getYomigana(tagger, text);
		lua_pushwstring(L, toKatakana(yomiKatakana, true));

		delete model;
		delete tagger;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int mecab_yomi_katakana(lua_State* L) {
	try {
		std::wstring text;
		if (lua_type(L, 1) == LUA_TSTRING) {
			text = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		std::wstring yomiKatakana = mecab_getYomigana(tagger, text);
		lua_pushwstring(L, toKatakana(yomiKatakana, false));

		delete model;
		delete tagger;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int mecab_words(lua_State* L) {
	try {
		std::wstring text;
		if (lua_type(L, 1) == LUA_TSTRING) {
			text = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		const MeCab::Node* node = mecab_getNode(tagger, text);
		mecab_check(node);

		int i = 1;
		lua_newtable(L);
		for (; node; node = node->next) {
			std::vector<std::wstring> v = split(StrToWstr(node->feature), L',');
			lua_pushinteger(L, i);
			lua_pushwstring(L, v[7]);
			lua_settable(L, -3);
			i++;
		}
		
		delete model;
		delete tagger;
		delete node;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}