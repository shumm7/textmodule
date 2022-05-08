#include "http.hpp"

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <lua.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;

web::http::http_request set_header(lua_State* L, int idx, web::http::http_request request) {
	int type = lua_type(L, idx);
	luaL_argcheck(L,  type == LUA_TNONE || type == LUA_TNIL|| type== LUA_TTABLE, idx, "table/nil/none expected");
	if (type == LUA_TTABLE) {
		lua_pushnil(L);
		while (lua_next(L, idx) != 0) {
			lua_Wstring key = tm_towstring(L, -2);
			lua_Wstring value = tm_towstring(L, -1);
			request.headers().add(key, value);
			lua_pop(L, 1);
		}
	}
	return request;
}

int http_get(lua_State* L) {
	try {
		lua_Wstring url = tm_towstring(L, 1);

		web::http::http_request request(methods::GET);
		request = set_header(L, 2, request);

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
		lua_Wstring url = tm_towstring(L, 1);
		lua_Wstring body = tm_towstring(L, 2);

		web::http::http_request request(methods::POST);
		request.set_body(body);

		request = set_header(L, 3, request);

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