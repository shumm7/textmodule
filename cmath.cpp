#include "cmath.hpp"

#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>
#include <Eigen/Dense>

#include <boost/math/special_functions/fibonacci.hpp>
#include <boost/math/special_functions/prime.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_math.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_exception.hpp"
#include "bignumber.hpp"

int cmath_sin(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__sin"))
			return 1;

		lua_pushnumber(L, std::sin(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sinh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__sinh"))
			return 1;

		lua_pushnumber(L, std::sinh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cos(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__cos"))
			return 1;

		lua_pushnumber(L, std::cos(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cosh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__cosh"))
			return 1;

		lua_pushnumber(L, std::cosh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_tan(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__tan"))
			return 1;

		lua_pushnumber(L, std::tan(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_tanh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__tanh"))
			return 1;

		lua_pushnumber(L, std::tanh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_asin(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__asin"))
			return 1;

		lua_pushnumber(L, std::asin(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_asinh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__asinh"))
			return 1;

		lua_pushnumber(L, std::asinh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_acos(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__acos"))
			return 1;

		lua_pushnumber(L, std::acos(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_acosh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__acosh"))
			return 1;

		lua_pushnumber(L, std::acosh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_atan(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__atan"))
			return 1;

		lua_pushnumber(L, std::atan(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_atan2(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__atan2"))
			return 1;

		lua_pushnumber(L, std::atan2(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_atanh(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__atanh"))
			return 1;

		lua_pushnumber(L, std::atanh(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_abs(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__abs"))
			return 1;

		lua_pushnumber(L, std::fabs(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ceil(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__ceil"))
			return 1;

		lua_pushnumber(L, std::ceil(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_deg(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__deg"))
			return 1;

		lua_pushnumber(L, tm_tonumber(L, 1) * boost::math::constants::radian<lua_Number>());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_exp(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__exp"))
			return 1;

		lua_pushnumber(L, std::exp(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_floor(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__floor"))
			return 1;

		lua_pushnumber(L, std::floor(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_fmod(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__fmod"))
			return 1;

		lua_pushnumber(L, std::fmod(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_frexp(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__frexp"))
			return 2;

		int e = 0;
		lua_pushnumber(L, std::frexp(tm_tonumber(L, 1), &e));
		lua_pushinteger(L, e);
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ldexp(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__ldexp"))
			return 1;

		lua_pushnumber(L, std::ldexp(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_log(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__log"))
			return 1;

		lua_pushnumber(L, std::log(tm_tonumber(L, 1)) / std::log(tm_tonumber_s(L, 2, boost::math::constants::e<lua_Number>())));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_max(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__max"))
			return 1;

		int n = lua_gettop(L);
		lua_Number dmax = tm_tonumber(L, 1);
		int i;
		for (i = 2; i <= n; i++) {
			lua_Number d =tm_tonumber(L, i);
			if (d > dmax)
				dmax = d;
		}
		lua_pushnumber(L, dmax);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_min(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__min"))
			return 1;

		int n = lua_gettop(L);
		lua_Number dmin = tm_tonumber(L, 1);
		int i;
		for (i = 2; i <= n; i++) {
			lua_Number d = tm_tonumber(L, i);
			if (d < dmin)
				dmin = d;
		}
		lua_pushnumber(L, dmin);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_modf(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__min"))
			return 2;

		lua_Number i = 0;
		lua_Number f = std::modf(tm_tonumber(L, 1), &i);

		lua_pushnumber(L, i);
		lua_pushnumber(L, f);
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_pow(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__pow"))
			return 1;

		lua_pushnumber(L, std::pow(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_rad(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__rad"))
			return 1;

		lua_pushnumber(L, tm_tonumber(L, 1) * boost::math::constants::degree<lua_Number>());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sqrt(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__sqrt"))
			return 1;

		lua_pushnumber(L, std::sqrt(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_trunc(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__trunc"))
			return 1;

		lua_pushnumber(L, std::trunc(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_round(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__round"))
			return 1;

		lua_pushnumber(L, std::round(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_norm(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__norm"))
			return 1;

		lua_pushnumber(L, std::norm(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_conj(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__conj"))
			return 1;

		lua_pushnumber(L, tm_tonumber(L, 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lerp(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__lerp"))
			return 1;

		lua_pushnumber(L, std::lerp(tm_tonumber(L, 1), tm_tonumber(L, 2), tm_tonumber(L, 3)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_dot(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__dot"))
			return 1;

		lua_pushnumber(L, tm_tonumber(L, 1) * tm_tonumber(L, 2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cross(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__cross"))
			return 1;

		tm_tonumber(L, 1);
		tm_tonumber(L, 2);

		lua_pushnumber(L, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_scale(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__scale"))
			return 1;

		lua_pushnumber(L, tm_tonumber(L, 1) * tm_tonumber(L, 2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_distance(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__distance"))
			return 1;

		lua_pushnumber(L, std::fabs(tm_tonumber(L, 1) - tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_normalize(lua_State* L) {
	try {
		if (luaL_callmeta(L, 1, "__normalize"))
			return 1;

		lua_Number d = tm_tonumber(L, 1);
		lua_pushnumber(L, d / std::fabs(d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_cbrt(lua_State* L) {
	try {
		lua_pushnumber(L, std::cbrt(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_clamp(lua_State* L) {
	try {
		lua_Number value = tm_tonumber(L, 1);
		lua_Number min = tm_tonumber_s(L, 2, 0);
		lua_Number max = tm_tonumber_s(L, 3, 1);

		if (min > max) {
			lua_Number temp = min;
			min = max;
			max = temp;
		}

		if (value < min)
			lua_pushnumber(L, min);
		else if (value > max)
			lua_pushnumber(L, max);
		else
			lua_pushnumber(L, value);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_rep(lua_State* L) {
	try {
		lua_Number value = tm_tonumber(L, 1);
		lua_Number min = tm_tonumber_s(L, 2, 0);
		lua_Number max = tm_tonumber_s(L, 3, 1);

		if (min > max) {
			lua_Number temp = min;
			min = max;
			max = temp;
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
		lua_pushnumber(L, std::tgamma(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lgamma(lua_State* L) {
	try {
		lua_pushnumber(L, std::lgamma(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_erf(lua_State* L) {
	try {
		lua_pushnumber(L, std::erf(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_erfc(lua_State* L) {
	try {
		lua_pushnumber(L, std::erfc(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_hypot(lua_State* L) {
	try {
		lua_Number x = tm_tonumber(L, 1);
		lua_Number y = tm_tonumber(L, 2);

		int tp = lua_type(L, 3);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 3, "number/none expected");
		if (tp == LUA_TNONE) {
			lua_pushnumber(L, std::hypot(x, y));
		}
		else {
			lua_Number z = tm_tonumber(L, 3);
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
		lua_pushnumber(L, std::copysign(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_gcd(lua_State* L) {
	try {
		lua_pushnumber(L, std::gcd(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lcm(lua_State* L) {
	try {
		lua_pushnumber(L, std::lcm(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_fact(lua_State* L) {
	try {
		lua_pushbignumber(L, factorial(tm_tointeger(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comb(lua_State* L) {
	try {
		lua_pushbignumber(L, combination(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_perm(lua_State* L) {
	try {
		lua_pushbignumber(L, permutation(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_rep_comb(lua_State* L) {
	try {
		lua_pushbignumber(L, repetition_combination(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_rep_perm(lua_State* L) {
	try {
		lua_pushbignumber(L, repetition_permutation(tm_tointeger(L, 1), tm_tointeger(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_circle_perm(lua_State* L) {
	try {
		lua_pushbignumber(L, circular_permutation(tm_tointeger(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_sign(lua_State* L) {
	try {
		lua_pushboolean(L, !std::signbit(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_isprime(lua_State* L) {
	try {
		lua_pushboolean(L, isprime(tm_tointeger(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_isinteger(lua_State* L) {
	try {
		lua_Number a = tm_tonumber(L, 1);
		lua_Integer b = (lua_Integer)tm_tonumber(L, 1);
		lua_pushboolean(L, a == b);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_iseven(lua_State* L) {
	try {
		lua_Integer n = tm_tointeger(L, 1);
		lua_pushboolean(L, n % 2 == 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_isodd(lua_State* L) {
	try {
		lua_Integer n = tm_tointeger(L, 1);
		lua_pushboolean(L, n % 2 != 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_classify(lua_State* L) {
	try {
		int c = std::fpclassify(tm_tonumber(L, 1));
		switch (c) {
		case FP_INFINITE:
			lua_pushstring(L, "infinite");
			break;
		case FP_NAN:
			lua_pushstring(L, "nan");
			break;
		case FP_NORMAL:
			lua_pushstring(L, "normal");
			break;
		case FP_SUBNORMAL:
			lua_pushstring(L, "subnormal");
			break;
		case FP_ZERO:
			lua_pushstring(L, "zero");
			break;
		default:
			return 0;
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_assoc_laguerre(lua_State* L) {
	try {
		lua_pushnumber(L, std::assoc_laguerre(tm_tointeger(L, 1), tm_tointeger(L, 2), tm_tonumber(L, 3)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_assoc_legendre(lua_State* L) {
	try {
		lua_pushnumber(L, std::assoc_legendre(tm_tointeger(L, 1), tm_tointeger(L, 2), tm_tonumber(L, 3)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_beta(lua_State* L) {
	try {
		lua_pushnumber(L, std::beta(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_1(lua_State* L) {
	try {
		lua_pushnumber(L, std::comp_ellint_1(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_2(lua_State* L) {
	try {
		lua_pushnumber(L, std::comp_ellint_2(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_comp_ellint_3(lua_State* L) {
	try {
		lua_pushnumber(L, std::comp_ellint_3(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_i(lua_State* L) {
	try {
		lua_pushnumber(L, std::cyl_bessel_i(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_j(lua_State* L) {
	try {
		lua_pushnumber(L, std::cyl_bessel_j(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_bessel_k(lua_State* L) {
	try {
		lua_pushnumber(L, std::cyl_bessel_k(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_cyl_neumann(lua_State* L) {
	try {
		lua_pushnumber(L, std::cyl_neumann(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_1(lua_State* L) {
	try {
		lua_pushnumber(L, std::ellint_1(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_2(lua_State* L) {
	try {
		lua_pushnumber(L, std::ellint_2(tm_tonumber(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_ellint_3(lua_State* L) {
	try {
		lua_pushnumber(L, std::ellint_3(tm_tonumber(L, 1), tm_tonumber(L, 2), tm_tonumber(L, 3)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_expint(lua_State* L) {
	try {
		lua_pushnumber(L, std::expint(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_hermite(lua_State* L) {
	try {
		lua_pushnumber(L, std::hermite(tm_tointeger(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_laguerre(lua_State* L) {
	try {
		lua_pushnumber(L, std::laguerre(tm_tointeger(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_legendre(lua_State* L) {
	try {
		lua_pushnumber(L, std::legendre(tm_tointeger(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_riemann_zeta(lua_State* L) {
	try {
		lua_pushnumber(L, std::riemann_zeta(tm_tonumber(L, 1)));
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

		lua_pushnumber(L, std::sph_bessel(tm_tointeger(L, 1), tm_tonumber(L, 2)));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sph_legendre(lua_State* L) {
	try {
		lua_pushnumber(L, std::sph_legendre(tm_tointeger(L, 1), tm_tointeger(L, 2), tm_tonumber(L, 3)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sph_neumann(lua_State* L) {
	try {
		lua_pushnumber(L, std::sph_neumann(tm_tointeger(L, 1), tm_tonumber(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_zeta(lua_State* L) {
	try {
		lua_pushnumber(L, boost::math::zeta(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_bezier(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp==LUA_TUSERDATA, 2, "number/vector2/vector3/vector4 expected");
	
		if (tp == LUA_TNUMBER) {
			lua_Number res = 0;
			int n = lua_gettop(L) - 2;
			for (int i = 0; i <= n; i++) {
				res += bernstein(t, n, i) * tm_tonumber(L, i + 2);
			}
			lua_pushnumber(L, res);
			return 1;
		}
		else if (tp == LUA_TUSERDATA) {
			if (luaL_checkmetatable(L, 2, TEXTMODULE_VECTOR2)) {
				lua_Vector2 res = { 0,0 };
				int n = lua_gettop(L) - 2;

				for (int i = 0; i <= n; i++) {
					res += bernstein(t, n, i) * (*tm_tovector2(L, i + 2));
				}
				lua_pushvector2(L, res);
				return 1;
			}
			else if (luaL_checkmetatable(L, 2, TEXTMODULE_VECTOR3)) {
				lua_Vector3 res = { 0,0,0 };
				int n = lua_gettop(L) - 2;

				for (int i = 0; i <= n; i++) {
					res += bernstein(t, n, i) * (*tm_tovector3(L, i + 2));
				}
				lua_pushvector3(L, res);
				return 1;
			}
			else if (luaL_checkmetatable(L, 2, TEXTMODULE_VECTOR4)) {
				lua_Vector4 res = { 0,0,0,0 };
				int n = lua_gettop(L) - 2;

				for (int i = 0; i <= n; i++) {
					res += bernstein(t, n, i) * (*tm_tovector4(L, i + 2));
				}
				lua_pushvector4(L, res);
				return 1;
			}
			else
				return luaL_argerror(L, 2, "number/vector2/vector3/vector4 expected");
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_equation(lua_State* L) {
	try {
		int n = lua_gettop(L);
		if (n <= 1) return 0;

		Eigen::VectorXd v(n-1);

		double a0 = tm_tonumber(L, 1);
		for (int i = 1; i < n; i++)
			v[i-1] = tm_tonumber(L, i + 1) / a0;

		Eigen::VectorXcd a = equation(v);

		for (int i = 0; i < a.size(); i++) {
			if(a[i].imag()==0)
				lua_pushnumber(L, a[i].real());
			else
				lua_pushcomplex(L, a[i]);
		}

		return a.size();
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_fibonacci_aux(lua_State* L) {
	try {
		lua_Integer n = tm_tointeger(L, lua_upvalueindex(1));
		lua_pushnumber(L, boost::math::fibonacci<lua_Number>(n));

		lua_pushinteger(L, n + 1);
		lua_replace(L, lua_upvalueindex(1));
		return 1;
	}
	catch (std::overflow_error) {
		return 0;
	}
}

int cmath_fibonacci(lua_State* L) {
	try {
		if (lua_gettop(L)>0) {
			lua_pushnumber(L, boost::math::fibonacci<lua_Number>(tm_tointeger(L, 1)));
			return 1;
		}
		else {
			lua_settop(L, 0);
			lua_pushinteger(L, 0);
			lua_pushcclosure(L, cmath_fibonacci_aux, 1);
			return 1;
		}
	}
	catch (std::overflow_error) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_prime_aux(lua_State* L) {
	try {
		lua_Integer n = tm_tointeger(L, lua_upvalueindex(1));
		lua_pushnumber(L, boost::math::prime(n-1));

		lua_pushinteger(L, n + 1);
		lua_replace(L, lua_upvalueindex(1));
		return 1;
	}
	catch (std::overflow_error) {
		return 0;
	}
	catch (std::out_of_range) {
		return 0;
	}
}

int cmath_prime(lua_State* L) {
	try {
		if (lua_gettop(L) > 0) {
			lua_pushnumber(L, boost::math::prime(tm_tointeger(L, 1)-1));
			return 1;
		}
		else {
			lua_settop(L, 0);
			lua_pushinteger(L, 0);
			lua_pushcclosure(L, cmath_prime_aux, 1);
			return 1;
		}
	}
	catch (std::overflow_error) {
		return 0;
	}
	catch (std::out_of_range) {
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_const_cmath(lua_State* L) {
	lua_settablevalue(L, "rad_to_deg", boost::math::constants::radian<lua_Number>());
	lua_settablevalue(L, "deg_to_rad", boost::math::constants::degree<lua_Number>());
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
	lua_settablevalue(L, "zeta2", boost::math::constants::zeta_two<lua_Number>());
	lua_settablevalue(L, "zeta3", boost::math::constants::zeta_three<lua_Number>());
	lua_settablevalue(L, "inv_sqrt3", std::numbers::inv_sqrt3);
	lua_settablevalue(L, "euler", std::numbers::egamma);
	lua_settablevalue(L, "egamma", std::numbers::egamma);
	lua_settablevalue(L, "phi", std::numbers::phi);
	lua_settablevalue(L, "gauss", boost::math::constants::gauss<lua_Number>());

	lua_settablevalue(L, "huge", HUGE_VAL);
	lua_settablevalue(L, "infinity", std::numeric_limits<lua_Number>::infinity());
	lua_settablevalue(L, "negative_infinity", -std::numeric_limits<lua_Number>::infinity());
	lua_settablevalue(L, "nan", NAN);
	lua_settablevalue(L, "quiet_nan", std::numeric_limits<lua_Number>::quiet_NaN());
	lua_settablevalue(L, "signaling_nan", std::numeric_limits<lua_Number>::signaling_NaN());

	lua_settablevalue(L, "min_exponent", std::numeric_limits<lua_Number>::min_exponent10);
	lua_settablevalue(L, "max_exponent", std::numeric_limits<lua_Number>::max_exponent10);
	lua_settablevalue(L, "digits", std::numeric_limits<lua_Number>::digits10);
	lua_settablevalue(L, "denorm_min", std::numeric_limits<lua_Number>::denorm_min());
	lua_settablevalue(L, "epsilon", std::numeric_limits<lua_Number>::epsilon());
}

void luaReg_cmath(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//bignumber (metatable)
		luaL_newmetatable(L, TEXTMODULE_BIGNUMBER); //add metatable
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable

		//table bignumber (metatable)
		luaL_newmetatable(L, TEXTMODULE_BIGNUMBER_TABLE);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1);


		//const
		lua_newtable(L);
		luaReg_const_cmath(L);

		//bignumber
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_REG);
		luaReg_const_bignumber(L);
		luaL_getmetatable(L, TEXTMODULE_BIGNUMBER_TABLE);
		lua_setmetatable(L, -2);
		lua_setfield(L, -2, "bignumber");

		//function
		luaL_register(L, NULL, TEXTMODULE_CMATH_REG);
		lua_setfield(L, -2, name);
	}
}