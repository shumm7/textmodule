#include <lua.hpp>
#include <iostream>
#include <regex>

#include "obj.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_math.h"

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

int obj_remove_ctrl(lua_State* L) {
	try {
		std::wstring str = tm_towstring(L, 1);
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
		std::wstring str = tm_towstring(L, 1);
		int idx = tm_tointeger_s(L, 2, 1);
		std::wsmatch results;

		if (idx > 0) {
			int pivot = 1;
			for (int i = 0; i < str.length(); i++) {
				std::wstring temp = str.substr(i);
				bool sresult = std::regex_search(temp, results, std::wregex(REG_CTRL));

				if (sresult) {
					int n = results.position() + 1 + i;
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
			int count = 0;
			for (int i = 0; i < str.length(); i++) {
				std::wstring temp = str.substr(i);
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

int obj_cbool(lua_State* L) {
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

void luaReg_obj(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_OBJ_REG);

		luaReg_const_figure(L, "figure");
		luaReg_const_object(L, "object");

		lua_setfield(L, -2, name);
	}
}