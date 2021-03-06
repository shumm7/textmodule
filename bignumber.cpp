#include "bignumber.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

#include "textmodule_type.hpp"
#include "textmodule_lua.hpp"

int bignumber_new(lua_State* L) {
	try {
		luaL_argcheck(L, lua_isstring(L, 2) || lua_isnumber(L, 2) || (lua_isuserdata(L, 2) && luaL_checkmetatable(L, 2, TEXTMODULE_BIGNUMBER)), 1, "string/number/bignumber expected");
		
		lua_pushbignumber(L, tm_tobignumber(L, 2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___tostring(lua_State* L) {
	try {
		lua_Bignumber n = tm_tobignumber(L, 1);
		lua_pushsstring(L, n.str());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___tonumber(lua_State* L) {
	try {
		lua_Bignumber n = tm_tobignumber(L, 1);
		lua_pushnumber(L, (lua_Number)n);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___add(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) + tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___sub(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) - tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___mul(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) * tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___div(lua_State* L) {
	try {
		lua_Bignumber ret = tm_tobignumber(L, 1) / tm_tobignumber(L, 2);
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___mod(lua_State* L) {
	try {
		lua_Bignumber ret = boost::multiprecision::fmod(tm_tobignumber(L, 1), tm_tobignumber(L, 2));
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___pow(lua_State* L) {
	try {
		lua_Bignumber ret = boost::multiprecision::pow(tm_tobignumber(L, 1), tm_tointeger(L, 2));
		lua_pushbignumber(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___unm(lua_State* L) {
	try {
		lua_pushbignumber(L, -tm_tobignumber(L, 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___lt(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) < tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___le(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) <= tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___eq(lua_State* L) {
	try {
		bool ret = tm_tobignumber(L, 1) == tm_tobignumber(L, 2);
		lua_pushboolean(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___type(lua_State* L) {
	try {
		lua_pushstring(L, "bignumber");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int bignumber___abs(lua_State* L) {
	try {
		lua_pushbignumber(L, boost::multiprecision::fabs(tm_tobignumber(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_const_bignumber(lua_State* L) {
	// Constant
	lua_settablevalue(L, "rad_to_deg", boost::math::constants::radian<lua_Bignumber>());
	lua_settablevalue(L, "deg_to_rad", boost::math::constants::degree<lua_Bignumber>());
	lua_settablevalue(L, "e", boost::math::constants::e<lua_Bignumber>());
	lua_settablevalue(L, "napier", boost::math::constants::e<lua_Bignumber>());
	lua_settablevalue(L, "log2e", boost::math::constants::log2_e<lua_Bignumber>());
	lua_settablevalue(L, "log10e", boost::math::constants::log10_e<lua_Bignumber>());
	lua_settablevalue(L, "pi", boost::math::constants::pi<lua_Bignumber>());
	lua_settablevalue(L, "inv_pi", 1.0 / boost::math::constants::pi<lua_Bignumber>());
	lua_settablevalue(L, "inv_sqrtpi", 1.0 / boost::math::constants::root_pi<lua_Bignumber>());
	lua_settablevalue(L, "ln2", boost::math::constants::ln_two<lua_Bignumber>());
	lua_settablevalue(L, "ln10", boost::math::constants::ln_ten<lua_Bignumber>());
	lua_settablevalue(L, "sqrt2", boost::math::constants::root_two<lua_Bignumber>());
	lua_settablevalue(L, "sqrt3", boost::math::constants::root_three<lua_Bignumber>());
	lua_settablevalue(L, "zeta2", boost::math::constants::zeta_two<lua_Bignumber>());
	lua_settablevalue(L, "zeta3", boost::math::constants::zeta_three<lua_Bignumber>());
	lua_settablevalue(L, "inv_sqrt3", 1.0 / boost::math::constants::root_three<lua_Bignumber>());
	lua_settablevalue(L, "euler", boost::math::constants::euler<lua_Bignumber>());
	lua_settablevalue(L, "egamma", boost::math::constants::euler<lua_Bignumber>());
	lua_settablevalue(L, "phi", boost::math::constants::phi<lua_Bignumber>());
	lua_settablevalue(L, "gauss", boost::math::constants::gauss<lua_Bignumber>());

	lua_settablevalue(L, "huge", std::numeric_limits<lua_Bignumber>::infinity());
	lua_settablevalue(L, "infinity", std::numeric_limits<lua_Bignumber>::infinity());
	lua_settablevalue(L, "negative_infinity", -std::numeric_limits<lua_Bignumber>::infinity());
	lua_settablevalue(L, "nan", std::numeric_limits<lua_Bignumber>::quiet_NaN());
	lua_settablevalue(L, "quiet_nan", std::numeric_limits<lua_Bignumber>::quiet_NaN());
	lua_settablevalue(L, "signaling_nan", std::numeric_limits<lua_Bignumber>::signaling_NaN());

	lua_settablevalue(L, "min_exponent", std::numeric_limits<lua_Bignumber>::min_exponent10);
	lua_settablevalue(L, "max_exponent", std::numeric_limits<lua_Bignumber>::max_exponent10);
	lua_settablevalue(L, "digits", std::numeric_limits<lua_Bignumber>::digits10);
	lua_settablevalue(L, "denorm_min", std::numeric_limits<lua_Bignumber>::denorm_min());
	lua_settablevalue(L, "epsilon", std::numeric_limits<lua_Bignumber>::epsilon());

	// SI Prefix
	lua_settablevalue(L, "yotta", boost::multiprecision::pow(lua_Bignumber(10), 24));
	lua_settablevalue(L, "zetta", boost::multiprecision::pow(lua_Bignumber(10), 21));
	lua_settablevalue(L, "exa", boost::multiprecision::pow(lua_Bignumber(10), 18));
	lua_settablevalue(L, "peta", boost::multiprecision::pow(lua_Bignumber(10), 15));
	lua_settablevalue(L, "tera", boost::multiprecision::pow(lua_Bignumber(10), 12));
	lua_settablevalue(L, "giga", boost::multiprecision::pow(lua_Bignumber(10), 9));
	lua_settablevalue(L, "mega", boost::multiprecision::pow(lua_Bignumber(10), 6));
	lua_settablevalue(L, "kilo", boost::multiprecision::pow(lua_Bignumber(10), 3));
	lua_settablevalue(L, "hecto", boost::multiprecision::pow(lua_Bignumber(10), 2));
	lua_settablevalue(L, "deca", boost::multiprecision::pow(lua_Bignumber(10), 1));
	lua_settablevalue(L, "deci", boost::multiprecision::pow(lua_Bignumber(10), -1));
	lua_settablevalue(L, "centi", boost::multiprecision::pow(lua_Bignumber(10), -2));
	lua_settablevalue(L, "milli", boost::multiprecision::pow(lua_Bignumber(10), -3));
	lua_settablevalue(L, "micro", boost::multiprecision::pow(lua_Bignumber(10), -6));
	lua_settablevalue(L, "nano", boost::multiprecision::pow(lua_Bignumber(10), -9));
	lua_settablevalue(L, "pico", boost::multiprecision::pow(lua_Bignumber(10), -12));
	lua_settablevalue(L, "femto", boost::multiprecision::pow(lua_Bignumber(10), -15));
	lua_settablevalue(L, "atto", boost::multiprecision::pow(lua_Bignumber(10), -18));
	lua_settablevalue(L, "zepto", boost::multiprecision::pow(lua_Bignumber(10), -21));
	lua_settablevalue(L, "yocto", boost::multiprecision::pow(lua_Bignumber(10), -24));

	// Binary Prefix
	lua_settablevalue(L, "kibi", boost::multiprecision::pow(lua_Bignumber(2), 10));
	lua_settablevalue(L, "mebi", boost::multiprecision::pow(lua_Bignumber(2), 20));
	lua_settablevalue(L, "gibi", boost::multiprecision::pow(lua_Bignumber(2), 30));
	lua_settablevalue(L, "tebi", boost::multiprecision::pow(lua_Bignumber(2), 40));
	lua_settablevalue(L, "pebi", boost::multiprecision::pow(lua_Bignumber(2), 50));
	lua_settablevalue(L, "exbi", boost::multiprecision::pow(lua_Bignumber(2), 60));
	lua_settablevalue(L, "zebi", boost::multiprecision::pow(lua_Bignumber(2), 70));
	lua_settablevalue(L, "yobi", boost::multiprecision::pow(lua_Bignumber(2), 80));
}

static luaL_Reg TEXTMODULE_BIGNUMBER_REG[]{
	{"__call", bignumber_new},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_BIGNUMBER_META_REG[]{
	{"__tostring", bignumber___tostring},
	{"__tonumber", bignumber___tonumber},
	{"__add", bignumber___add},
	{"__sub", bignumber___sub},
	{"__mul", bignumber___mul},
	{"__div", bignumber___div},
	{"__mod", bignumber___mod},
	{"__pow", bignumber___pow},
	{"__unm", bignumber___unm},
	{"__lt", bignumber___lt},
	{"__le", bignumber___le},
	{"__eq", bignumber___eq},
	{"__type", bignumber___type},
	{nullptr, nullptr}
};

void luaReg_bignumber(lua_State* L) {
	luaL_newmetatable(L, TEXTMODULE_BIGNUMBER, TEXTMODULE_BIGNUMBER_META_REG);
	luaL_newmetatable(L, TEXTMODULE_BIGNUMBER_TABLE, TEXTMODULE_BIGNUMBER_REG);

	luaL_register(L, NULL, TEXTMODULE_BIGNUMBER_REG);
}