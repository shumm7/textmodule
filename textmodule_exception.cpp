#include "textmodule_exception.hpp"
#include <lua.hpp>
#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>
#include <nlohmann/json.hpp>

const char* lua_typeexception(std::vector<std::string> type) {
	int m = type.size();
	if (m <= 0) {
		type.push_back("no value");
	}

	std::string ret = "";
	for (int i = 0; i < m-1; i++)
		ret += (type.at(i) + "/");

	ret += type.at(m - 1);
	ret += " expected";
	return ret.c_str();
}

const char* lua_typeexception(std::string type) {
	std::string ret = type + " expected";
	return  ret.c_str();
}

int luaL_argerror(lua_State* L, int numarg, std::string extramsg) {
	return luaL_argerror(L, numarg, extramsg.c_str());
}

int luaL_typeexception(lua_State* L, int numarg, std::vector<std::string> type) {
	return luaL_argerror(L, numarg, lua_typeexception(type));
}

int luaL_typeexception(lua_State* L, int numarg, std::string type) {
	return luaL_argerror(L, numarg, lua_typeexception(type));
}


void tm_debuglog(std::string message, nlohmann::json option) {
	if (option["debug"].is_boolean()) {
		if (option["debug"]) {
			message = std::format("[{:%F %x} textmodule]", std::chrono::system_clock::now()) + message;
			OutputDebugString(message.c_str());
		}
	}
}