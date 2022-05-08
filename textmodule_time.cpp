#include "textmodule_time.hpp"

#include <lua.hpp>
#include <chrono>

namespace chrono = std::chrono;

int time_tm_getfield(lua_State* L, int idx, const char* key, int d) {
	int res;
	lua_getfield(L, idx, key);
	if (lua_isnumber(L, -1))
		res = lua_tointeger(L, -1);
	else {
		if (d < 0)
			return luaL_error(L, "field " LUA_QS " missing in date table", key);
		res = d;
	}
	lua_pop(L, 1);
	return res;
}

long long time_get_duration(std::chrono::utc_clock::duration duration, int unit) {
	switch (unit) {
	case 1:
		return duration_cast<chrono::nanoseconds>(duration).count();
	case 2:
		return duration_cast<chrono::microseconds>(duration).count();
	case 3:
		return duration_cast<chrono::milliseconds>(duration).count();
	default:
	case 4:
		return duration_cast<chrono::seconds>(duration).count();
	case 5:
		return duration_cast<chrono::minutes>(duration).count();
	case 6:
		return duration_cast<chrono::hours>(duration).count();
	case 7:
		return duration_cast<chrono::days>(duration).count();
	case 8:
		return duration_cast<chrono::weeks>(duration).count();
	case 9:
		return duration_cast<chrono::months>(duration).count();
	case 10:
		return duration_cast<chrono::years>(duration).count();
	}
}