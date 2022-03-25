#include <lua.hpp>
#include <nlohmann/json.hpp>

#include "textmodule.h"
#include "textmodule_string.h"
#include "textmodule_option.h"

#include "base.h"
#include "string.h"
#include "debug.h"
#include "utf8.h"
#include "os.h"
#include "tmstring.h"
#include "clipboard.h"
#include "filesystem.h"
#include "hash.h"
#include "http.h"
#include "cmath.h"
#include "random.h"
#include "bit.h"
#include "qrcode.h"

#include "complex.h"
#include "vector2.h"
#include "vector3.h"
#include "quaternion.h"

#include "color.h"
#include "rgb.h"
#include "hsv.h"
#include "hsl.h"

void luaReg(lua_State* L, nlohmann::json o) {
	//base
	luaReg_base(L, getOptionParamB(o, OPTION_VAPI, API_BASE));

	//debug
	luaReg_debug(L, API_DEBUG, true);

	//string
	luaReg_string(L, API_STRING, getOptionParamB(o, OPTION_VAPI, API_STRING));

	//tmstring
	luaReg_tmstring(L, API_TMSTRING, getOptionParamB(o, OPTION_VAPI, API_TMSTRING));

	//os
	luaReg_os(L, API_OS, getOptionParamB(o, OPTION_VAPI, API_OS));

	//utf8
	luaReg_utf8(L, API_UTF8, getOptionParamB(o, OPTION_VAPI, API_UTF8));

	//color
	luaReg_color(L, API_COLOR_BASE, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_COLOR_BASE));
	luaReg_rgb(L, API_RGB, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_RGB));
	luaReg_hsv(L, API_HSV, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_HSV));
	luaReg_hsl(L, API_HSL, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_HSL));

	//geometry
	luaReg_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_COMPLEX));
	luaReg_vector2(L, API_VECTOR2, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_VECTOR2));
	luaReg_vector3(L, API_VECTOR3, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_VECTOR3));
	luaReg_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_QUATERNION));

	//clipboard
	luaReg_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI, API_CLIPBOARD));

	//filesystem
	luaReg_filesystem(L, API_FILESYSTEM, getOptionParamB(o, OPTION_VAPI, API_FILESYSTEM));

	//hash
	luaReg_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI, API_HASH));

	//http
	luaReg_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI, API_HTTP));

	//math
	luaReg_cmath(L, API_CMATH, getOptionParamB(o, OPTION_VAPI, API_CMATH));

	//random
	luaReg_random(L, API_RANDOM, getOptionParamB(o, OPTION_VAPI, API_RANDOM));

	//bit
	luaReg_bit(L, API_BIT, getOptionParamB(o, OPTION_VAPI, API_BIT));

	//qrcode
	luaReg_qrcode(L, API_QRCODE, getOptionParamB(o, OPTION_VAPI, API_QRCODE));
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

	luaReg_random(L,
		ALIAS_API_RANDOM,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_RANDOM) && getOptionParamB(o, OPTION_VAPI, API_RANDOM)
	);
}

void luaGlobal(lua_State* L, nlohmann::json o) {
	luaGlobal_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_CLIPBOARD));
	luaGlobal_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HASH));
	luaGlobal_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HTTP));

	//geometry
	luaGlobal_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_COMPLEX));
	luaGlobal_vector2(L, API_VECTOR2, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_VECTOR2));
	luaGlobal_vector3(L, API_VECTOR3, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_VECTOR3));
	luaGlobal_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_QUATERNION));
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