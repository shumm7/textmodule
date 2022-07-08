#pragma once
#include <nlohmann/json.hpp>
#include "textmodule_lua.hpp"

#define OPTION_VMODULE "module"
#define OPTION_VMODULE_ALIAS "module-alias"

#define OPTION_VAPI "api"
#define OPTION_VAPI_ALIAS "api-alias"
#define OPTION_VAPI_GLOBAL "api-global"
#define OPTION_VVER_CHECK "version-check"

#define VERSION_CHECK_ERROR -1
#define VERSION_CHECK_LATEST 0
#define VERSION_CHECK_OUTDATED 1
#define VERSION_CHECK_MSG_ERROR "version check failed"
#define VERSION_CHECK_MSG_OUTDATED "textmodule is outdated"

typedef lua_Json lua_Option;

nlohmann::json getOption();
int versionCheck();

void tm_debuglog(lua_Option opt, lua_Sstring tag, lua_Sstring log);
void tm_debuglog_apiloaded(lua_Option opt, lua_Sstring apiname);
void tm_debuglog_apinoloaded(lua_Option opt, lua_Sstring apiname);