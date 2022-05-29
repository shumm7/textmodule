#pragma once
#include <lua.hpp>

int vector4_new(lua_State* L);
int vector4_identity(lua_State* L);
int vector4_one(lua_State* L);
int vector4_zero(lua_State* L);

int vector4__x(lua_State* L);
int vector4__y(lua_State* L);
int vector4__z(lua_State* L);
int vector4__w(lua_State* L);
int vector4____tostring(lua_State* L);
int vector4____gc(lua_State* L);
int vector4____add(lua_State* L);
int vector4____sub(lua_State* L);
int vector4____mul(lua_State* L);
int vector4____div(lua_State* L);
int vector4____unm(lua_State* L);
int vector4____lt(lua_State* L);
int vector4____le(lua_State* L);
int vector4____index(lua_State* L);
int vector4____newindex(lua_State* L);
int vector4____type(lua_State* L);
int vector4____call(lua_State* L);

int vector4__abs(lua_State* L);
int vector4__norm(lua_State* L);
int vector4__normalize(lua_State* L);
int vector4__dot(lua_State* L);
int vector4__scale(lua_State* L);
int vector4__distance(lua_State* L);
int vector4__conj(lua_State* L);
int vector4__table(lua_State* L);
int vector4__quaternion(lua_State* L);
int vector4__vector2(lua_State* L);
int vector4__vector3(lua_State* L);

void luaReg_vector4(lua_State* L, const char* name, bool reg);
void luaGlobal_vector4(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_VECTOR4_REG[] = {
	{"new", vector4_new},
	{"identity", vector4_identity},
	{"one", vector4_one},
	{"zero", vector4_zero},

	{"x", vector4__x},
	{"y", vector4__y},
	{"z", vector4__z},
	{"w", vector4__w},

	{"table", vector4__table},
	{"quaternion", vector4__quaternion},
	{"vector2", vector4__vector2},
	{"vector3", vector4__vector3},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR4_META_REG[] = {
	{"x", vector4__x},
	{"y", vector4__y},
	{"z", vector4__z},
	{"w", vector4__w},

	{"__tostring", vector4____tostring},
	{"__add", vector4____add},
	{"__sub", vector4____sub},
	{"__mul", vector4____mul},
	{"__div", vector4____div},
	{"__unm", vector4____unm},
	{"__lt", vector4____lt},
	{"__le", vector4____le},
	//{"__index", vector4____index},
	{"__newindex", vector4____newindex},
	{"__type", vector4____type},
	{"__call", vector4____call},

	{"__abs", vector4__abs},
	{"__norm", vector4__norm},
	{"__normalize", vector4__normalize},
	{"__dot", vector4__dot},
	{"__conj", vector4__conj},
	{"__scale", vector4__scale},
	{"__distance", vector4__distance},

	{"table", vector4__table},
	{"quaternion", vector4__quaternion},
	{"vector2", vector4__vector2},
	{"vector3", vector4__vector3},
	{nullptr, nullptr}
};