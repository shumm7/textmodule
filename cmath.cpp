#include "cmath.hpp"

#include <lua.hpp>
#include <iostream>
#include <cmath>

#include "textmodule_lua.hpp"
#include "textmodule_math.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_exception.hpp"
#include "numeric.hpp"
#include "bignumber.hpp"
#include "sequence.hpp"

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
		if (tm_callmetan(L, 1, "__fmod"))
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
		if (tm_callmetan(L, 1, "__frexp"))
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
		if (tm_callmetan(L, 1, "__ldexp"))
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
		if (tm_callmetan(L, 1, "__log"))
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
		if (tm_callmetan(L, 1, "__max"))
			return 1;

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TTABLE || tp == LUA_TNONE, 1, "number/table expected");

		std::vector<lua_Number> v;
		if (tp == LUA_TTABLE) {
			v = lua_tosequence(L, 1);
		}
		else {
			int n = lua_gettop(L);
			for (int i = 0; i < n; i++)
				v.push_back(tm_tonumber(L, i + 1));
		}

		lua_pushnumber(L, array_max(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_min(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__min"))
			return 1;

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TTABLE || tp == LUA_TNONE, 1, "number/table expected");

		std::vector<lua_Number> v;
		if (tp == LUA_TTABLE) {
			v = lua_tosequence(L, 1);
		}
		else {
			int n = lua_gettop(L);
			for (int i = 0; i < n; i++)
				v.push_back(tm_tonumber(L, i + 1));
		}

		lua_pushnumber(L, array_min(v));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int cmath_modf(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__min"))
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
		if (tm_callmetan(L, 1, "__pow"))
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
		if (tm_callmetan(L, 1, "__lerp"))
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
		if (tm_callmetan(L, 1, "__dot"))
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
		if (tm_callmetan(L, 1, "__cross"))
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
		if (tm_callmetan(L, 1, "__scale"))
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
		if (tm_callmetan(L, 1, "__distance"))
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

		luaL_argcheck(L, lua_istable(L, 1) || lua_isnumber(L, 1), 1, "number/table expected");

		if (lua_istable(L, 1)) {
			std::vector<double> v = lua_tosequence(L, 1);
			auto vec = array_normalize(v);
			lua_newtable(L);
			for (int i = 0; i < vec.size(); i++)
				lua_settablevalue(L, i + 1, vec.at(i));
		}
		else if(lua_isnumber(L, 1)) {
			lua_Number d = tm_tonumber(L, 1);
			lua_pushnumber(L, d / std::fabs(d));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


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
	{ nullptr, nullptr }
};

void luaReg_cmath(lua_State* L, lua_Option opt) {
	if (opt["api"]["math"]) {
		tm_debuglog_apiloaded(opt, "math");

		lua_newtable(L);

		//bignumber
		lua_newtable(L);
		luaReg_bignumber(L);
		luaReg_const_bignumber(L);
		luaL_getmetatable(L, TEXTMODULE_BIGNUMBER_TABLE);
		lua_setmetatable(L, -2);
		lua_setfield(L, -2, "bignumber");

		//math
		luaL_register(L, NULL, TEXTMODULE_CMATH_REG);
		luaReg_numeric(L);
		luaReg_sequence(L);
		lua_setfield(L, -2, "math");
	}
	else {
		tm_debuglog_apinoloaded(opt, "math");
	}
}