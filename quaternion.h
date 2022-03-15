#pragma once
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <lua.hpp>

typedef Eigen::Quaternion<double> Quat;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Matrix3d Matrix3;
typedef Eigen::AngleAxisd AngleAxis;

#define TEXTMODULE_QUATERNION "Eigen::Quaternion<double>*"
#define quaternion_check(L, n) (reinterpret_cast<Quat*>(luaL_checkudata(L, n, TEXTMODULE_QUATERNION)))

int quaternion_new(lua_State* L);
int quaternion_euler_new(lua_State* L);
int quaternion_angleaxis(lua_State* L);
int quaternion_twovectors(lua_State* L);
int quaternion_identity(lua_State* L);

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

int quaternion__abs(lua_State* L);
int quaternion__norm(lua_State* L);
int quaternion__conj(lua_State* L);
int quaternion__euler(lua_State* L);
int quaternion__inverse(lua_State* L);
int quaternion__normalize(lua_State* L);
int quaternion__dot(lua_State* L);
int quaternion__table(lua_State* L);
int quaternion__cross(lua_State* L);

void luaReg_quaternion(lua_State* L, const char* name, bool reg);
void luaGlobal_quaternion(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_QUATERNION_REG[] = {
	{"new", quaternion_new},
	{"euler_new", quaternion_euler_new},
	{"enew", quaternion_euler_new},
	{"angleaxis", quaternion_angleaxis},
	{"twovectors", quaternion_twovectors},
	{"identity", quaternion_identity},

	{"w", quaternion__w},
	{"x", quaternion__x},
	{"y", quaternion__y},
	{"z", quaternion__z},

	{"abs", quaternion__abs},
	{"norm", quaternion__norm},
	{"conj", quaternion__conj},
	{"euler", quaternion__euler},
	{"inverse", quaternion__inverse},
	{"normalize", quaternion__normalize},
	{"dot", quaternion__dot},
	{"cross", quaternion__cross},
	{"table", quaternion__table},
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

	{"abs", quaternion__abs},
	{"norm", quaternion__norm},
	{"conj", quaternion__conj},
	{"euler", quaternion__euler},
	{"inverse", quaternion__inverse},
	{"normalize", quaternion__normalize},
	{"dot", quaternion__dot},
	{"cross", quaternion__cross},
	{"table", quaternion__table},
	{nullptr, nullptr}
};