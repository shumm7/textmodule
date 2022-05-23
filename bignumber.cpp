#include "bignumber.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>
#include <sstream>

#include "textmodule_type.hpp"
#include "textmodule_lua.hpp"

int bignumber_bignumber(lua_State* L) {
	try {
		lua_pushbignumber(L, tm_tobignumber(L, 1));
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


void luaReg_const_bignumber(lua_State* L) {
	lua_newtable(L);
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

	lua_setfield(L, -2, "constant");
}