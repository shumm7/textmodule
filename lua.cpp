#include <lua.hpp>
#include <nlohmann/json.hpp>

#include "textmodule.hpp"
#include "textmodule_string.hpp"
#include "textmodule_option.hpp"

#include "base.hpp"
#include "string.hpp"
#include "debug.hpp"
#include "os.hpp"
#include "tmstring.hpp"
#include "clipboard.hpp"
#include "filesystem.hpp"
#include "hash.hpp"
#include "http.hpp"
#include "cmath.hpp"
#include "random.hpp"
#include "bit.hpp"
#include "qrcode.hpp"
#include "obj.hpp"
#include "ease.hpp"
#include "device.hpp"
#include "time.hpp"
#include "json.hpp"
#include "u8.hpp"

#include "complex.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "quaternion.hpp"

#include "colorlist.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "image.hpp"

void luaAlias(lua_State* L, nlohmann::json o) {
	luaReg_filesystem(L,
		ALIAS_API_FILESYSTEM,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_FILESYSTEM) && getOptionParamB(o, OPTION_VAPI, API_FILESYSTEM)
	);

	luaReg_random(L,
		ALIAS_API_RANDOM,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_RANDOM) && getOptionParamB(o, OPTION_VAPI, API_RANDOM)
	);

	luaReg_obj(L,
		ALIAS_API_OBJ,
		getOptionParamB(o, OPTION_VAPI_ALIAS, API_OBJ) && getOptionParamB(o, OPTION_VAPI, API_OBJ)
	);
}

void luaReg(lua_State* L, nlohmann::json o, const char* module) {
	//create base table
	static luaL_Reg none[] = {
		{nullptr, nullptr}
	};
	luaL_register(L, module, none);

	//module
	luaReg_base(L, getOptionParamB(o, OPTION_VAPI, API_BASE)); //base
	luaReg_debug(L, API_DEBUG, true); //debug
	luaReg_string(L, API_STRING, getOptionParamB(o, OPTION_VAPI, API_STRING)); //string
	luaReg_os(L, API_OS, getOptionParamB(o, OPTION_VAPI, API_OS)); //os
	luaReg_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI, API_CLIPBOARD)); //clipboard
	luaReg_filesystem(L, API_FILESYSTEM, getOptionParamB(o, OPTION_VAPI, API_FILESYSTEM)); //filesystem
	luaReg_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI, API_HASH)); //hash
	luaReg_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI, API_HTTP)); //http
	luaReg_cmath(L, API_CMATH, getOptionParamB(o, OPTION_VAPI, API_CMATH)); //math
	luaReg_random(L, API_RANDOM, getOptionParamB(o, OPTION_VAPI, API_RANDOM)); //random
	luaReg_bit(L, API_BIT, getOptionParamB(o, OPTION_VAPI, API_BIT)); //bit
	luaReg_qrcode(L, API_QRCODE, getOptionParamB(o, OPTION_VAPI, API_QRCODE)); //qrcode
	luaReg_obj(L, API_OBJ, getOptionParamB(o, OPTION_VAPI, API_OBJ)); //obj
	luaReg_ease(L, API_EASE, getOptionParamB(o, OPTION_VAPI, API_EASE)); //ease
	luaReg_device(L, API_DEVICE, getOptionParamB(o, OPTION_VAPI, API_DEVICE)); //device
	luaReg_time(L, API_TIME, getOptionParamB(o, OPTION_VAPI, API_TIME)); //time
	luaReg_json(L, API_JSON, getOptionParamB(o, OPTION_VAPI, API_JSON)); //json
	luaReg_u8(L, API_UTF8, getOptionParamB(o, OPTION_VAPI, API_UTF8));

	//color
	luaReg_color(L, API_COLOR, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_COLOR)); //color
	luaReg_pixel(L, API_PIXEL, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_PIXEL)); //pixel
	//luaReg_image(L, API_IMAGE, getOptionParamB(o, OPTION_VAPI, API_COLOR, API_IMAGE)); //image

	//geometry
	luaReg_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_COMPLEX)); //complex
	luaReg_vector2(L, API_VECTOR2, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_VECTOR2)); //vector2
	luaReg_vector3(L, API_VECTOR3, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_VECTOR3)); //vector3
	luaReg_vector4(L, API_VECTOR4, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_VECTOR4)); //vector4
	luaReg_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI, API_GEOMETRY, API_QUATERNION)); //quaternion

	// alias
	luaAlias(L, o);
}

void luaGlobal(lua_State* L, nlohmann::json o) {
	luaGlobal_clipboard(L, API_CLIPBOARD, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_CLIPBOARD));
	luaGlobal_hash(L, API_HASH, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HASH));
	luaGlobal_http(L, API_HTTP, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_HTTP));
	luaGlobal_json(L, API_JSON, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_JSON));

	//geometry
	luaGlobal_complex(L, API_COMPLEX, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_COMPLEX));
	luaGlobal_vector2(L, API_VECTOR2, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_VECTOR2));
	luaGlobal_vector3(L, API_VECTOR3, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_VECTOR3));
	luaGlobal_vector3(L, API_VECTOR4, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_VECTOR4));
	luaGlobal_quaternion(L, API_QUATERNION, getOptionParamB(o, OPTION_VAPI_GLOBAL, API_GEOMETRY, API_QUATERNION));
}


int luaSetup(lua_State* L) {
	nlohmann::json option = getOption();

	// Luaインスタンスに変数を登録
	if (getOptionParamB(option, OPTION_VMODULE)) {
		luaReg(L, option, MODULE_NAME); //main module

		if(getOptionParamB(option, OPTION_VMODULE_ALIAS)) // tm alias
			luaReg(L, option, ALIAS_MODULE_NAME);

		luaGlobal(L, option); //global
	}

	// バージョンチェック
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
			SetDllPath();

			return 1 + n;
		}
		catch (std::exception& e) {
			luaL_error(L, e.what());
			return 1;
		}
	}
}