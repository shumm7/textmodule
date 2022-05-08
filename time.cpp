#include "time.hpp"

#include <lua.hpp>
#include <iostream>
#include <format>
#include <sstream>
#include <chrono>
#include <time.h>
#include <windows.h>
#include <ctime>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_time.hpp"

namespace chrono = std::chrono;

int time_now(lua_State* L) {
	try {
		lua_pushclock(L);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_fromtime(lua_State* L) {
	try {
		__time64_t time_c = tm_tonumber(L, 1);
		chrono::system_clock::time_point time = chrono::system_clock::from_time_t(time_c);
		lua_Clock clock = chrono::utc_clock::from_sys(time);

		lua_pushclock(L, clock);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_totime(lua_State* L) {
	try {
		lua_Clock clock = *tm_toclock(L, 1);

		chrono::system_clock::time_point now = chrono::utc_clock::to_sys(clock);
		__time64_t now_c = chrono::system_clock::to_time_t(now);

		lua_pushnumber(L, (lua_Number)now_c);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_totable(lua_State* L) {
	try {
		lua_Clock clock = *tm_toclock(L, 1);

		chrono::system_clock::time_point now = chrono::utc_clock::to_sys(clock);
		__time64_t now_c = chrono::system_clock::to_time_t(now);
		struct tm tm;

		_localtime64_s(&tm, &now_c);
		lua_pushtmstruct(L, &tm);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_fromtable(lua_State* L) {
	try {
		struct tm Time = tm{};
		__time64_t time_c;

		lua_totmstruct(L, 1, &Time);

		time_c = _mktime64(&Time);

		chrono::system_clock::time_point time = chrono::system_clock::from_time_t(time_c);
		lua_Clock clock = chrono::utc_clock::from_sys(time);

		lua_pushclock(L, clock);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int time___tostring(lua_State* L) {
	try {
		lua_Clock* time = tm_toclock(L, 1);
		std::wstringstream c;
		c << *time;

		lua_pushwstring(L, c.str());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time___add(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp==LUA_TUSERDATA, 1, "clock/number expected");

		lua_Integer sec;
		lua_Clock* time;

		if (tp == LUA_TNUMBER) {
			sec = tm_tointeger(L, 1);
			time = tm_toclock(L, 2);
		}
		else if (tp == LUA_TUSERDATA) {
			time = tm_toclock(L, 1);
			sec = tm_tointeger(L, 2);
		}
		else
			return 0;


		chrono::seconds s{ sec };
		lua_pushclock(L, *time + s);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time___sub(lua_State* L) {
	try {
		lua_Clock* time = tm_toclock(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp==LUA_TNUMBER, 2, "clock/number expected");

		if (tp == LUA_TNUMBER) {
			lua_Integer sec = tm_tointeger(L, 2);
			chrono::seconds s{ sec };

			lua_pushclock(L, *time - s);
			return 1;
		}
		else if (LUA_TUSERDATA) {
			lua_Clock* time2 = tm_toclock(L, 2);
			auto e = *time - *time2;

			lua_pushnumber(L, chrono::duration_cast<chrono::seconds>(e).count());
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_duration(lua_State* L) {
	try {
		lua_Clock* time1 = tm_toclock(L, 1);
		lua_Clock* time2 = tm_toclock(L, 2);

		long long duration = time_get_duration(*time1 - *time2, tm_tointeger_s(L, 3, 4));
		lua_pushnumber(L, duration);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_epoch(lua_State* L) {
	try {
		lua_Clock* time = tm_toclock(L, 1);

		long long duration = time_get_duration((*time).time_since_epoch(), tm_tointeger_s(L, 2, 4));
		lua_pushnumber(L, duration);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int time_localize(lua_State* L) {
	try {
		lua_Clock time = *tm_toclock(L, 1);
		std::string time_f = std::format("{:%Y-%m-%d %H:%M:%OS} UTC", time);

		// パターンを作成
		UnicodeString up = tm_toustring(L, 2);

		// ロケールを設定
		UErrorCode status = U_ZERO_ERROR;
		Locale loc = Locale(tm_tostring_s(L, 3, "en"));

		// タイムゾーンを設定
		TimeZone* timezone = TimeZone::createTimeZone(UnicodeString(tm_toustring_s(L, 4, "UTC")));

		// カレンダーを作成
		SimpleDateFormat* df = new SimpleDateFormat(UnicodeString("yyyy-MM-dd hh:mm:ss zzzz"), UnicodeString(time_f.c_str()), status);
		UnicodeString uin = UnicodeString(time_f.c_str());
		UDate inDate = df->parse(uin, status);

		// ロケールとパターンを用いてフォーマットする
		UnicodeString ud;
		SimpleDateFormat* dp = new SimpleDateFormat(up, loc, status);
		dp->setTimeZone(*timezone);
		dp->format(inDate, ud);

		lua_pushustring(L, ud);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int time_locale_pattern(lua_State* L) {
	try {
		// ロケールを指定
		Locale loc = Locale(tm_tostring_s(L, 1, "en"));

		// ロケールをもとに適切なパターンを生成
		UErrorCode status = U_ZERO_ERROR;
		DateTimePatternGenerator* g_jp = DateTimePatternGenerator::createInstance(loc, status);
		UnicodeString up_jp = g_jp->getBestPattern(UnicodeString(tm_tostring_s(L, 2, "yyyyMMddHHmmssz")), status);

		lua_pushustring(L, up_jp);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}



void luaReg_const_unit(lua_State* L, const char* name) {
	lua_newtable(L);

	lua_settablevalue(L, "nanoseconds", 1);
	lua_settablevalue(L, "microseconds", 2);
	lua_settablevalue(L, "milliseconds", 3);
	lua_settablevalue(L, "seconds", 4);
	lua_settablevalue(L, "minutes", 5);
	lua_settablevalue(L, "hours", 6);
	lua_settablevalue(L, "days", 7);
	lua_settablevalue(L, "weeks", 8);
	lua_settablevalue(L, "months", 9);
	lua_settablevalue(L, "years", 10);

	lua_setfield(L, -2, name);
}

void luaReg_time(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//time
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_TIME_REG);

		luaReg_const_unit(L, "unit");

		lua_setfield(L, -2, name);


		//time (metatable)
		luaL_newmetatable(L, TEXTMODULE_CLOCK); //add metatable
		luaL_register(L, NULL, TEXTMODULE_TIME_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_TIME_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}