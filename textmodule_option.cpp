#include "textmodule_option.hpp"

#include <nlohmann/json.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>
#include <fstream>
#include <string>
#include <regex>

#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/chrono.h>

#include "textmodule.hpp"
#include "textmodule_string.hpp"
#include "textmodule_lua.hpp"

#define OPTION_PATH ".\\textmodule\\config.json"
#define VERSION_CHECK_URL L"https://raw.githubusercontent.com/shumm7/textmodule/main/VERSION"

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;

nlohmann::json getOption() {
	std::ifstream ifs(OPTION_PATH);
	nlohmann::json j;
	ifs >> j;

	return j;
}

int versionCheck() {
	try {
		std::wstring url = VERSION_CHECK_URL;

		web::http::client::http_client client(url);
		web::http::http_request request(methods::GET);
		web::http::http_response response = client.request(request).get();

		if (response.status_code() == status_codes::OK) {
			std::wstring v = std::regex_replace(response.extract_string().get(), wregex(L"\n"), L"\0");
			if (v == tostring_n(MODULE_VERSION))
				return VERSION_CHECK_LATEST;
			else
				return VERSION_CHECK_OUTDATED;

		}
		else {
			return VERSION_CHECK_ERROR;
		}
	}
	catch (std::exception) {
		return VERSION_CHECK_ERROR;
	}
}


void tm_debuglog(lua_Option opt, lua_Sstring tag, lua_Sstring log) {
	if (opt["debug"]) {
		fmt::dynamic_format_arg_store<fmt::format_context> store;

		std::tm tm;
		__time64_t time_t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		_localtime64_s(&tm, &time_t);
		store.push_back(tm);
		store.push_back(tag);
		store.push_back(log);

		std::string c = fmt::vformat("[{0:%Y-%m-%d %H-%M-%S}] (textmodule): debug log: [{1:s}] {2:s}", store);

		OutputDebugStringA(c.c_str());
		//std::cout << c << std::endl;
	}
}

void tm_debuglog_apiloaded(lua_Option opt, lua_Sstring apiname) {
	std::string s = apiname + std::string(" was successfully loaded");
	tm_debuglog(opt, "API", s);
}

void tm_debuglog_apinoloaded(lua_Option opt, lua_Sstring apiname) {
	std::string s = apiname + std::string(" was not loaded");
	tm_debuglog(opt, "API", s);
}