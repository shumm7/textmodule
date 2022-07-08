#include "exedit.hpp"

#include <iostream>
#include <aviutl.hpp>
#include <exedit.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_aviutl.hpp"

bool is093rc1 = false; 

void lua_pushexeditobject(lua_State* L, ExEdit::Object* object) {
	lua_newtable(L);

	lua_settablevalue(L, "layer", object->layer_disp + 1);
	lua_settablevalue(L, "name", std::string(object->dispname));
	lua_settablevalue(L, "frame", lua_Vector2(object->frame_begin + 1, object->frame_end + 1));

	lua_newtable(L);
	for (int i = 0; i < (object->track_n); i++)
		lua_settablevalue(L, i+1, lua_Vector2(object->track_value_left[i], object->track_value_right[i]));
	lua_setfield(L, -2, "track");

	lua_newtable(L);
	for (int i = 0; i < (object->track_n); i++)
		lua_settablevalue(L, i + 1, object->track_param[i]);
	lua_setfield(L, -2, "trackparam");

	lua_newtable(L);
	for (int i = 0; i < (object->check_n); i++)
		lua_settablevalue(L, i + 1, (bool)(object->check_value[i]));
	lua_setfield(L, -2, "check");
}


int exedit_currentscene(lua_State* L) {
	try {
		int id = *Get_SceneDisplaying(false);

		ExEdit::SceneSetting* ss = Get_SceneSetting(false);
		const char* name = ss[id].name;
		if (name == NULL) name = "";

		lua_pushnumber(L, id);
		lua_pushstring(L, name);
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int exedit_scene(lua_State* L) {
	try {
		int id = 0;
		if (lua_type(L, 1) == LUA_TNUMBER) {
			id = tm_tointeger(L, 1);
			if (id < 0 || id>49) return 0;
		}
		else if (lua_type(L, 1) == LUA_TNONE) {
			id = *Get_SceneDisplaying(false);
		}
		else {
			luaL_argerror(L, 1, "number/none expected");
		}

		ExEdit::SceneSetting* ss = Get_SceneSetting(false);

		const char* name = ss[id].name;
		if (name == NULL) name = "";

		lua_newtable(L);
		lua_settablevalue(L, "id", id);
		lua_settablevalue(L, "name", name);
		lua_settablevalue(L, "size", lua_Vector2(ss[id].width, ss[id].height));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int exedit_textbuffer(lua_State* L) {
	try {
		lua_pushwstring(L, std::wstring(Get_TextBuffer(false)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int exedit_object(lua_State* L) {
	try {
		ExEdit::Object** obj_table = Get_ObjectBuffer_Data(false);
		int* obj_index = Get_TraScript_ProcessingobjectIndex(false);
		ExEdit::Object* object = (*obj_table) + *obj_index;

		ExEdit::Filter** Filter = Get_LoadedFilterTable(false);
		for (int i = 0; i < object->countFilters(); i++) {
			int id = object->filter_param[i].id;
			std::cout << id << ": " << Filter[id]->name << std::endl;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

static luaL_Reg TEXTMODULE_EXEDIT_REG[] = {
	{"currentscene", exedit_currentscene},
	{"scene", exedit_scene},
	{"textbuffer", exedit_textbuffer},
	{"object", exedit_object},
	{ nullptr, nullptr }
};

void luaReg_exedit(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_EXEDIT_REG);

		lua_setfield(L, -2, name);
	}
}