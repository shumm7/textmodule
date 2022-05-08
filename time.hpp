#pragma once
#include <lua.hpp>

#include <unicode/datefmt.h>
#include <unicode/dtfmtsym.h>
#include <unicode/gregocal.h>
#include <unicode/timezone.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>
#include <unicode/dtptngen.h>
#include <unicode/dtitvfmt.h>

using namespace icu;

int time_now(lua_State* L);
int time_fromtime(lua_State* L);
int time_totime(lua_State* L);
int time_totable(lua_State* L);
int time_fromtable(lua_State* L);

int time___tostring(lua_State* L);
int time___add(lua_State* L);
int time___sub(lua_State* L);

int time_duration(lua_State* L);
int time_epoch(lua_State* L);
int time_localize(lua_State* L);
int time_locale_pattern(lua_State* L);

void luaReg_time(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_TIME_REG[] = {
	{"now", time_now},
	{"totime", time_totime},
	{"fromtime", time_fromtime},
	{"totable", time_totable},
	{"fromtable", time_fromtable},
	{"duration", time_duration},
	{"epoch", time_epoch},
	{"localize", time_localize},
	{"locale_pattern", time_locale_pattern},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_TIME_META_REG[] = {
	{"totime", time_totime},
	{"totable", time_totable},
	{ "__tostring", time___tostring },
	{ "__add", time___add },
	{ "__sub", time___sub },
	{"duration", time_duration},
	{"epoch", time_epoch},
	{"localize", time_localize},
	{nullptr, nullptr}
};