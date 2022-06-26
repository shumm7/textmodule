#include "numeric.hpp"

#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/FFT>

#include "textmodule_lua.hpp"
#include "textmodule_math.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_exception.hpp"

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
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 3, lua_typeexception("number"));
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
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA, 2, lua_typeexception({"number", "vector2", "vector3", "vector4"}));
	
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

int cmath_fft(lua_State* L) {
	try {
		if (lua_istable(L, 1)) {
			std::vector<lua_Number> time = lua_tosequence(L, 1);
			if (time.size() < 2)
				return luaL_argerror(L, 1, NOT_SEQUENCE);

			std::vector<std::complex<lua_Number>> freq;

			Eigen::FFT<lua_Number> fft;
			fft.fwd(freq, time);

			lua_newtable(L);
			for (int i = 0; i < freq.size(); i++)
				lua_settablevalue(L, i + 1, freq.at(i));

			return 1;
		}
		else {
			return luaL_typeexception(L, 1, "table");
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_invfft(lua_State* L) {
	try {
		if (lua_istable(L, 1)) {
			std::vector<lua_Complex> freq = lua_tocsequence(L, 1);
			if (freq.size() < 2)
				return luaL_argerror(L, 1, NOT_SEQUENCE);

			std::vector<lua_Number> time;

			Eigen::FFT<lua_Number> fft;
			fft.inv(time, freq);

			lua_newtable(L);
			for (int i = 0; i < time.size(); i++)
				lua_settablevalue(L, i + 1, time.at(i));

			return 1;
		}
		else {
			return luaL_typeexception(L, 1, "table");
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_const_cmath(lua_State* L) {
    // Constant
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

	lua_settablevalue(L, "huge", std::numeric_limits<lua_Number>::infinity());
	lua_settablevalue(L, "infinity", std::numeric_limits<lua_Number>::infinity());
	lua_settablevalue(L, "negative_infinity", -std::numeric_limits<lua_Number>::infinity());
	lua_settablevalue(L, "nan", std::numeric_limits<lua_Number>::quiet_NaN());
	lua_settablevalue(L, "quiet_nan", std::numeric_limits<lua_Number>::quiet_NaN());
	lua_settablevalue(L, "signaling_nan", std::numeric_limits<lua_Number>::signaling_NaN());

	lua_settablevalue(L, "min_exponent", std::numeric_limits<lua_Number>::min_exponent10);
	lua_settablevalue(L, "max_exponent", std::numeric_limits<lua_Number>::max_exponent10);
	lua_settablevalue(L, "digits", std::numeric_limits<lua_Number>::digits10);
	lua_settablevalue(L, "denorm_min", std::numeric_limits<lua_Number>::denorm_min());
	lua_settablevalue(L, "epsilon", std::numeric_limits<lua_Number>::epsilon());

	// SI Prefix
	lua_settablevalue(L, "yotta", std::pow(10, 24));
	lua_settablevalue(L, "zetta", std::pow(10, 21));
	lua_settablevalue(L, "exa", std::pow(10, 18));
	lua_settablevalue(L, "peta", std::pow(10, 15));
	lua_settablevalue(L, "tera", std::pow(10, 12));
	lua_settablevalue(L, "giga", std::pow(10, 9));
	lua_settablevalue(L, "mega", std::pow(10, 6));
	lua_settablevalue(L, "kilo", std::pow(10, 3));
	lua_settablevalue(L, "hecto", std::pow(10, 2));
	lua_settablevalue(L, "deca", std::pow(10, 1));
	lua_settablevalue(L, "deci", std::pow(10, -1));
	lua_settablevalue(L, "centi", std::pow(10, -2));
	lua_settablevalue(L, "milli", std::pow(10, -3));
	lua_settablevalue(L, "micro", std::pow(10, -6));
	lua_settablevalue(L, "nano", std::pow(10, -9));
	lua_settablevalue(L, "pico", std::pow(10, -12));
	lua_settablevalue(L, "femto", std::pow(10, -15));
	lua_settablevalue(L, "atto", std::pow(10, -18));
	lua_settablevalue(L, "zepto", std::pow(10, -21));
	lua_settablevalue(L, "yocto", std::pow(10, -24));

	// Binary Prefix
	lua_settablevalue(L, "kibi", std::pow(2, 10));
	lua_settablevalue(L, "mebi", std::pow(2, 20));
	lua_settablevalue(L, "gibi", std::pow(2, 30));
	lua_settablevalue(L, "tebi", std::pow(2, 40));
	lua_settablevalue(L, "pebi", std::pow(2, 50));
	lua_settablevalue(L, "exbi", std::pow(2, 60));
	lua_settablevalue(L, "zebi", std::pow(2, 70));
	lua_settablevalue(L, "yobi", std::pow(2, 80));
}


static luaL_Reg TEXTMODULE_NUMERIC_REG[] = {
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
	{"fft", cmath_fft},
	{"invfft", cmath_invfft},
	{ nullptr, nullptr }
};

void luaReg_numeric(lua_State* L) {
	luaReg_const_cmath(L);
	luaL_register(L, NULL, TEXTMODULE_NUMERIC_REG);
}