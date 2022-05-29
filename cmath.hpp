#pragma once
#include <lua.hpp>

int cmath_sin(lua_State* L);
int cmath_sinh(lua_State* L);
int cmath_cos(lua_State* L);
int cmath_cosh(lua_State* L);
int cmath_tan(lua_State* L);
int cmath_tanh(lua_State* L);
int cmath_asin(lua_State* L);
int cmath_asinh(lua_State* L);
int cmath_acos(lua_State* L);
int cmath_acosh(lua_State* L);
int cmath_atan(lua_State* L);
int cmath_atan2(lua_State* L);
int cmath_atanh(lua_State* L);

int cmath_abs(lua_State* L);
int cmath_ceil(lua_State* L);
int cmath_deg(lua_State* L);
int cmath_exp(lua_State* L);
int cmath_floor(lua_State* L);
int cmath_fmod(lua_State* L);
int cmath_frexp(lua_State* L);
int cmath_ldexp(lua_State* L);
int cmath_log(lua_State* L);
int cmath_max(lua_State* L);
int cmath_min(lua_State* L);
int cmath_modf(lua_State* L);
int cmath_pow(lua_State* L);
int cmath_rad(lua_State* L);
int cmath_sqrt(lua_State* L);
int cmath_trunc(lua_State* L);
int cmath_round(lua_State* L);
int cmath_norm(lua_State* L);
int cmath_conj(lua_State* L);
int cmath_lerp(lua_State* L);
int cmath_dot(lua_State* L);
int cmath_cross(lua_State* L);
int cmath_scale(lua_State* L);
int cmath_distance(lua_State* L);
int cmath_normalize(lua_State* L);

int cmath_cbrt(lua_State* L);
int cmath_rep(lua_State* L);
int cmath_clamp(lua_State* L);
int cmath_tgamma(lua_State* L);
int cmath_lgamma(lua_State* L);
int cmath_erf(lua_State* L);
int cmath_erfc(lua_State* L);
int cmath_hypot(lua_State* L);
int cmath_copysign(lua_State* L);
int cmath_gcd(lua_State*);
int cmath_lcm(lua_State*);
int cmath_fact(lua_State* L);
int cmath_comb(lua_State* L);
int cmath_perm(lua_State* L);
int cmath_rep_comb(lua_State* L);
int cmath_rep_perm(lua_State* L);
int cmath_circle_perm(lua_State* L);

int cmath_sign(lua_State* L);
int cmath_isprime(lua_State* L);
int cmath_isinteger(lua_State* L);
int cmath_iseven(lua_State* L);
int cmath_isodd(lua_State* L);
int cmath_classify(lua_State* L);

int cmath_assoc_laguerre(lua_State* L);
int cmath_assoc_legendre(lua_State* L);
int cmath_beta(lua_State* L);
int cmath_comp_ellint_1(lua_State* L);
int cmath_comp_ellint_2(lua_State* L);
int cmath_comp_ellint_3(lua_State* L);
int cmath_cyl_bessel_i(lua_State* L);
int cmath_cyl_bessel_j(lua_State* L);
int cmath_cyl_bessel_k(lua_State* L);
int cmath_cyl_neumann(lua_State* L);
int cmath_ellint_1(lua_State* L);
int cmath_ellint_2(lua_State* L);
int cmath_ellint_3(lua_State* L);
int cmath_expint(lua_State* L);
int cmath_hermite(lua_State* L);
int cmath_laguerre(lua_State* L);
int cmath_legendre(lua_State* L);
int cmath_riemann_zeta(lua_State* L);
int cmath_sph_bessel(lua_State* L);
int cmath_sph_legendre(lua_State* L);
int cmath_sph_neumann(lua_State* L);
int cmath_zeta(lua_State* L);
int cmath_bezier(lua_State* L);
int cmath_equation(lua_State* L);
int cmath_fibonacci(lua_State* L);
int cmath_prime(lua_State* L);

void luaReg_cmath(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_CMATH_REG[] = {
	{"abs", cmath_abs},
	{"acos",cmath_acos},
	{"asin",cmath_asin},
	{"atan",cmath_atan},
	{"atan2",cmath_atan2},
	{"atanh", cmath_atanh},
	{"ceil",cmath_ceil},
	{"cosh", cmath_cosh},
	{"cos", cmath_cos},
	{"deg", cmath_deg},
	{"exp", cmath_exp},
	{"floor", cmath_floor},
	{"fmod", cmath_fmod},
	{"frexp", cmath_frexp},
	{"ldexp", cmath_ldexp},
	{"log", cmath_log},
	{"max", cmath_max},
	{"min", cmath_min},
	{"modf", cmath_modf},
	{"pow", cmath_pow},
	{"rad", cmath_rad},
	{"sinh", cmath_sinh},
	{"sin", cmath_sin},
	{"sqrt",cmath_sqrt},
	{"tanh", cmath_tanh},
	{"tan", cmath_tan},
	{"trunc", cmath_trunc},
	{"round", cmath_round},
	{"norm", cmath_norm},
	{"conj", cmath_conj},
	{"lerp", cmath_lerp},
	{"dot", cmath_dot},
	{"cross", cmath_cross},
	{"scale", cmath_scale},
	{"distance", cmath_distance},
	{"normalize", cmath_normalize},

	{"cbrt", cmath_cbrt},
	{"clamp", cmath_clamp},
	{"rep", cmath_rep},
	{"tgamma", cmath_tgamma},
	{"lgamma", cmath_lgamma},
	{"erf", cmath_erf},
	{"erfc", cmath_erfc},
	{"hypot", cmath_hypot},
	{"copysign", cmath_copysign},
	{"gcd", cmath_gcd},
	{"lcm", cmath_lcm},
	{"fact", cmath_fact},
	{"comb", cmath_comb},
	{"perm", cmath_perm},
	{"rep_comb", cmath_rep_comb},
	{"rep_perm", cmath_rep_perm},
	{"circle_perm", cmath_circle_perm},

	{"sign", cmath_sign},
	{"isprime", cmath_isprime},
	{"isinteger", cmath_isinteger},
	{"iseven", cmath_iseven},
	{"isodd", cmath_isodd},
	{"classify", cmath_classify},
	
	{"assoc_laguerre", cmath_assoc_laguerre},
	{"assoc_legendre", cmath_assoc_legendre},
	{"beta", cmath_beta},
	{"comp_ellint_1", cmath_comp_ellint_1},
	{"comp_ellint_2", cmath_comp_ellint_2},
	{"comp_ellint_3", cmath_comp_ellint_3},
	{"cyl_bessel_i",  cmath_cyl_bessel_i},
	{"cyl_bessel_j",  cmath_cyl_bessel_j},
	{"cyl_bessel_k",  cmath_cyl_bessel_k},
	{"cyl_neumann",  cmath_cyl_neumann},
	{"ellint_1",  cmath_ellint_1},
	{"ellint_2",  cmath_ellint_2},
	{"ellint_3",  cmath_ellint_3},
	{"expint",  cmath_expint},
	{"hermite", cmath_hermite},
	{"laguerre", cmath_laguerre},
	{"legendre", cmath_legendre},
	{"riemann_zeta", cmath_riemann_zeta},
	{"sph_bessel", cmath_sph_bessel},
	{"sph_legendre", cmath_sph_legendre},
	{"sph_neumann", cmath_sph_neumann},

	{"bezier", cmath_bezier},
	{"equation", cmath_equation},
	{"fibonacci", cmath_fibonacci},
	{"prime", cmath_prime},
	{ nullptr, nullptr }
};