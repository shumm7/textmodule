#include <lua.hpp>
#include <algorithm>

#include "rgb.h"
#include "hsv.h"
#include "hsl.h"
#include "color.h"

#include "vector3.h"

#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_color.h"
#include "textmodule_exception.h"

std::string get_rgbmsg() {
	std::string t = "number/string/";
	t += TEXTMODULE_RGB;
	t += " expected";
	return t;
}

std::string get_rgbmsg(std::string first) {
	std::string t = first + "/";
	t += TEXTMODULE_RGB;
	t += " expected";
	return t;
}

void get_value(lua_State* L, RGB* col, int idx) {
	int r = 0;
	int g = 0;
	int b = 0;

	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNUMBER || LUA_TSTRING || LUA_TUSERDATA, idx, get_rgbmsg().c_str());

	if (tp == LUA_TNUMBER) {
		int val = tm_tointeger(L, idx);
		RGB ret;
		getRGBhex(val, &ret);
		r = ret.r;
		g = ret.g;
		b = ret.b;
	}
	else if (tp == LUA_TSTRING) {
		int val = HexToDec(tm_towstring(L, idx));
		RGB ret;
		getRGBhex(val, &ret);
		r = ret.r;
		g = ret.g;
		b = ret.b;
	}
	else if (tp == LUA_TUSERDATA) {
		if (luaL_checkmetatable(L, idx, TEXTMODULE_RGB)) {
			RGB* val = rgb_check(L, idx);
			r = val->r;
			g = val->g;
			b = val->b;
		}
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR3)) {
			Vector3* val = vector3_check(L, idx);
			r = val->x();
			g = val->y();
			b = val->z();
		}
	}
	col->r = check_rgbvalue(r);
	col->g = check_rgbvalue(g);
	col->b = check_rgbvalue(b);

	return;
}

void get_tvalue(lua_State* L, int idx, RGB* ret) {
	int tp1 = lua_type(L, idx + 0);
	int tp2 = lua_type(L, idx + 1);
	int tp3 = lua_type(L, idx + 2);

	luaL_argcheck(L, tp1 == LUA_TNUMBER || tp1 == LUA_TSTRING || tp1 == LUA_TUSERDATA, idx+0, get_rgbmsg("number/string").c_str());
	luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER) || (tp1 == LUA_TSTRING && tp2 == LUA_TNONE) || (tp1 == LUA_TNUMBER && tp2 == LUA_TNONE) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE), idx+1, "number/none expected");
	luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) || (tp1 == LUA_TSTRING && tp2 == LUA_TNONE && tp3 == LUA_TNONE) || (tp1 == LUA_TNUMBER && tp2 == LUA_TNONE && tp3 == LUA_TNONE) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE), idx+2, "number/none expected");

	if (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) {
		ret->r = tm_tonumber(L, 1);
		ret->g = tm_tonumber(L, 2);
		ret->b = tm_tonumber(L, 3);
	}
	else if (tp1 == LUA_TSTRING && tp2 == LUA_TNONE && tp3 == LUA_TNONE) {
		int val = HexToDec(tm_towstring(L, 1));
		getRGBhex(val, ret);
	}
	else if (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE) {
		if (luaL_checkmetatable(L, idx, TEXTMODULE_RGB)) {
			RGB* val = rgb_check(L, idx);
			ret->r = val->r;
			ret->g = val->g;
			ret->b = val->b;
		}
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR3)) {
			Vector3* val = vector3_check(L, idx);
			ret->r = val->x();
			ret->g = val->y();
			ret->b = val->z();
		}
	}
	else if (tp1 == LUA_TNUMBER && tp2 == LUA_TNONE && tp3 == LUA_TNONE) {
		int val = tm_tointeger(L, 1);
		getRGBhex(val, ret);
	}
}


