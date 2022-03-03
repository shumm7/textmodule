#pragma once
#include <nlohmann/json.hpp>

#define OPTION_VMODULE "module"
#define OPTION_VAPI "api"
#define OPTION_VAPI_ALIAS "api-alias"
#define OPTION_VAPI_GLOBAL "api-global"

nlohmann::json getOption();
bool getOptionParamB(nlohmann::json j, std::string p1);
bool getOptionParamB(nlohmann::json j, std::string p1, std::string p2);