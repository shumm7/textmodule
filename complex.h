#pragma once
#include <lua.hpp>
#define TEXTMODULE_COMPLEX "std::complex<double>*"
#define complex_check(L, n) (reinterpret_cast<std::complex<double>*>(luaL_checkudata(L, n, TEXTMODULE_COMPLEX)))

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
int complex__log10(lua_State* L);
int complex__sqrt(lua_State* L);

int complex__table(lua_State* L);

void luaReg_complex(lua_State* L, const char* name, bool reg);
void luaGlobal_complex(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_COMPLEX_REG[] = {
	{"new", complex_new},
	{"polar_new", complex_polar_new},
	{"pnew", complex_polar_new},

	{"real", complex__real},
	{"imag", complex__imag},

	{"abs", complex__abs},
	{"arg", complex__arg},
	{"norm", complex__norm},
	{"conj", complex__conj},
	{"proj", complex__proj},
	{"polar", complex__polar},

	{"cos", complex__cos},
	{"sin", complex__sin},
	{"tan", complex__tan},
	{"cosh", complex__cosh},
	{"sinh", complex__sinh},
	{"tanh", complex__tanh},
	{"acos", complex__acos},
	{"asin", complex__asin},
	{"atan", complex__atan},
	{"acosh", complex__acosh},
	{"asinh", complex__asinh},
	{"atanh", complex__atanh},

	{"exp", complex__exp},
	{"log", complex__log},
	{"log10", complex__log10},
	{"pow", complex____pow},
	{"sqrt", complex__sqrt},

	{"table", complex__table},

	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COMPLEX_META_REG[] = {
	{"real", complex__real},
	{"imag", complex__imag},

	{"__tostring", complex____tostring},
	{"__add", complex____add},
	{"__sub", complex____sub},
	{"__mul", complex____mul},
	{"__div", complex____div},
	{"__pow", complex____pow},
	{"__unm", complex____unm},
	{"__lt", complex____lt},
	{"__le", complex____le},

	{"abs", complex__abs},
	{"arg", complex__arg},
	{"norm", complex__norm},
	{"conj", complex__conj},
	{"proj", complex__proj},
	{"polar", complex__polar},

	{"cos", complex__cos},
	{"sin", complex__sin},
	{"tan", complex__tan},
	{"cosh", complex__cosh},
	{"sinh", complex__sinh},
	{"tanh", complex__tanh},
	{"acos", complex__acos},
	{"asin", complex__asin},
	{"atan", complex__atan},
	{"acosh", complex__acosh},
	{"asinh", complex__asinh},
	{"atanh", complex__atanh},

	{"exp", complex__exp},
	{"log", complex__log},
	{"log10", complex__log10},
	{"pow", complex____pow},
	{"sqrt", complex__sqrt},

	{"table", complex__table},
	{nullptr, nullptr}
};