#pragma once
#include <lua.hpp>

int quaternion_new(lua_State* L);
int quaternion_euler_new(lua_State* L);
int quaternion_angleaxis(lua_State* L);
int quaternion_twovectors(lua_State* L);
int quaternion_lookrot(lua_State* L);
int quaternion_identity(lua_State* L);
int quaternion_zero(lua_State* L);

int quaternion__w(lua_State* L);
int quaternion__x(lua_State* L);
int quaternion__y(lua_State* L);
int quaternion__z(lua_State* L);

int quaternion____tostring(lua_State* L);
int quaternion____gc(lua_State* L);
int quaternion____add(lua_State* L);
int quaternion____sub(lua_State* L);
int quaternion____mul(lua_State* L);
int quaternion____div(lua_State* L);
int quaternion____unm(lua_State* L);
int quaternion____lt(lua_State* L);
int quaternion____le(lua_State* L);
int quaternion____index(lua_State* L);
int quaternion____newindex(lua_State* L);
int quaternion____type(lua_State* L);
int quaternion____tonumber(lua_State* L);
int quaternion____call(lua_State* L);

int quaternion__abs(lua_State* L);
int quaternion__norm(lua_State* L);
int quaternion__conj(lua_State* L);
int quaternion__euler(lua_State* L);
int quaternion__inverse(lua_State* L);
int quaternion__normalize(lua_State* L);
int quaternion__dot(lua_State* L);
int quaternion__table(lua_State* L);
int quaternion__cross(lua_State* L);
int quaternion__slerp(lua_State* L);
int quaternion__vector4(lua_State* L);

void luaReg_quaternion(lua_State* L, const char* name, bool reg);
void luaGlobal_quaternion(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_QUATERNION_REG[] = {
	{"new", quaternion_new},
	{"euler_new", quaternion_euler_new},
	{"enew", quaternion_euler_new},
	{"angleaxis", quaternion_angleaxis},
	{"twovectors", quaternion_twovectors},
	{"lookrot", quaternion_lookrot},
	{"identity", quaternion_identity},
	{"zero", quaternion_zero},

	{"w", quaternion__w},
	{"x", quaternion__x},
	{"y", quaternion__y},
	{"z", quaternion__z},

	{"euler", quaternion__euler},
	{"inverse", quaternion__inverse},
	{"table", quaternion__table},
	{"vector4", quaternion__vector4},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_QUATERNION_META_REG[] = {
	{"w", quaternion__w},
	{"x", quaternion__x},
	{"y", quaternion__y},
	{"z", quaternion__z},

	{"__tostring", quaternion____tostring},
	{"__add", quaternion____add},
	{"__sub", quaternion____sub},
	{"__mul", quaternion____mul},
	{"__div", quaternion____div},
	{"__unm", quaternion____unm},
	{"__lt", quaternion____lt},
	{"__le", quaternion____le},
	//{"__index", quaternion____index},
	{"__newindex", quaternion____newindex},
	{"__type", quaternion____type},
	{"__tonumber", quaternion____tonumber},
	{"__call", quaternion____call},

	{"__abs", quaternion__abs},
	{"__norm", quaternion__norm},
	{"__conj", quaternion__conj},
	{"__dot", quaternion__dot},
	{"__cross", quaternion__cross},
	{"__lerp", quaternion__slerp},
	{"__normalize", quaternion__normalize},

	{"table", quaternion__table},
	{"vector4", quaternion__vector4},
	{nullptr, nullptr}
};