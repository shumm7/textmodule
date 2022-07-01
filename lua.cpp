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

void luaReg(lua_State* L, nlohmann::json o, const char* module) {
	//create base table
	static luaL_Reg none[] = {
		{nullptr, nullptr}
	};
	luaL_register(L, module, none);
	
	nlohmann::json api = o["api"];

	//module
	luaReg_base(L, api["base"]); //base
	luaReg_debug(L, "debug", true); //debug
	luaReg_string(L, "string", api["string"]); //string
	luaReg_os(L, "os", api["os"]); //os
	luaReg_clipboard(L, "clipboard", api["clipboard"]); //clipboard
	luaReg_filesystem(L, "filesystem", api["filesystem"]); //filesystem
	luaReg_hash(L, "hash", api["hash"]); //hash
	luaReg_http(L, "http", api["http"]); //http
	luaReg_cmath(L, "math", api["math"]); //math
	luaReg_random(L, "random", api["random"]); //random
	luaReg_bit(L, "bit", api["bit"]); //bit
	luaReg_qrcode(L, "qrcode", api["qrcode"]); //qrcode
	luaReg_obj(L, "object", api["object"]); //obj
	luaReg_ease(L, "ease", api["ease"]); //ease
	luaReg_device(L, "device", api["device"]); //device
	luaReg_time(L, "time", api["time"]); //time
	luaReg_json(L, "json", api["json"]); //json

	//color
	luaReg_color(L, "color", api["color"]["color"]); //color
	luaReg_colorlist(L, "colorlist", api["color"]["colorlist"]); //colorlist
	luaReg_pixel(L, "pixel", api["color"]["pixel"]); //pixel
	//luaReg_image(L, "image", api["color"]["image"]); //image

	//geometry
	luaReg_complex(L, "complex", api["geometry"]["complex"]); //complex
	luaReg_quaternion(L, "quaternion", api["geometry"]["quaternion"]); //quaternion
	luaReg_vector2(L, "vector2", api["geometry"]["vector2"]); //vector2
	luaReg_vector3(L, "vector3", api["geometry"]["vector3"]); //vector3
	luaReg_vector4(L, "vector4", api["geometry"]["vector4"]); //vector4
	luaReg_matrix2(L, "matrix2", api["geometry"]["matrix2"]); //matrix2
	luaReg_matrix3(L, "matrix3", api["geometry"]["matrix3"]); //matrix3
	luaReg_matrix4(L, "matrix4", api["geometry"]["matrix4"]); //matrix4
}


int luaSetup(lua_State* L) {
	nlohmann::json option = getOption();

	// Luaインスタンスに変数を登録
	if (option[OPTION_VMODULE]) {
		luaReg(L, option, MODULE_NAME); //main module

		if(option[OPTION_VMODULE_ALIAS]) // tm alias
			luaReg(L, option, ALIAS_MODULE_NAME);
	}

	// バージョンチェック
	int n = 0;
	if (option[OPTION_VVER_CHECK]) {
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
		catch (nlohmann::json::exception& j) {
			luaL_error(L, "invalid json format or value: config.json");
			return 0;
		}
		catch (std::exception& e) {
			luaL_error(L, e.what());
			return 0;
		}
	}
}