int rgb_new(lua_State* L) {
	try {
		RGB* val = new RGB;
		get_tvalue(L, 1, val);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = check_rgbvalue(val->r);
		ret->g = check_rgbvalue(val->g);
		ret->b = check_rgbvalue(val->b);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_comp(lua_State* L) {
	try {
		RGB* val = new RGB;
		get_tvalue(L, 1, val);

		int max = std::max({ val->r, val->g, val->b });
		int min = std::min({ val->r, val->g, val->b });

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = check_rgbvalue((max+min) - (val->r));
		ret->g = check_rgbvalue((max + min) - (val->g));
		ret->b = check_rgbvalue((max + min) - (val->b));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_opposite(lua_State* L) {
	try {
		RGB* val = new RGB;
		get_tvalue(L, 1, val);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = check_rgbvalue(255 - (val->r));
		ret->g = check_rgbvalue(255 - (val->g));
		ret->b = check_rgbvalue(255 - (val->b));

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____tostring(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);
		std::wstring ret = L"(" + tostring_n(val->r)
			+ L"," + tostring_n(val->g)
			+ L"," + tostring_n(val->b)
		+ L")";

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____add(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = range(val1.r + val2.r, 0, 255);
		ret->g = range(val1.g + val2.g, 0, 255);
		ret->b = range(val1.b + val2.b, 0, 255);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____sub(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = range(val1.r - val2.r, 0, 255);
		ret->g = range(val1.g - val2.g, 0, 255);
		ret->b = range(val1.b - val2.b, 0, 255);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____mul(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = range(val1.r * val2.r / 255, 0, 255);
		ret->g = range(val1.g * val2.g / 255, 0, 255);
		ret->b = range(val1.b * val2.b / 255, 0, 255);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____lt(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		lua_pushboolean(L, HexToDec(getRGBhex(&val1)) < HexToDec(getRGBhex(&val2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____le(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		lua_pushboolean(L, HexToDec(getRGBhex(&val1)) <= HexToDec(getRGBhex(&val2)));
		return 1;	
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____index(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				lua_pushinteger(L, val->r);
				return 1;
			case 2:
				lua_pushinteger(L, val->g);
				return 1;
			case 3:
				lua_pushinteger(L, val->b);
				return 1;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "r") {
				lua_pushinteger(L, val->r);
				return 1;
			}
			else if (l == "g") {
				lua_pushinteger(L, val->g);
				return 1;
			}
			else if (l == "b") {
				lua_pushinteger(L, val->b);
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____newindex(lua_State* L) {
	try {
		auto val = rgb_check(L,1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		int value = tm_tointeger(L, 3);

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				val->r = value;
				break;
			case 2:
				val->g = value;
				break;
			case 3:
				val->b = value;
				break;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "r") {
				val->r = value;
			}
			else if (l == "g") {
				val->g = value;
			}
			else if (l == "b") {
				val->b = value;
			}
			else {
				return 0;
			}
		}

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);
		ret = val;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb____call(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);
		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, 2, "string/none expected");

		if (tp == LUA_TNONE) {

		}
		else if (tp == LUA_TSTRING) {
			std::string w = tm_tostring(L, 1);

			if (w == "r") {
				lua_pushinteger(L, val->r);
				return 1;
			}
			else if (w == "g") {
				lua_pushinteger(L, val->g);
				return 1;
			}
			else if (w == "b") {
				lua_pushinteger(L, val->b);
				return 1;
			}
			else if (w == "rgb") {
				lua_pushinteger(L, val->r);
				lua_pushinteger(L, val->g);
				lua_pushinteger(L, val->b);
				return 3;
			}
			else if (w == "number"){
				lua_pushinteger(L, HexToDec(getRGBhex(val)));
				return 1;
			}
			else if (w == "hex") {
				lua_pushwstring(L, getRGBhex(val));
				return 1;
			}
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_r(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->r = check_rgbvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->r);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_g(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->g = check_rgbvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->g);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_b(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->b = check_rgbvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->b);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_rgb(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		lua_pushinteger(L, val->r);
		lua_pushinteger(L, val->g);
		lua_pushinteger(L, val->b);
		return 3;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_hex(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);
		lua_pushwstring(L, getRGBhex(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_number(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);
		lua_pushinteger(L, HexToDec(getRGBhex(val)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_hsv(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		HSV* ret = reinterpret_cast<HSV*>(lua_newuserdata(L, sizeof(HSV)));
		luaL_getmetatable(L, TEXTMODULE_HSV);
		lua_setmetatable(L, -2);

		RGBtoHSV(val, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_hsl(lua_State* L) {
	try {
		RGB* val = rgb_check(L, 1);

		HSL* ret = reinterpret_cast<HSL*>(lua_newuserdata(L, sizeof(HSL)));
		luaL_getmetatable(L, TEXTMODULE_HSL);
		lua_setmetatable(L, -2);

		RGBtoHSL(val, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int rgb_average(lua_State* L) {
	try {
		RGB val1;
		RGB val2;
		get_value(L, &val1, 1);
		get_value(L, &val2, 2);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		ret->r = check_rgbvalue((val1.r + val2.r) / 2);
		ret->g = check_rgbvalue((val1.g + val2.g) / 2);
		ret->b = check_rgbvalue((val1.b + val2.b) / 2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_rgb(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//rgb
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_RGB_REG);
		lua_setfield(L, -2, name);

		//rgb (metatable)
		luaL_newmetatable(L, TEXTMODULE_RGB); //add metatable
		luaL_register(L, NULL, TEXTMODULE_RGB_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_RGB_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}