#include <lua.hpp>

int cmath_cbrt(lua_State* L);
int cmath_trunc(lua_State* L);
int cmath_lerp(lua_State* L);
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

void luaReg_cmath(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_CMATH_REG[] = {
	{"cbrt", cmath_cbrt},
	{"trunc", cmath_trunc},
	{"lerp", cmath_lerp},
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
	{ nullptr, nullptr }
};