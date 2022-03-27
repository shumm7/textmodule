#pragma once
#include <lua.hpp>

int vector3_new(lua_State* L);
int vector3_identity(lua_State* L);
int vector3_back(lua_State* L);
int vector3_down(lua_State* L);
int vector3_forward(lua_State* L);
int vector3_left(lua_State* L);
int vector3_one(lua_State* L);
int vector3_right(lua_State* L);
int vector3_up(lua_State* L);
int vector3_zero(lua_State* L);

int vector3__x(lua_State* L);
int vector3__y(lua_State* L);
int vector3__z(lua_State* L);
int vector3____tostring(lua_State* L);
int vector3____gc(lua_State* L);
int vector3____add(lua_State* L);
int vector3____sub(lua_State* L);
int vector3____mul(lua_State* L);
int vector3____div(lua_State* L);
int vector3____unm(lua_State* L);
int vector3____lt(lua_State* L);
int vector3____le(lua_State* L);
int vector3____index(lua_State* L);
int vector3____newindex(lua_State* L);

int vector3__abs(lua_State* L);
int vector3__norm(lua_State* L);
int vector3__normalize(lua_State* L);
int vector3__dot(lua_State* L);
int vector3__cross(lua_State* L);
int vector3__scale(lua_State* L);
int vector3__distance(lua_State* L);
int vector3__conj(lua_State* L);
int vector3__table(lua_State* L);
int vector3__vector2(lua_State* L);

void luaReg_vector3(lua_State* L, const char* name, bool reg);
void luaGlobal_vector3(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_VECTOR3_REG[] = {
	{"new", vector3_new},
	{"identity", vector3_identity},
	{"back", vector3_back},
	{"down", vector3_down},
	{"forward", vector3_forward},
	{"left", vector3_left},
	{"one", vector3_one},
	{"right", vector3_right},
	{"up", vector3_up},
	{"zero", vector3_zero},

	{"x", vector3__x},
	{"y", vector3__y},
	{"z", vector3__z},

	{"abs", vector3__abs},
	{"norm", vector3__norm},
	{"normalize", vector3__normalize},
	{"dot", vector3__dot},
	{"cross", vector3__cross},
	{"scale", vector3__scale},
	{"distance", vector3__distance},
	{"conj", vector3__conj},
	{"table", vector3__table},
	{"vector2", vector3__vector2},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR3_META_REG[] = {
	{"x", vector3__x},
	{"y", vector3__y},
	{"z", vector3__z},

	{"__tostring", vector3____tostring},
	{"__add", vector3____add},
	{"__sub", vector3____sub},
	{"__mul", vector3____mul},
	{"__div", vector3____div},
	{"__unm", vector3____unm},
	{"__lt", vector3____lt},
	{"__le", vector3____le},
	//{"__index", vector3____index},
	{"__newindex", vector3____newindex},

	{"abs", vector3__abs},
	{"norm", vector3__norm},
	{"normalize", vector3__normalize},
	{"dot", vector3__dot},
	{"cross", vector3__cross},
	{"scale", vector3__scale},
	{"distance", vector3__distance},
	{"conj", vector3__conj},
	{"table", vector3__table},
	{"vector2", vector3__vector2},
	{nullptr, nullptr}
};