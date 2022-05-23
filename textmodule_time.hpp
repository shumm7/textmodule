#pragma once
#include <lua.hpp>
#include <chrono>

int time_tm_getfield(lua_State* L, int idx, const char* key, int d);
long long time_get_duration(std::chrono::utc_clock::duration duration, int unit);