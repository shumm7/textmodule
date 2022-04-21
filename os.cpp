#include <lua.hpp>
#include <iostream>
#include <chrono>
#include <time.h>
#include <windows.h>

#include "os.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

lua_Integer tm_getfield(lua_State* L, const char* key, int d) {
	lua_Integer res;
	lua_getfield(L, -1, key);
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

int os_time(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TTABLE, 1, "table/none expected");

		if (tp == LUA_TNONE) {
			std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
			__time64_t now_c = std::chrono::system_clock::to_time_t(now);

			lua_pushnumber(L, (lua_Number)now_c);
			return 1;
		}
		else if (tp == LUA_TTABLE) {
			struct tm Time;
			__time64_t res;

			Time.tm_isdst = tm_getfield(L, "isdst", false);
			Time.tm_year = tm_getfield(L, "year", -1) - 1900;
			Time.tm_mon = tm_getfield(L, "month", -1) - 1;
			Time.tm_mday = tm_getfield(L, "day", -1);
			Time.tm_hour = tm_getfield(L, "hour", 12);
			Time.tm_min = tm_getfield(L, "min", 0);
			Time.tm_sec = tm_getfield(L, "sec", 0);

			res = _mktime64(&Time);
			lua_pushnumber(L, (lua_Number)res);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
	return 0;
}

int os_date(lua_State* L) {
	try {
		lua_Wstring format;
		bool utc = false;
		__time64_t time_t;

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, 1, "string/none expected");

		if (tp == LUA_TNONE)
			format = L"%c";
		else if (tp== LUA_TSTRING)
			format = lua_towstring(L, 1);


		if (format[0] == L'!') {  // is UTC?
			utc = true;
			format = format.substr(1);
		}


		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER)
			time_t = static_cast<__time64_t>(lua_tonumber(L, 2));
		else
			time_t = std::chrono::system_clock::to_time_t(now);

		if (format == L"*t") {
			struct tm tm;
			if (utc) //make tm struct
				_gmtime64_s(&tm, &time_t);
			else
				_localtime64_s(&tm, &time_t);

			lua_newtable(L);
			lua_pushinteger(L, tm.tm_year + 1900);
			lua_setfield(L, -2, "year");
			lua_pushinteger(L, tm.tm_mon + 1);
			lua_setfield(L, -2, "month");
			lua_pushinteger(L, tm.tm_mday);
			lua_setfield(L, -2, "day");
			lua_pushinteger(L, tm.tm_hour);
			lua_setfield(L, -2, "hour");
			lua_pushinteger(L, tm.tm_min);
			lua_setfield(L, -2, "min");
			lua_pushinteger(L, tm.tm_sec);
			lua_setfield(L, -2, "sec");
			lua_pushinteger(L, tm.tm_wday + 1);
			lua_setfield(L, -2, "wday");
			lua_pushinteger(L, tm.tm_yday + 1);
			lua_setfield(L, -2, "yday");
			lua_pushinteger(L, tm.tm_isdst);
			lua_setfield(L, -2, "isdst");

			return 1;
		}
		else {
			std::wstring f = L"{:" + format + L"}";

			std::chrono::sys_seconds now_sec = std::chrono::floor<std::chrono::seconds>(now); // �b�P��
			std::chrono::zoned_seconds zone_time;
			if (utc)
				zone_time = { "UTC" , now_sec };
			else
				zone_time = { std::chrono::current_zone() , now_sec };

			std::chrono::local_seconds local_time = zone_time.get_local_time();

			
			f = std::format(f, local_time);
			lua_pushwstring(L, f);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int os_difftime(lua_State* L) {
	try {
		__time64_t time2_t = static_cast<__time64_t>(tm_tonumber(L, 1));
		__time64_t time1_t = static_cast<__time64_t>(tm_tonumber(L, 2));

		std::chrono::time_point time2 = std::chrono::system_clock::from_time_t(time2_t);
		std::chrono::time_point time1 = std::chrono::system_clock::from_time_t(time1_t);
		int sec = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(time2 - time1).count());

		lua_pushnumber(L, sec);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int os_clock(lua_State* L) {
	try {
		clock_t clk = clock();

		lua_pushnumber(L, (lua_Number)clk / (lua_Number)CLOCKS_PER_SEC);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int os_sleep(lua_State* L) {
	try {
		lua_Number time = tm_tonumber_s(L, 1, 0);

		if (time <= 0)
			return 0;

		Sleep(static_cast<DWORD>(time * 1000.0));
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_os(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_OS_REG);
		lua_setfield(L, -2, name);
	}
}