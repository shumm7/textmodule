#include "sequence.hpp"
#include <lua.hpp>
#include <iostream>
#include <cmath>
#include <numbers>
#include <numeric>

#include <boost/math/special_functions/fibonacci.hpp>
#include <boost/math/special_functions/prime.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_math.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_exception.hpp"

int cmath_aseq(lua_State* L) {
	try {
		double start = 1;
		int cnt = 0;
		double step = 1;

		switch (lua_gettop(L)) {
		case 0:
			lua_newtable(L);
			return 1;
		case 1:
			cnt = tm_tointeger(L, 1);
			break;
		default:
			start = tm_tonumber(L, 1);
			cnt = tm_tointeger(L, 2);
			step = tm_tonumber_s(L, 3, 1);
			break;
		}

		lua_newtable(L);
		double n = start;
		for (int c = 1; c <= cnt; c++) {
			lua_settablevalue(L, c, n);
			n += step;
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_gseq(lua_State* L) {
	try {
		double start = 1;
		int cnt = 0;
		double step = 1;

		switch (lua_gettop(L)) {
		case 0:
			lua_newtable(L);
			return 1;
		case 1:
			cnt = tm_tointeger(L, 1);
			break;
		default:
			start = tm_tonumber(L, 1);
			cnt = tm_tointeger(L, 2);
			step = tm_tonumber_s(L, 3, 1);
			break;
		}

		lua_newtable(L);
		double n = start;
		for (int c = 1; c <= cnt; c++) {
			lua_settablevalue(L, c, n);
			n *= step;
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_arange(lua_State* L) {
	try {
		double start = 1;
		double max = 0;
		double step = 1;

		switch (lua_gettop(L)) {
		case 0:
			lua_newtable(L);
			return 1;
		case 1:
			max = tm_tonumber(L, 1);
			break;
		default:
			start = tm_tonumber(L, 1);
			max = tm_tonumber(L, 2);
			step = tm_tonumber_s(L, 3, 1);
			break;
		}

		lua_newtable(L);
		int c = 1;
		for (double i = start; i <= max; i += step) {
			lua_settablevalue(L, c, i);
			c++;
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_linspace(lua_State* L) {
	try {
		double start = 0;
		double stop = 1;
		double div = 3;

		switch (lua_gettop(L)) {
		case 1:
			div = tm_tointeger(L, 1);
			break;
		default:
			start = tm_tonumber(L, 1);
			stop = tm_tonumber(L, 2);
			div = tm_tointeger_s(L, 3, 3);
			break;
		}
		if (div < 1)
			throw std::out_of_range(OUT_OF_RANGE);

		lua_newtable(L);
		double n = stop - start;
		for (int i = 0; i < div; i++) {
			lua_settablevalue(L, i + 1, start + n*(i/(div-1)) );
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_ascend(lua_State* L) {
	try {
		std::vector<lua_Number> s = lua_tosequence(L, 1);
		std::sort(s.begin(), s.end());

		lua_newtable(L);
		for (int i = 0; i < s.size(); i++)
			lua_settablevalue(L, i + 1, s.at(i));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_descend(lua_State* L) {
	try {
		std::vector<lua_Number> s = lua_tosequence(L, 1);
		std::sort(s.begin(), s.end(), std::greater<lua_Number>{});

		lua_newtable(L);
		for (int i = 0; i < s.size(); i++)
			lua_settablevalue(L, i + 1, s.at(i));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sum(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_sum(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_mean(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_mean(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_variance(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_var(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_uvariance(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_uvar(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_deviation(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, std::sqrt(array_var(v)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_sdeviation(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, std::sqrt(array_uvar(v)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_median(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_median(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_mode(lua_State* L) {
	try {
		std::vector<lua_Number> v = lua_tosequence(L, 1);
		lua_pushnumber(L, array_mode(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int cmath_fibonacci(lua_State* L) {
	try {
		int len = tm_tonumber(L, 1);
		if (len < 0) throw std::out_of_range(OUT_OF_RANGE);

		lua_newtable(L);
		for (int i = 0; i <= len; i++)
			lua_settablevalue(L, i+1, boost::math::fibonacci<lua_Number>(i));
		return 1;
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

int cmath_prime(lua_State* L) {
	try {
		int len = tm_tonumber(L, 1);
		if (len < 0) throw std::out_of_range(OUT_OF_RANGE);

		lua_newtable(L);
		for (int i = 0; i < len; i++)
			lua_settablevalue(L, i+1, (lua_Number)boost::math::prime(i));
		return 1;
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


static luaL_Reg TEXTMODULE_SEQUENCE_REG[] = {
	{"aseq", cmath_aseq},
	{"gseq", cmath_gseq},
	{"arange", cmath_arange},
	{"linspace", cmath_linspace},

	{"ascend", cmath_ascend},
	{"descend", cmath_descend},
	{"sum", cmath_sum},
	{"mean", cmath_mean},
	{"variance", cmath_variance},
	{"uvariance", cmath_uvariance},
	{"deviation", cmath_deviation},
	{"sdeviation", cmath_sdeviation},
	{"median", cmath_median},
	{"mode", cmath_mode},

	{"fibonacci", cmath_fibonacci},
	{"prime", cmath_prime},

	{ nullptr, nullptr }
};

void luaReg_sequence(lua_State* L) {
	luaL_register(L, NULL, TEXTMODULE_SEQUENCE_REG);
}