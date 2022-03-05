﻿#include <lua.hpp>
#include <nlohmann/json.hpp>

#include "textmodule.h"
#include "textmodule_string.h"
#include "textmodule_option.h"

#include "string.h"
#include "base.h"
#include "utf8.h"
#include "os.h"
#include "tmstring.h"
#include "color.h"
#include "clipboard.h"
#include "filesystem.h"
#include "io.h"
#include "complex.h"
#include "quaternion.h"
#include "hash.h"
#include "http.h"

void luaReg(lua_State* L, nlohmann::json o) {
	//base
	luaReg_base(L, getOptionParamB(o, OPTION_VAPI, API_BASE));

	//string
	luaReg_string(L, API_STRING, getOptionParamB(o, OPTION_VAPI, API_STRING));

	//tmstring
	luaReg_tmstring(L, API_TMSTRING, getOptionParamB(o, OPTION_VAPI, API_TMSTRING));

	//os
	luaReg_os(L, API_OS, getOptionParamB(o, OPTION_VAPI, API_OS));

	//utf8
	luaReg_utf8(L, API_UTF8, getOptionParamB(o, OPTION_VAPI, API_UTF8));

	//color
	luaReg_color(L, API_COLOR, getOptionParamB(o, OPTION_VAPI, API_COLOR));

	//clipboard
	luaReg_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI, API_CLIPBOARD));

	//filesystem
	luaReg_filesystem(L, API_FILESYSTEM, getOptionParamB(o, OPTION_VAPI, API_FILESYSTEM));

	//complex
	luaReg_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI, API_COMPLEX));

	//quaternion
	luaReg_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI, API_QUATERNION));

	//hash
	luaReg_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI, API_HASH));

	//hash
	luaReg_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI, API_HTTP));
}

void luaAlias(lua_State* L, nlohmann::json o) {
	luaReg_tmstring(L,
		ALIAS_API_TMSTRING,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_TMSTRING) && getOptionParamB(o, OPTION_VAPI, API_TMSTRING)
	);

	luaReg_filesystem(L,
		ALIAS_API_FILESYSTEM,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_FILESYSTEM) && getOptionParamB(o, OPTION_VAPI, API_FILESYSTEM)
	);
}

void luaGlobal(lua_State* L, nlohmann::json o) {
	luaGlobal_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_CLIPBOARD));
	luaGlobal_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_COMPLEX));
	luaGlobal_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_QUATERNION));
	luaGlobal_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HASH));
	luaGlobal_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HTTP));
}

int luaSetup(lua_State* L) {
	nlohmann::json option = getOption();
	if (getOptionParamB(option, OPTION_VMODULE)) {
		luaReg(L, option);
		luaAlias(L, option);
		luaGlobal(L, option);
	}

	int n = 0;

	if (getOptionParamB(option, OPTION_VVER_CHECK)) {
		n = versionCheck();
		if (n == VERSION_CHECK_ERROR) {
			luaL_error(L, VERSION_CHECK_MSG_ERROR);
			n = 1;
		}
		else if (n == VERSION_CHECK_OUTDATED) {
			luaL_error(L, VERSION_CHECK_MSG_OUTDATED);
		}
	}
	return n;
}

extern "C" {
	__declspec(dllexport) int luaopen_textmodule(lua_State* L) {
		try {
			int n = luaSetup(L);

			

			return 1 + n;
		}
		catch (std::exception& e) {
			luaL_error(L, e.what());
			return 1;
		}
	}
}