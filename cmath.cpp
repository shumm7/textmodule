#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>

#include "cmath.h"
#include "textmodule_lua.h"

int cmath_cbrt(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::cbrt(x));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_trunc(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);

		lua_pushnumber(L, std::trunc(n));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lerp(lua_State* L) {
	try {
		double a = tm_tonumber(L, 1);
		double b = tm_tonumber(L, 2);
		double t = tm_tonumber(L, 3);

		lua_pushnumber(L, std::lerp(a, b, t));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_clamp(lua_State* L) {
	try {
		double value = tm_tonumber(L, 1);
		double min = tm_tonumber_s(L, 2, 0);
		double max = tm_tonumber_s(L, 3, 1);

		if (min > max) {
			throw std::invalid_argument("invalid argument");
		}

		if (value < min) {
			lua_pushnumber(L, min);
		}
		else if (value > max) {
			lua_pushnumber(L, max);
		}
		else {
			lua_pushnumber(L, value);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_rep(lua_State* L) {
	try {
		double value = tm_tonumber(L, 1);
		double min = tm_tonumber_s(L, 2, 0);
		double max = tm_tonumber_s(L, 3, 1);

		if (min > max) {
			throw std::invalid_argument("invalid argument");
		}

		while (min > value || value >= max) {
			if (value < min) {
				value += (max - min);
			}
			else if (value >= max) {
				value -= (max -min);
			}
		}

		lua_pushnumber(L, value);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_tgamma(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::tgamma(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lgamma(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::lgamma(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_erf(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);
		
		lua_pushnumber(L, std::erf(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_erfc(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::erfc(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_hypot(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);
		double y = tm_tonumber(L, 2);

		int tp = lua_type(L, 3);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 3, "number/none expected");
		if (tp == LUA_TNONE) {
			lua_pushnumber(L, std::hypot(x, y));
		}
		else {
			double z = tm_tonumber(L, 3);
			lua_pushnumber(L, std::hypot(x, y, z));
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_copysign(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);
		double y = tm_tonumber(L, 2);

		lua_pushnumber(L, std::copysign(x, y));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_gcd(lua_State* L) {
	try {
		int x = tm_tointeger(L, 1);
		int y = tm_tointeger(L, 2);

		lua_pushnumber(L, std::gcd(x, y));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lcm(lua_State* L) {
	try {
		int x = tm_tointeger(L, 1);
		int y = tm_tointeger(L, 2);

		lua_pushnumber(L, std::lcm(x, y));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_assoc_laguerre(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double m = tm_tonumber(L, 2);
		double x = tm_tonumber(L, 3);

		lua_pushnumber(L, std::assoc_laguerre(n, m, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_assoc_legendre(lua_State* L) {
	try {
		double l = tm_tonumber(L, 1);
		double m = tm_tonumber(L, 2);
		double x = tm_tonumber(L, 3);

		lua_pushnumber(L, std::assoc_legendre(l, m, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_beta(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);
		double y = tm_tonumber(L, 2);

		lua_pushnumber(L, std::beta(x, y));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_1(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);

		lua_pushnumber(L, std::comp_ellint_1(k));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_2(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);

		lua_pushnumber(L, std::comp_ellint_2(k));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_3(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);
		double nu = tm_tonumber(L, 2);

		lua_pushnumber(L, std::comp_ellint_3(k, nu));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_i(lua_State* L) {
	try {
		double nu = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::cyl_bessel_i(nu, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_j(lua_State* L) {
	try {
		double nu = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::cyl_bessel_j(nu, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_k(lua_State* L) {
	try {
		double nu = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::cyl_bessel_k(nu, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_neumann(lua_State* L) {
	try {
		double nu = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::cyl_neumann(nu, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_1(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);
		double phi = tm_tonumber(L, 2);

		lua_pushnumber(L, std::ellint_1(k, phi));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_2(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);
		double phi = tm_tonumber(L, 2);

		lua_pushnumber(L, std::ellint_2(k, phi));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_3(lua_State* L) {
	try {
		double k = tm_tonumber(L, 1);
		double nu = tm_tonumber(L, 2);
		double phi = tm_tonumber(L, 3);

		lua_pushnumber(L, std::ellint_3(k, nu, phi));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_expint(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::expint(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_hermite(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::hermite(n, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_laguerre(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::laguerre(n, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_legendre(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);
		lua_pushnumber(L, std::legendre(n, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_riemann_zeta(lua_State* L) {
	try {
		double x = tm_tonumber(L, 1);

		lua_pushnumber(L, std::riemann_zeta(x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sph_bessel(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::sph_bessel(n, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sph_legendre(lua_State* L) {
	try {
		double l = tm_tonumber(L, 1);
		double m = tm_tonumber(L, 2);
		double theta = tm_tonumber(L, 3);

		lua_pushnumber(L, std::sph_legendre(l, m, theta));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sph_neumann(lua_State* L) {
	try {
		double n = tm_tonumber(L, 1);
		double x = tm_tonumber(L, 2);

		lua_pushnumber(L, std::sph_neumann(n, x));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_cmath(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_CMATH_REG);

		lua_settablevalue(L, "rad_to_deg", 180.0 / std::numbers::pi);
		lua_settablevalue(L, "deg_to_rad", std::numbers::pi / 180.0);
		lua_settablevalue(L, "e", std::numbers::e);
		lua_settablevalue(L, "napier", std::numbers::e);
		lua_settablevalue(L, "log2e", std::numbers::log2e);
		lua_settablevalue(L, "log10e", std::numbers::log10e);
		lua_settablevalue(L, "pi", std::numbers::pi);
		lua_settablevalue(L, "inv_pi", std::numbers::inv_pi);
		lua_settablevalue(L, "inv_sqrtpi", std::numbers::inv_sqrtpi);
		lua_settablevalue(L, "ln2", std::numbers::ln2);
		lua_settablevalue(L, "ln10", std::numbers::ln10);
		lua_settablevalue(L, "sqrt2", std::numbers::sqrt2);
		lua_settablevalue(L, "sqrt3", std::numbers::sqrt3);
		lua_settablevalue(L, "inv_sqrt3", std::numbers::inv_sqrt3);
		lua_settablevalue(L, "egamma", std::numbers::egamma);
		lua_settablevalue(L, "phi", std::numbers::phi);
		lua_settablevalue(L, "huge", HUGE_VAL);
		lua_settablevalue(L, "infinity", std::numeric_limits<double>::infinity());
		lua_settablevalue(L, "negative_infinity", -std::numeric_limits<double>::infinity());
		lua_settablevalue(L, "nan", NAN);
		lua_settablevalue(L, "quiet_nan", std::numeric_limits<double>::quiet_NaN());
		lua_settablevalue(L, "signaling_nan", std::numeric_limits<double>::signaling_NaN());
		lua_settablevalue(L, "min_exponent", std::numeric_limits<double>::min_exponent10);
		lua_settablevalue(L, "max_exponent", std::numeric_limits<double>::max_exponent10);
		lua_settablevalue(L, "digits", std::numeric_limits<double>::digits10);

		lua_setfield(L, -2, name);
	}
}