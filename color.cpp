#include <lua.hpp>
#include <csv.h>
#include <vector>
#include <fstream>

#include "color.h"
#include "rgb.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_color.h"

#define LIST_DIRECTORY ".\\textmodule\\color\\"

#define SEARCHMODE_FULL 0
#define SEARCHMODE_PART 1
#define SEARCHMODE_FORWARD 2
#define SEARCHMODE_BACK 3

enum Target {
	color = 1<<0,
	name = 1<<1,
	japanese = 1<<2,
	english = 1<<3
};

std::string get_colorlistmsg() {
	std::string t = TEXTMODULE_COLORLIST;
	t += " expected";
	return t;
}

void getlist(std::string listname, ColorList* list) {
	std::string dir = LIST_DIRECTORY + listname + ".csv";
	io::CSVReader<4> ls(dir);

	std::string color;
	std::string name;
	std::string japanese;
	std::string english;

	ls.read_header(io::ignore_extra_column, "color", "name", "japanese", "english");

	while (ls.read_row(color, name, japanese, english)) {
		ColorItem c;
		c.color = StrToWstr(color);
		c.name = StrToWstr(name);
		c.japanese = StrToWstr(japanese);
		c.english = StrToWstr(english);

		list->push_back(c);
	}
}

void search(ColorList* list, std::wstring searchWord, int searchMode, ColorList* ret, int searchTarget) {
	std::wstring sw = searchWord;
	int st = searchTarget;

	if (sw == L"") {
		return;
	}

	for (int i = 0; i < list->size(); i++) {
		ColorItem p = list->at(i);
		if (searchMode == SEARCHMODE_FULL) {
			if (p.color == sw && (st & Target::color)
				|| p.name == sw && (st & Target::name)
				|| p.japanese == sw && (st & Target::japanese)
				|| p.english == sw && (st & Target::english)
			)
				ret->push_back(p);
		}
		else if (searchMode == SEARCHMODE_PART) {
			if (p.color.find(sw) != std::string::npos && (st & Target::color)
				|| p.name.find(sw) != std::string::npos && (st & Target::name)
				|| p.japanese.find(sw) != std::string::npos && (st & Target::japanese)
				|| p.english.find(sw) != std::string::npos && (st & Target::english)
			)
				ret->push_back(p);
		}
		else if (searchMode == SEARCHMODE_FORWARD) {
			if (p.color.find(sw) == 0 && (st & Target::color)
				|| p.name.find(sw)==0 && (st & Target::name)
				|| p.japanese.find(sw)==0 && (st & Target::japanese)
				|| p.english.find(sw)==0 && (st & Target::english)
			)
				ret->push_back(p);
		}
		else if (searchMode == SEARCHMODE_BACK) {
			if( (p.color.rfind(sw) == (p.color.length() - sw.length()) && sw.length() <= p.color.length() && (st & Target::color))
				|| (p.name.rfind(sw)==(p.name.length()-sw.length()) && sw.length()<=p.name.length() && (st & Target::name))
				|| (p.japanese.rfind(sw) == (p.japanese.length() - sw.length()) && sw.length() <= p.japanese.length() && (st & Target::japanese))
				|| (p.english.rfind(sw) == (p.english.length() - sw.length()) && sw.length() <= p.english.length() && (st & Target::english))
			)
				ret->push_back(p);
		}
		else {
			throw std::invalid_argument("invalid search mode");
		}
	}
}

void set_colorlist_table(lua_State* L, ColorList* val) {
	lua_newtable(L);
	for (int i = 0; i < val->size(); i++) {
		lua_pushinteger(L, i + 1);
		lua_newtable(L);

		{
			RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
			luaL_getmetatable(L, TEXTMODULE_RGB);
			lua_setmetatable(L, -2);
			getRGBhex(HexToDec(val->at(i).color), ret);
			lua_setfield(L, -2, "color");

			lua_pushwstring(L, val->at(i).name);
			lua_setfield(L, -2, "name");

			lua_pushwstring(L, val->at(i).japanese);
			lua_setfield(L, -2, "japanese");

			lua_pushwstring(L, val->at(i).english);
			lua_setfield(L, -2, "english");
		}

		lua_settable(L, -3);
	}

	luaL_getmetatable(L, TEXTMODULE_COLORLIST);
	lua_setmetatable(L, -2);
}

void get_colorlist_table(lua_State* L, int idx, ColorList* ret) {
	luaL_argcheck(L, lua_type(L, idx) == LUA_TTABLE && luaL_checkmetatable(L, idx, TEXTMODULE_COLORLIST), idx, get_colorlistmsg().c_str());

	lua_pushnil(L);
	while (lua_next(L, idx)) {
		lua_getfield(L, -1, "english");
		lua_getfield(L, -2, "japanese");
		lua_getfield(L, -3, "name");
		lua_getfield(L, -4, "color");

		ColorItem c;
		c.english = tm_towstring(L, -4);
		c.japanese = tm_towstring(L, -3);
		c.name = tm_towstring(L, -2);
		c.color = getRGBhex(rgb_check(L, -1));
		ret->push_back(c);

		lua_pop(L, 5);
	}
}


int color_getlist(lua_State* L) {
	try {
		ColorList list;
		getlist(tm_tostring(L, 1), &list);
		set_colorlist_table(L, &list);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_search(lua_State* L) {
	try {
		ColorList list;
		get_colorlist_table(L, 1, &list);

		ColorList ret;
		search(&list, tm_towstring(L, 2), tm_tointeger_s(L, 3, 0), &ret, tm_tointeger_s(L, 4, Target::color | Target::name | Target::japanese | Target::english));
		set_colorlist_table(L, &ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_makepalette(lua_State* L) {
	try {
		ColorList list;
		get_colorlist_table(L, 1, &list);

		std::wstring ret;
		std::wstring color;
		std::wstring name;
		int r = 0;

		for (int i = 0; i < 32; i++) {
			r++;
			if (i < list.size()) {
				color = upperString(list[i].color.substr(2));
				name = list[i].name;
			}
			else {
				color = L"FFFFFF";
				name = L"";
			}

			if (r == 4) {
				if (name == L"")
					ret += color + L"\n";
				else
					ret += color + L";" + name + L"\n";

				r = 0;
			}
			else {
				if (name == L"")
					ret += color + L",";
				else
					ret += color + L";" + name + L",";
			}
		}

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_loadpalette(lua_State* L) {
	try {
		std::wstring palette = lua_towstring(L, 1);
		std::vector<std::wstring> lines = split(palette, L'\n');
		ColorList ret;

		for (int i = 0; i < 8; i++) {
			std::vector<std::wstring> colors = split(lines.at(i), L',');
			for (int j = 0; j < 4; j++) {
				std::wstring n_color = colors.at(j);
				ColorItem p;

				if (n_color.find(L";") != std::string::npos) { //色名を記載している
					std::vector<std::wstring> n = split(n_color, L';');
					p.color = DecToHex(HexToDec(L"0x" + lowerString(n.at(0))));
					p.name = n.at(1);
				}
				else { //色名を記載していない
					p.color = DecToHex(HexToDec(L"0x" + lowerString(n_color)));
					p.name = L"";
				}
				ret.push_back(p);
			}
		}
		set_colorlist_table(L, &ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_color(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COLOR_REG);
		lua_setfield(L, -2, name);

		luaL_newmetatable(L, TEXTMODULE_COLORLIST); //add metatable
		luaL_register(L, NULL, TEXTMODULE_COLOR_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COLOR_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}