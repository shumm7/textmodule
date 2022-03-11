#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <random>

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


int cmath_uniform_distribution(lua_State* L) {
	double m = 0;
	double n = 0;
	if (lua_type(L, 1) == LUA_TNONE && lua_type(L, 2) == LUA_TNONE) {
		m = 0;
		n = 1;
	}
	else if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) == LUA_TNONE) {
		m = 1;
		n = lua_tonumber(L, 1);
	}
	else if (lua_type(L, 1) == LUA_TNUMBER && lua_type(L, 2) == LUA_TNUMBER) {
		m = lua_tonumber(L, 1);
		n = lua_tonumber(L, 2);
	}

	std::random_device seed_gen;
	std::default_random_engine engine(seed_gen());
	std::uniform_real_distribution<> dist(m, n);

	lua_pushnumber(L, dist(engine));
	return 1;
}

void luaReg_cmath(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);

		// rad_to_deg
		lua_pushnumber(L, 180.0 / std::numbers::pi);
		lua_setfield(L, -2, "rad_to_deg");

		//deg_to_rad
		lua_pushnumber(L, std::numbers::pi / 180.0);
		lua_setfield(L, -2, "deg_to_rad");

		//e
		lua_pushnumber(L, std::numbers::e);
		lua_setfield(L, -2, "e");

		//napier
		lua_pushnumber(L, std::numbers::e);
		lua_setfield(L, -2, "napier");

		//log2e
		lua_pushnumber(L, std::numbers::log2e);
		lua_setfield(L, -2, "log2e");

		//log10e
		lua_pushnumber(L, std::numbers::log10e);
		lua_setfield(L, -2, "log10e");

		//pi
		lua_pushnumber(L, std::numbers::pi);
		lua_setfield(L, -2, "pi");

		//inv_pi
		lua_pushnumber(L, std::numbers::inv_pi);
		lua_setfield(L, -2, "inv_pi");

		//inv_sqrtpi
		lua_pushnumber(L, std::numbers::inv_sqrtpi);
		lua_setfield(L, -2, "inv_sqrtpi");

		//ln2
		lua_pushnumber(L, std::numbers::ln2);
		lua_setfield(L, -2, "ln2");

		//ln10
		lua_pushnumber(L, std::numbers::ln10);
		lua_setfield(L, -2, "ln10");

		//sqrt2
		lua_pushnumber(L, std::numbers::sqrt2);
		lua_setfield(L, -2, "sqrt2");

		//sqrt3
		lua_pushnumber(L, std::numbers::sqrt3);
		lua_setfield(L, -2, "sqrt3");

		//inv_sqrt3
		lua_pushnumber(L, std::numbers::inv_sqrt3);
		lua_setfield(L, -2, "inv_sqrt3");

		//egamma
		lua_pushnumber(L, std::numbers::egamma);
		lua_setfield(L, -2, "egamma");

		//phi
		lua_pushnumber(L, std::numbers::phi);
		lua_setfield(L, -2, "phi");

		//huge
		lua_pushnumber(L, HUGE_VAL);
		lua_setfield(L, -2, "huge");

		//infinity
		lua_pushnumber(L, INFINITY);
		lua_setfield(L, -2, "infinity");

		//nan
		lua_pushnumber(L, NAN);
		lua_setfield(L, -2, "nan");

		luaL_register(L, NULL, TEXTMODULE_CMATH_REG);
		lua_setfield(L, -2, name);
	}
}