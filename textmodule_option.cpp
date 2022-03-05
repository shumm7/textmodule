#include <nlohmann/json.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>
#include <fstream>
#include <string>

#include "textmodule.h"
#include "textmodule_option.h"
#include "textmodule_string.h"

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

bool getOptionParamB(nlohmann::json j, std::string p1) {
	return j[p1].get<bool>();
}

bool getOptionParamB(nlohmann::json j, std::string p1, std::string p2) {
	return j[p1][p2].get<bool>();
}

int versionCheck() {
	try {
		std::wstring url = VERSION_CHECK_URL;

		web::http::client::http_client client(url);
		web::http::http_request request(methods::GET);
		web::http::http_response response = client.request(request).get();

		if (response.status_code() == status_codes::OK) {
			std::wstring v = response.extract_string().get();
			if (v == tostring_n(MODULE_VERSION)) {
				return VERSION_CHECK_LATEST;
			}
			else {
				return VERSION_CHECK_OUTDATED;
			}
		}
		else {
			return VERSION_CHECK_ERROR;
		}
	}
	catch (std::exception& e) {
		return VERSION_CHECK_ERROR;
	}
}