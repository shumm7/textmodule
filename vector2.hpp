#pragma once
#include <lua.hpp>

int vector2_new(lua_State* L);
int vector2_identity(lua_State* L);
int vector2_down(lua_State* L);
int vector2_left(lua_State* L);
int vector2_one(lua_State* L);
int vector2_right(lua_State* L);
int vector2_up(lua_State* L);
int vector2_zero(lua_State* L);

int vector2__x(lua_State* L);
int vector2__y(lua_State* L);
int vector2____tostring(lua_State* L);
int vector2____gc(lua_State* L);
int vector2____add(lua_State* L);
int vector2____sub(lua_State* L);
int vector2____mul(lua_State* L);
int vector2____div(lua_State* L);
int vector2____unm(lua_State* L);
int vector2____lt(lua_State* L);
int vector2____le(lua_State* L);
int vector2____index(lua_State* L);
int vector2____newindex(lua_State* L);
int vector2____type(lua_State* L);
int vector2____call(lua_State* L);

int vector2__abs(lua_State* L);
int vector2__norm(lua_State* L);
int vector2__normalize(lua_State* L);
int vector2__dot(lua_State* L);
int vector2__scale(lua_State* L);
int vector2__distance(lua_State* L);
int vector2__conj(lua_State* L);
int vector2__table(lua_State* L);
int vector2__complex(lua_State* L);
int vector2__vector3(lua_State* L);
int vector2__vector4(lua_State* L);

void luaReg_vector2(lua_State* L, const char* name, bool reg);
void luaGlobal_vector2(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_VECTOR2_REG[] = {
	{"new", vector2_new},
	{"identity", vector2_identity},
	{"down", vector2_down},
	{"left", vector2_left},
	{"one", vector2_one},
	{"right", vector2_right},
	{"up", vector2_up},
	{"zero", vector2_zero},

	{"x", vector2__x},
	{"y", vector2__y},

	{"abs", vector2__abs},
	{"norm", vector2__norm},
	{"normalize", vector2__normalize},
	{"dot", vector2__dot},
	{"scale", vector2__scale},
	{"distance", vector2__distance},
	{"conj", vector2__conj},
	{"complex", vector2__complex},
	{"table", vector2__table},
	{"vector3", vector2__vector3},
	{"vector4", vector2__vector4},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR2_META_REG[] = {
	{"x", vector2__x},
	{"y", vector2__y},

	{"__tostring", vector2____tostring},
	{"__add", vector2____add},
	{"__sub", vector2____sub},
	{"__mul", vector2____mul},
	{"__div", vector2____div},
	{"__unm", vector2____unm},
	{"__lt", vector2____lt},
	{"__le", vector2____le},
	//{"__index", vector2____index},
	{"__newindex", vector2____newindex},
	{"__type", vector2____type},
	{"__call", vector2____call},

	{"abs", vector2__abs},
	{"norm", vector2__norm},
	{"normalize", vector2__normalize},
	{"dot", vector2__dot},
	{"scale", vector2__scale},
	{"distance", vector2__distance},
	{"conj", vector2__conj},
	{"complex", vector2__complex},
	{"table", vector2__table},
	{"vector3", vector2__vector3},
	{"vector4", vector2__vector4},
	{nullptr, nullptr}
};