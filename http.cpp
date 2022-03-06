#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <lua.hpp>

#include "http.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;

int http_get(lua_State* L) {
	try {
		std::wstring url = tm_towstring(L, 1);
		std::wstring body = tm_towstring(L, 2);

		web::http::http_request request(methods::GET);
		request.set_body(body);

		int i = 3;
		while (true) {
			std::wstring key;
			std::wstring value;
			if (lua_type(L, i) == LUA_TSTRING && lua_type(L, i+1) == LUA_TSTRING) {
				key = lua_towstring(L, i);
				value = lua_towstring(L, i+1);
				request.headers().add(key, value);
			}
			else {
				break;
			}
			i += 2;
		}

		web::http::client::http_client client(url);
		web::http::http_response response = client.request(request).get();
		lua_pushwstring(L, response.extract_string().get());
		lua_pushinteger(L, response.status_code());

		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int http_post(lua_State* L) {
	try {
		std::wstring url = tm_towstring(L, 1);
		std::wstring body = tm_towstring(L, 2);

		web::http::http_request request(methods::POST);
		request.set_body(body);

		int i = 3;
		while (true) {
			std::wstring key;
			std::wstring value;
			if (lua_type(L, i) == LUA_TSTRING && lua_type(L, i + 1) == LUA_TSTRING) {
				key = lua_towstring(L, i);
				value = lua_towstring(L, i + 1);
				request.headers().add(key, value);
			}
			else {
				break;
			}
			i += 2;
		}

		web::http::client::http_client client(url);
		web::http::http_response response = client.request(request).get();
		lua_pushwstring(L, response.extract_string().get());
		lua_pushinteger(L, response.status_code());

		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_http(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HTTP_REG);
		lua_setfield(L, -2, name);
	}
}

void luaGlobal_http(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HTTP_REG);
		lua_setglobal(L, name);
	}
}