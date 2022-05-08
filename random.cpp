#include "random.hpp"

#include <lua.hpp>
#include <random>

#include "textmodule_lua.hpp"

int random_minstd_rand0(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::minstd_rand0 engine(seed_gen());
		lua_pushnumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_minstd_rand(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::minstd_rand engine(seed_gen());
		lua_pushnumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_mt19937(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		lua_pushnumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_mt19937_64(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());
		lua_pushbignumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_ranlux24(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::ranlux24 engine(seed_gen());
		lua_pushnumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_ranlux48(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::ranlux48 engine(seed_gen());
		lua_pushbignumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_knuth_b(lua_State* L) {
	try {
		std::random_device seed_gen;
		std::knuth_b engine(seed_gen());
		lua_pushnumber(L, engine());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int random_uniform(lua_State* L) {
	try {
		lua_Number m = 0;
		lua_Number n = 0;
		lua_Integer seed = 0;
		bool seed_set = false;

		switch (lua_gettop(L)) {
		case 0:
			m = 0;
			n = 1;
			break;
		case 1:
			m = 0;
			n = tm_tonumber(L, 1);
			break;
		case 2:
			m = tm_tonumber(L, 1);
			n = tm_tonumber(L, 2);
			break;
		case 3:
			m = tm_tonumber(L, 1);
			n = tm_tonumber(L, 2);
			seed = tm_tointeger(L, 3);
			seed_set = true;
			break;
		default:
			return luaL_error(L, "wrong number of arguments");
		}

		if (seed_set) {
			std::default_random_engine engine(seed);
			std::uniform_real_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::uniform_real_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_bernoulli(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::bernoulli_distribution dist(m);
			lua_pushboolean(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::bernoulli_distribution dist(m);
			lua_pushboolean(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_binomial(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::binomial_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::binomial_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_geometric(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::geometric_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::geometric_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_negative_binomial(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::negative_binomial_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::negative_binomial_distribution<> dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_poisson(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::poisson_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::poisson_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_exponential(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::exponential_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::exponential_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_gamma(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::gamma_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::gamma_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_weibull(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::weibull_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::weibull_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_extreme_value(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::extreme_value_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::extreme_value_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_normal(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::normal_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::normal_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_lognormal(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::lognormal_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::lognormal_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_chi_squared(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::chi_squared_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::chi_squared_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_cauchy(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::cauchy_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::cauchy_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_fisher_f(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);
		lua_Number n = tm_tonumber(L, 2);

		if (lua_type(L, 3) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 3));
			std::fisher_f_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::fisher_f_distribution dist(m, n);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int random_student_t(lua_State* L) {
	try {
		lua_Number m = tm_tonumber(L, 1);

		if (lua_type(L, 2) == LUA_TNUMBER) {
			std::default_random_engine engine(tm_tointeger(L, 2));
			std::student_t_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		else {
			std::random_device seed_gen;
			std::default_random_engine engine(seed_gen());
			std::student_t_distribution dist(m);
			lua_pushnumber(L, dist(engine));
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_random(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_RANDOM_REG);
		lua_setfield(L, -2, name);
	}
}