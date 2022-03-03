#include <lua.hpp>
#include <iostream>
#include <chrono>
#include <time.h>
#include <windows.h>

#include "os.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

using namespace std::chrono;

int os_time(lua_State* L) {
	try {
		if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			auto now = std::chrono::system_clock::now();
			__time64_t now_c = std::chrono::system_clock::to_time_t(now);

			lua_pushnumber(L, static_cast<double>(now_c));
			return 1;
		}
		else if (lua_type(L, 1) == LUA_TTABLE) {
			lua_getfield(L, 1, "year");
			lua_getfield(L, 1, "month");
			lua_getfield(L, 1, "day");
			lua_getfield(L, 1, "hour");
			lua_getfield(L, 1, "min");
			lua_getfield(L, 1, "sec");

			struct tm Time = { 0, 0, 0, 1, 0, 0 };
			__time64_t res;

			if (lua_type(L, -6) == LUA_TNUMBER) //year
				Time.tm_year = lua_tointeger(L, -6) - 1900;
			else
				return 0;
			if (lua_type(L, -5) == LUA_TNUMBER) //month
				Time.tm_mon = lua_tointeger(L, -5) - 1;
			else
				return 0;
			if (lua_type(L, -4) == LUA_TNUMBER) //day
				Time.tm_mday = lua_tointeger(L, -4);
			else
				return 0;

			if (lua_type(L, -3) == LUA_TNUMBER) //hour
				Time.tm_hour = lua_tointeger(L, -3);
			if (lua_type(L, -2) == LUA_TNUMBER) //min
				Time.tm_min = lua_tointeger(L, -2);
			if (lua_type(L, -1) == LUA_TNUMBER) //sec
				Time.tm_sec = lua_tointeger(L, -1);

			res = _mktime64(&Time);
			lua_pushnumber(L, static_cast<double>(res));
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
		std::wstring format;
		bool utc = false;

		__time64_t time_t;


		if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			format = L"%c";
		}
		else if (lua_type(L, 1) == LUA_TSTRING) {
			format = lua_towstring(L, 1);
		}
		else {
			return 0;
		}

		if (format[0] == L'!') {  //UTC
			utc = true;
			format = format.substr(1);
		}


		std::chrono::time_point now = std::chrono::system_clock::now();

		if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			time_t = std::chrono::system_clock::to_time_t(now);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			time_t = static_cast<__time64_t>(lua_tonumber(L, 2));
		}
		else {
			return 0;
		}


		if (format == L"*t") {
			struct tm tm;
			if (utc) { //tm struct
				_gmtime64_s(&tm, &time_t);
			}
			else {
				_localtime64_s(&tm, &time_t);
			}

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
			if (utc) {
				zone_time = { "UTC" , now_sec };
			}
			else {
				zone_time = { std::chrono::current_zone() , now_sec };
			}
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
		__time64_t time2_t;
		__time64_t time1_t;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			time2_t = static_cast<__time64_t>(lua_tonumber(L, 1));
		}
		else {
			return 0;
		}
		if (lua_type(L, 2) == LUA_TNUMBER) {
			time1_t = static_cast<__time64_t>(lua_tonumber(L, 2));
		}
		else {
			return 0;
		}

		time_point time2 = std::chrono::system_clock::from_time_t(time2_t);
		time_point time1 = std::chrono::system_clock::from_time_t(time1_t);
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

		lua_pushnumber(L, (double)clk / (double)CLOCKS_PER_SEC);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int os_sleep(lua_State* L) {
	try {
		double time;
		if (lua_type(L, 1) == LUA_TNUMBER) {
			time = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

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