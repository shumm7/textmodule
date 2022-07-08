#include "obj.hpp"

#include <lua.hpp>
#include <iostream>
#include <regex>
#include <vector>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_math.hpp"

#define HEX6 "[0-9a-f]{6}"
#define INTN "[0-9]*?"
#define NUMP "(?:[0-9]+[.]?[0-9]*|[.][0-9]+)"
#define NUMN "([+-]?(?:[0-9]+[.]?[0-9]*|[.][0-9]+))"

#define REG_CTRL_SHARP L"(<#>|<#" HEX6 ">|<#" HEX6 "," HEX6 ">)"
#define REG_CTRL_S L"(<s(|" INTN ")>|<s(|" INTN "),([^,]*?)>|<s(|" INTN "),(.*),(|[BI])*>)"
#define REG_CTRL_R L"(<r>|<r" NUMP ">)"
#define REG_CTRL_W L"(<w>|<w[*]?" NUMP ">)"
#define REG_CTRL_C L"(<c>|<c[*]?" NUMP ">)"
#define REG_CTRL_P L"(<p" NUMN "?," NUMN "?>|<p" NUMN "?," NUMN "?," NUMN "?>)"
#define REG_CTRL_QUESTION L"(<[\?](.*?)[\?]>)"
#define REG_CTRL L"(" REG_CTRL_SHARP L"|" REG_CTRL_S L"|" REG_CTRL_R L"|" REG_CTRL_W L"|" REG_CTRL_C L"|" REG_CTRL_P L"|" REG_CTRL_QUESTION L")"

#define FIGURE_BACKGROUND "背景"
#define FIGURE_CIRCLE "円"
#define FIGURE_SQUARE "四角形"
#define FIGURE_TRIANGLE "三角形"
#define FIGURE_PENTAGON "五角形"
#define FIGURE_HEXAGON "六角形"
#define FIGURE_STAR "星型"

typedef struct {};

int font_count = 0;


