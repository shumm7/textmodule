#include "cmath.hpp"

#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>

#include "textmodule_lua.hpp"
#include "textmodule_math.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_exception.hpp"
#include "bignumber.hpp"

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

int cmath_trunc(lua_State* L) {
	try {
		lua_pushnumber(L, std::trunc(tm_tonumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_lerp(lua_State* L) {
	try {
		lua_pushnumber(L, std::lerp(tm_tonumber(L, 1), tm_tonumber(L, 2), tm_tonumber(L, 3)));
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


void luaReg_const_cmath(lua_State* L) {
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
		lua_newtable(L);
		luaReg_const_cmath(L);
		luaL_register(L, NULL, TEXTMODULE_CMATH_REG);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_REG);
		lua_setfield(L, -2, name);

		//bignumber (metatable)
		luaL_newmetatable(L, TEXTMODULE_BIGNUMBER); //add metatable
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}