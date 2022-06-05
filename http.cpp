#include "http.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <streambuf>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include "MultipartEncoder/multipart_parser.h"
#include <lua.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
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

void _download(concurrency::streams::istream inBody, size_t inChunk, size_t inLength, size_t inContentLength, Concurrency::streams::streambuf<unsigned char>& outBuff)
{
	size_t nLength = inBody.read(outBuff, inChunk).get();
	if (nLength > 0) {
		_download(inBody, inChunk, inLength + nLength, inContentLength, outBuff);
	}
	else {
		return;
	}
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

int http_head(lua_State* L) {
	try {
		lua_Wstring url = tm_towstring(L, 1);

		web::http::http_request request(methods::HEAD);
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

int http_put(lua_State* L) {
	try {
		lua_Wstring url = tm_towstring(L, 1);
		lua_Wstring body = tm_towstring(L, 2);

		web::http::http_request request(methods::PUT);
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

int http_delete(lua_State* L) {
	try {
		lua_Wstring url = tm_towstring(L, 1);
		lua_Wstring body = tm_towstring(L, 2);

		web::http::http_request request(methods::DEL);
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

int http_download(lua_State* L) {
	try {
		std::wstring url = tm_towstring(L, 1);
		
		web::http::http_request request(methods::GET);
		request = set_header(L, 2, request);

		std::wstring path = tm_towstring(L, 3);
		web::http::client::http_client client(url);
		web::http::http_response response = client.request(request).get();

		size_t content_length(0);
		content_length = response.headers().content_length();
		if (response.status_code() != status_codes::OK)
			throw std::runtime_error(WstrToStr(L"failed to get "+url));

		concurrency::streams::istream stream = response.body();;
		Concurrency::streams::streambuf<unsigned char> buffer = file_buffer<unsigned char>::open(path).get();
		if (content_length == 0) throw std::runtime_error("content length is zero.");
		else {
			size_t chunk = content_length / 10;
			_download(stream, chunk, 0, content_length, buffer);
		}
		buffer.close().wait();

		lua_pushwstring(L, response.extract_string().get());
		lua_pushinteger(L, response.status_code());
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int http_encode(lua_State* L) {
	try {
		std::wstring encoded = web::uri::encode_uri(tm_towstring(L, 1));
		lua_pushwstring(L, encoded);	
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int http_decode(lua_State* L) {
	try {
		std::wstring decoded = web::uri::decode(tm_towstring(L, 1));
		lua_pushwstring(L, decoded);
		return 1;
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