#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>

#include "textmodule_option.h"
#include "textmodule_string.h"

#define OPTION_PATH ".\\textmodule\\config.json"

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