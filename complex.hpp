#pragma once
#include <lua.hpp>

int complex_new(lua_State* L);
int complex_polar_new(lua_State* L);

int complex__real(lua_State* L);
int complex__imag(lua_State* L);

int complex____tostring(lua_State* L);
int complex____gc(lua_State* L);
int complex____add(lua_State* L);
int complex____sub(lua_State* L);
int complex____mul(lua_State* L);
int complex____div(lua_State* L);
int complex____unm(lua_State* L);
int complex____pow(lua_State* L);
int complex____lt(lua_State* L);
int complex____le(lua_State* L);
int complex____index(lua_State* L);
int complex____newindex(lua_State* L);
int complex____type(lua_State* L);
int complex____tonumber(lua_State* L);
int complex____call(lua_State* L);

int complex__abs(lua_State* L);
int complex__arg(lua_State* L);
int complex__norm(lua_State* L);
int complex__conj(lua_State* L);
int complex__proj(lua_State* L);
int complex__polar(lua_State* L);

int complex__cos(lua_State* L);
int complex__sin(lua_State* L);
int complex__tan(lua_State* L);
int complex__cosh(lua_State* L);
int complex__sinh(lua_State* L);
int complex__tanh(lua_State* L);
int complex__acos(lua_State* L);
int complex__asin(lua_State* L);
int complex__atan(lua_State* L);
int complex__acosh(lua_State* L);
int complex__asinh(lua_State* L);
int complex__atanh(lua_State* L);

int complex__exp(lua_State* L);
int complex__log(lua_State* L);
int complex__sqrt(lua_State* L);

int complex__table(lua_State* L);
int complex_vector2(lua_State* L);

void luaReg_complex(lua_State* L, const char* name, bool reg);
void luaGlobal_complex(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COMPLEX_REG[] = {
	{"new", complex_new},
	{"polar_new", complex_polar_new},
	{"pnew", complex_polar_new},

	{"real", complex__real},
	{"imag", complex__imag},
	{"r", complex__real},
	{"i", complex__imag},

	{"arg", complex__arg},
	{"proj", complex__proj},
	{"polar", complex__polar},

	{"table", complex__table},
	{"vector2", complex_vector2},

	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COMPLEX_META_REG[] = {
	{"real", complex__real},
	{"imag", complex__imag},
	{"r", complex__real},
	{"i", complex__imag},

	{"__tostring", complex____tostring},
	{"__add", complex____add},
	{"__sub", complex____sub},
	{"__mul", complex____mul},
	{"__div", complex____div},
	{"__pow", complex____pow},
	{"__unm", complex____unm},
	{"__lt", complex____lt},
	{"__le", complex____le},
	//{"__index", complex____index},
	{"__newindex", complex____newindex},
	{"__type", complex____type},
	{"__tonumber", complex____tonumber},
	{"__call", complex____call},

	{"__cos", complex__cos},
	{"__sin", complex__sin},
	{"__tan", complex__tan},
	{"__cosh", complex__cosh},
	{"__sinh", complex__sinh},
	{"__tanh", complex__tanh},
	{"__acos", complex__acos},
	{"__asin", complex__asin},
	{"__atan", complex__atan},
	{"__acosh", complex__acosh},
	{"__asinh", complex__asinh},
	{"__atanh", complex__atanh},
	{"__exp", complex__exp},
	{"__log", complex__log},
	{"__sqrt", complex__sqrt},
	{"__abs", complex__abs},
	{"__norm", complex__norm},
	{"__conj", complex__conj},

	{"abs", complex__abs},
	{"norm", complex__norm},
	{"conj", complex__conj},
	{"arg", complex__arg},
	{"proj", complex__proj},
	{"polar", complex__polar},

	{"table", complex__table},
	{"vector2", complex_vector2},
	{nullptr, nullptr}
};