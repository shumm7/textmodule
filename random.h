#pragma once
#include <lua.hpp>

int random_uniform(lua_State* L);
int random_bernoulli(lua_State* L);
int random_binomial(lua_State* L);
int random_geometric(lua_State* L);
int random_negative_binomial(lua_State* L);
int random_poisson(lua_State* L);
int random_exponential(lua_State* L);
int random_gamma(lua_State* L);
int random_weibull(lua_State* L);
int random_extreme_value(lua_State* L);
int random_normal(lua_State* L);
int random_lognormal(lua_State* L);
int random_chi_squared(lua_State* L);
int random_cauchy(lua_State* L);
int random_fisher_f(lua_State* L);
int random_student_t(lua_State* L);

void luaReg_random(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_RANDOM_REG[] = {
	{"uniform", random_uniform},
	{"bernoulli", random_bernoulli},
	{"binomial", random_binomial},
	{"geometric", random_geometric},
	{"negative_binomial", random_negative_binomial},
	{"poisson", random_poisson},
	{"exponential", random_exponential},
	{"gamma", random_gamma},
	{"weibull", random_weibull},
	{"extreme_value", random_extreme_value},
	{"normal", random_normal},
	{"lognormal", random_lognormal},
	{"chi_squared", random_chi_squared},
	{"cauchy", random_cauchy},
	{"fisher_f", random_fisher_f},
	{"student_t", random_student_t},
	{ nullptr, nullptr }
};
