#include <lua.hpp>
#include <nlohmann/json.hpp>

#include "textmodule.hpp"
#include "textmodule_lua.hpp"
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
#include "exedit.hpp"

#include "complex.hpp"
#include "quaternion.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix2.hpp"
#include "matrix3.hpp"
#include "matrix4.hpp"

#include "colorlist.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "image.hpp"

void luaReg(lua_State* L, nlohmann::json opt, const char* module) {
	//create base table
	static luaL_Reg none[] = {
		{nullptr, nullptr}
	};
	luaL_register(L, module, none);

	auto api = opt["api"];

	//module
	luaReg_base(L, opt); //base
	luaReg_debug(L, opt); //debug
	luaReg_string(L, opt); //string
	luaReg_os(L, opt); //os
	luaReg_clipboard(L, opt); //clipboard
	luaReg_filesystem(L, opt); //filesystem
	luaReg_hash(L, opt); //hash
	luaReg_http(L, opt); //http
	luaReg_cmath(L, opt); //math
	luaReg_random(L, opt); //random
	luaReg_bit(L, opt); //bit
	luaReg_qrcode(L, opt); //qrcode
	luaReg_obj(L, opt); //obj
	luaReg_ease(L, opt); //ease
	luaReg_device(L, opt); //device
	luaReg_time(L, opt); //time
	luaReg_json(L, opt); //json
	//luaReg_exedit(L, opt); //exedit

	//color
	luaReg_color(L, opt); //color
	luaReg_pixel(L, opt); //pixel
	luaReg_colorlist(L, opt); //colorlist
	//luaReg_image(L, opt); //image

	//geometry
	luaReg_complex(L, opt); //complex
	luaReg_quaternion(L, opt); //quaternion
	luaReg_vector2(L, opt); //vector2
	luaReg_vector3(L, opt); //vector3
	luaReg_vector4(L, opt); //vector4
	luaReg_matrix2(L, opt); //matrix2
	luaReg_matrix3(L, opt); //matrix3
	luaReg_matrix4(L, opt); //matrix4
}


int luaSetup(lua_State* L) {
	nlohmann::json option = getOption();
	
	tm_debuglog(option, "INFO", "adding a directory to the search path used to locate DLLs");
	SetDllPath();

	// Luaインスタンスに変数を登録
	if (option[OPTION_VMODULE]) {
		tm_debuglog(option, "INFO", "start module registration: " MODULE_NAME);
		luaReg(L, option, MODULE_NAME); //main module

		if (option[OPTION_VMODULE_ALIAS]) { // tm alias
			tm_debuglog(option, "INFO", "start module registration: " ALIAS_MODULE_NAME);
			luaReg(L, option, ALIAS_MODULE_NAME);
		}
	}

	// バージョンチェック
	int n = 0;
	if (option[OPTION_VVER_CHECK]) {
		tm_debuglog(option, "INFO", "check the module version");

		int v = versionCheck();
		if (v == VERSION_CHECK_ERROR) {
			tm_debuglog(option, "VERSION_CHECK", "version check: error");
			luaL_error(L, VERSION_CHECK_MSG_ERROR);
			n = 1;
		}
		else if (v == VERSION_CHECK_OUTDATED) {
			tm_debuglog(option, "VERSION_CHECK", "version check: outdated");
			luaL_error(L, VERSION_CHECK_MSG_OUTDATED);
			n = 1;
		}
		else
			tm_debuglog(option, "VERSION_CHECK", "version check: latest");
	}
	return n;
}

extern "C" {
	__declspec(dllexport) int luaopen_textmodule(lua_State* L) {
		try {
			int n = luaSetup(L);

			return 1 + n;
		}
		catch (nlohmann::json::exception& j) {
			std::string what = std::string("invalid json format or value: config.json\n") + std::string(j.what());
			luaL_error(L, what.c_str());
			return 0;
		}
		catch (std::exception& e) {
			luaL_error(L, e.what());
			return 0;
		}
	}
}