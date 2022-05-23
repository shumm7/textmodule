#pragma once
#include <lua.hpp>

int fs_current(lua_State* L);

int fs_absolute(lua_State* L);
int fs_relative(lua_State* L);
int fs_proximate(lua_State* L);
int fs_canonical(lua_State* L);
int fs_weakly_canonical(lua_State* L);

int fs_create(lua_State* L);
int fs_create_all(lua_State* L);

int fs_exists(lua_State* L);

int fs_remove(lua_State* L);
int fs_remove_all(lua_State* L);

int fs_copy(lua_State* L);
int fs_copy_file(lua_State* L);
int fs_rename(lua_State* L);

int fs_type(lua_State* L);
int fs_size(lua_State* L);
int fs_space(lua_State* L);

int fs_read(lua_State* L);
int fs_write(lua_State* L);
int fs_append(lua_State* L);

void luaReg_filesystem(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_FILESYSTEM_REG[] = {
	{"current", fs_current},
	{"absolute", fs_absolute},
	{"relative", fs_relative},
	{"proximate", fs_proximate},
	{"canonical", fs_canonical},
	{"weakly_canonical", fs_weakly_canonical},
	{"create", fs_create},
	{"create_all", fs_create_all},
	{"exists", fs_exists},
	{"remove", fs_remove},
	{"remove_all", fs_remove_all},
	{"copy", fs_copy},
	{"copy_file", fs_copy_file},
	{"rename", fs_rename},
	{"type", fs_type},
	{"size", fs_size},
	{"space", fs_space},
	{"read", fs_read},
	{"write", fs_write},
	{"append", fs_append},
	{ nullptr, nullptr }
};