int obj_remove_ctrl(lua_State* L) {
	try {
		lua_Wstring str = tm_towstring(L, 1);
		str = std::regex_replace(str, std::wregex(REG_CTRL), L"");

		lua_pushwstring(L, str);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int obj_find_ctrl(lua_State* L) {
	try {
		lua_Wstring str = tm_towstring(L, 1);
		lua_Integer idx = tm_tointeger_s(L, 2, 1);
		std::wsmatch results;

		if (idx > 0) {
			int pivot = 1;
			for (int i = 0; i < str.length(); i++) {
				std::wstring temp = str.substr(i);
				bool sresult = std::regex_search(temp, results, std::wregex(REG_CTRL));

				if (sresult) {
					lua_Integer n = results.position() + 1 + i;
					if (pivot == idx) {
						lua_pushinteger(L, n);
						lua_pushinteger(L, n + results.length() - 1);
						return 2;
					}
					else {
						i = n + results.length() - 2;
						pivot++;
					}
				}
				else
					break;
			}
		}
		else if (idx == 0) {
			lua_Integer count = 0;
			for (int i = 0; i < str.length(); i++) {
				lua_Wstring temp = str.substr(i);
				bool sresult = std::regex_search(temp, results, std::wregex(REG_CTRL));

				if (sresult) {
					int n = results.position() + 1 + i;
					i = n + results.length() - 2;
					count++;
				}
				else
					break;
			}

			lua_pushnumber(L, count);
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int obj_boolean(lua_State* L) {
	try {
		std::string str;
		switch (lua_type(L, 1))
		{
		case LUA_TNUMBER:
			if (tm_tonumber(L, 1) == 0)
				lua_pushboolean(L, false);
			else
				lua_pushboolean(L, true);
			return 1;
		case LUA_TSTRING:
			if (std::string(tm_tostring(L, 1)).length()<=0)
				lua_pushboolean(L, false);
			else
				lua_pushboolean(L, true);
			return 1;
		case LUA_TBOOLEAN:
			lua_pushboolean(L, tm_toboolean(L, 1));
			return 1;
		case LUA_TNIL:
		case LUA_TNONE:
			lua_pushboolean(L, false);
			return 1;
		default:
			lua_pushboolean(L, true);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_const_figure(lua_State* L, const char* name) {
	lua_newtable(L);

	lua_settablevalue(L, "background", FIGURE_BACKGROUND);
	lua_settablevalue(L, "circle", FIGURE_CIRCLE);
	lua_settablevalue(L, "square", FIGURE_SQUARE);
	lua_settablevalue(L, "triangle", FIGURE_TRIANGLE);
	lua_settablevalue(L, "pentagon", FIGURE_PENTAGON);
	lua_settablevalue(L, "hexagon", FIGURE_HEXAGON);
	lua_settablevalue(L, "star", FIGURE_STAR);

	lua_setfield(L, -2, name);
}

void luaReg_const_object(lua_State* L, const char* name) {
	lua_newtable(L);

	lua_settablevalue(L, "standard", "標準描画");
	lua_settablevalue(L, "advanced", "拡張描画");
	lua_settablevalue(L, "movie", "動画ファイル");
	lua_settablevalue(L, "image", "画像ファイル");
	lua_settablevalue(L, "audio", "音声ファイル");
	lua_settablevalue(L, "text", "テキスト");
	lua_settablevalue(L, "figure", "図形");
	lua_settablevalue(L, "framebuffer", "フレームバッファ");
	lua_settablevalue(L, "wave", "音声波形表示");
	lua_settablevalue(L, "scene", "シーン");
	lua_settablevalue(L, "scene_audio", "シーン(音声)");
	lua_settablevalue(L, "before", "直前オブジェクト");
	lua_settablevalue(L, "particle", "パーティクル出力");
	lua_settablevalue(L, "custom_object", "カスタムオブジェクト");
	lua_settablevalue(L, "time", "時間制御");
	lua_settablevalue(L, "group", "グループ制御");
	lua_settablevalue(L, "camera", "カメラ制御");
	lua_settablevalue(L, "camera_effect", "カメラ効果");
	lua_settablevalue(L, "effect", "フィルタ効果");
	lua_settablevalue(L, "filter", "フィルタオブジェクト");

	lua_setfield(L, -2, name);
}

void luaReg_const_blend(lua_State* L, const char* name) {
	lua_newtable(L);

	lua_settablevalue(L, "normal", 0);
	lua_settablevalue(L, "add", 1);
	lua_settablevalue(L, "subtract", 2);
	lua_settablevalue(L, "multiply", 3);
	lua_settablevalue(L, "screen", 4);
	lua_settablevalue(L, "overray", 5);
	lua_settablevalue(L, "lighten", 6);
	lua_settablevalue(L, "darken", 7);
	lua_settablevalue(L, "luminosity", 8);
	lua_settablevalue(L, "color_difference", 9);
	lua_settablevalue(L, "shadow", 10);
	lua_settablevalue(L, "contrast", 11);
	lua_settablevalue(L, "difference", 12);

	lua_setfield(L, -2, name);
}


static luaL_Reg TEXTMODULE_OBJ_REG[] = {
	{"remove_ctrl", obj_remove_ctrl},
	{"find_ctrl", obj_find_ctrl},
	{"boolean", obj_boolean},
	{nullptr, nullptr}
};

void luaReg_obj(lua_State* L, lua_Option opt) {
	if (opt["api"]["object"]) {
		tm_debuglog_apiloaded(opt, "object");

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_OBJ_REG);

		luaReg_const_figure(L, "figure");
		luaReg_const_object(L, "object");
		luaReg_const_blend(L, "blend");

		lua_setfield(L, -2, "object");
	}
	else {
		tm_debuglog_apinoloaded(opt, "object");
	}
}