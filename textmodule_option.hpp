#pragma once
#include <nlohmann/json.hpp>

#define OPTION_VMODULE "module"
#define OPTION_VAPI "api"
#define OPTION_VAPI_ALIAS "api-alias"
#define OPTION_VAPI_GLOBAL "api-global"
#define OPTION_VVER_CHECK "version-check"

#define VERSION_CHECK_ERROR -1
#define VERSION_CHECK_LATEST 0
#define VERSION_CHECK_OUTDATED 1
#define VERSION_CHECK_MSG_ERROR "version check failed"
#define VERSION_CHECK_MSG_OUTDATED "textmodule is outdated"

nlohmann::json getOption();

bool getOptionParamB(nlohmann::json j, std::string p1);
bool getOptionParamB(nlohmann::json j, std::string p1, std::string p2);
bool getOptionParamB(nlohmann::json j, std::string p1, std::string p2, std::string p3);

int versionCheck();