#include "mecab.hpp"

#include <lua.hpp>
#include <iostream>
#include <exception>
#include <vector>
#include <filesystem>
#include <mecab.h>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule.hpp"

#pragma comment(lib, "libmecab.lib")

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

const MeCab::Node* mecab_getNode(MeCab::Tagger* tagger, lua_Wstring w_input) {
	lua_Sstring input = WstrToStr(w_input);

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

lua_Wstring mecab_getRuby(MeCab::Tagger* tagger, lua_Wstring w_input) {
	mecab_check(tagger);

	const MeCab::Node* node = mecab_getNode(tagger, w_input);
	mecab_check(node);

	lua_Wstring res;
	for (; node; node = node->next) {
		std::vector<lua_Wstring> v = split(StrToWstr(node->feature), L',');
		if (v.size() != 1) {
			if(v[0]!=L"BOS/EOS")
				res += v[7];
		}
	}

	return res;
}

lua_Wstring mecab_getYomi(MeCab::Tagger* tagger, lua_Wstring w_input) {
	mecab_check(tagger);

	const MeCab::Node* node = mecab_getNode(tagger, w_input);
	mecab_check(node);

	lua_Wstring res;
	for (; node; node = node->next) {
		std::vector<lua_Wstring> v = split(StrToWstr(node->feature), L',');
		if (v.size() != 1) {
			if (v[0] != L"BOS/EOS")
				res += v[8];
		}
	}

	return res;
}


int mecab_node(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);

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

			{
				std::vector<lua_Wstring> v = split(StrToWstr(node->feature), L',');
				lua_newtable(L);
				for (int i = 0; i < v.size(); i++)
					lua_settablevalue(L, i + 1, v[i]);
				lua_settablevalue(L, 0, node->feature);
			}
			lua_setfield(L, -2, "feature"); //feature

			lua_settablevalue(L, "id", (lua_Integer)node->id); //id
			lua_settablevalue(L, "surface", node->surface); //surface
			lua_settablevalue(L, "length", (lua_Integer)node->length); //length
			lua_settablevalue(L, "rlength", (lua_Integer)node->rlength); //rlength
			lua_settablevalue(L, "rcAttr", (lua_Integer)node->rcAttr); //rcAttr
			lua_settablevalue(L, "lcAttr", (lua_Integer)node->lcAttr); //lcAttr
			lua_settablevalue(L, "posid", (lua_Integer)node->posid); //posid
			lua_settablevalue(L, "char_type", (lua_Integer)node->char_type); //char_type
			lua_settablevalue(L, "stat", (lua_Integer)node->stat); //stat
			lua_settablevalue(L, "isbest", (lua_Integer)node->isbest); //isbest
			lua_settablevalue(L, "alpha", (lua_Number)node->alpha); //alpha
			lua_settablevalue(L, "beta", (lua_Number)node->beta); //beta
			lua_settablevalue(L, "prob", (lua_Number)node->prob); //prob
			lua_settablevalue(L, "cost", (lua_Integer)node->cost); //cost

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

int mecab_ruby_h(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		std::wstring yomi = mecab_getRuby(tagger, text);
		lua_pushwstring(L, yomi);

		delete model;
		delete tagger;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int mecab_ruby_k(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		std::wstring yomi = mecab_getRuby(tagger, text);
		lua_pushustring(L, HiraganaToKatakana(WstrToUstr(yomi)));

		delete model;
		delete tagger;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int mecab_yomi(lua_State* L) {
	try {
		lua_Wstring text = tm_towstring(L, 1);

		char* c[MECAB_PARAM_N] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		std::wstring yomi = mecab_getYomi(tagger, text);
		lua_pushwstring(L, yomi);

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
		lua_Wstring text = tm_towstring(L, 1);

		char* c[MECAB_PARAM_N+1] = {
		const_cast<char*>(MECAB_PARAM_A),
		const_cast<char*>(MECAB_PARAM_R),
		const_cast<char*>(MECAB_PARAM_D),
		const_cast<char*>("-Owakati")
		};

		MeCab::Model* model = MeCab::Model::create(MECAB_PARAM_N+1, c);
		mecab_check(model);
		MeCab::Tagger* tagger = model->createTagger();
		mecab_check(tagger);
		lua_Sstring val = tagger->parse(WstrToStr(text).c_str());

		lua_newtable(L);
		std::vector<lua_Wstring> v = split(StrToWstr(val), L' ');

		for (int i = 0; i < v.size(); ++i) {
			if (v[i] != L"" && v[i] != L"\n") {
				lua_settablevalue(L, i + 1, v[i]);
			}
		}

		delete model;
		delete tagger;
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}