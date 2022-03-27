#include <lua.hpp>

#include "hsl.h"
#include "rgb.h"
#include "hsv.h"
#include "color.h"

#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_color.h"
#include "textmodule_exception.h"
#include "textmodule_geometry.h"

std::string get_hslmsg() {
	std::string t = "number/string/";
	t += TEXTMODULE_HSL;
	t += " expected";
	return t;
}

std::string get_hslmsg(std::string first) {
	std::string t = first + "/";
	t += TEXTMODULE_HSL;
	t += " expected";
	return t;
}

int hsl_new(lua_State* L) {
	try {
		int tp1 = lua_type(L, 1);
		int tp2 = lua_type(L, 2);
		int tp3 = lua_type(L, 3);

		luaL_argcheck(L, tp1 == LUA_TNUMBER || tp1 == LUA_TUSERDATA, 1, get_hslmsg("number/").c_str());
		luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE), 2, "number/none expected");
		luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE), 3, "number/none expected");

		int h = 0;
		int s = 0;
		int l = 0;

		if (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) {
			h = tm_tointeger(L, 1);
			s = tm_tointeger(L, 2);
			l = tm_tointeger(L, 3);
		}
		else if (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE) {
			if (luaL_checkmetatable(L, 1, TEXTMODULE_HSL)) {
				HSL* val = hsl_check(L, 1);
				h = val->h;
				s = val->s;
				l = val->l;
			}
			else if (luaL_checkmetatable(L, 1, TEXTMODULE_VECTOR3)) {
				Vector3* val = vector3_check(L, 1);
				h = val->x();
				s = val->y();
				l = val->z();
			}
		}

		HSL* ret = reinterpret_cast<HSL*>(lua_newuserdata(L, sizeof(HSL)));
		luaL_getmetatable(L, TEXTMODULE_HSL);
		lua_setmetatable(L, -2);

		ret->h = check_hsv_hvalue(h);
		ret->s = check_hsv_svvalue(s);
		ret->l = check_hsv_svvalue(l);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl____tostring(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);
		std::wstring ret = L"(" + tostring_n(val->h)
			+ L"," + tostring_n(val->s)
			+ L"," + tostring_n(val->l)
			+ L")";

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl____index(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				lua_pushinteger(L, val->h);
				return 1;
			case 2:
				lua_pushinteger(L, val->s);
				return 1;
			case 3:
				lua_pushinteger(L, val->l);
				return 1;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "h") {
				lua_pushinteger(L, val->h);
				return 1;
			}
			else if (l == "s") {
				lua_pushinteger(L, val->s);
				return 1;
			}
			else if (l == "l") {
				lua_pushinteger(L, val->l);
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

int hsl____newindex(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		int value = tm_tointeger(L, 3);

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				val->h = value;
				break;
			case 2:
				val->s = value;
				break;
			case 3:
				val->l = value;
				break;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "h") {
				val->h = value;
			}
			else if (l == "s") {
				val->s = value;
			}
			else if (l == "l") {
				val->l = value;
			}
			else {
				return 0;
			}
		}

		HSL* ret = reinterpret_cast<HSL*>(lua_newuserdata(L, sizeof(HSL)));
		luaL_getmetatable(L, TEXTMODULE_HSL);
		lua_setmetatable(L, -2);
		ret = val;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl____call(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);
		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, 2, "string/none expected");

		if (tp == LUA_TNONE) {

		}
		else if (tp == LUA_TSTRING) {
			std::string w = tm_tostring(L, 1);

			if (w == "h") {
				lua_pushinteger(L, val->h);
				return 1;
			}
			else if (w == "s") {
				lua_pushinteger(L, val->s);
				return 1;
			}
			else if (w == "l") {
				lua_pushinteger(L, val->l);
				return 1;
			}
			else if (w == "hsl") {
				lua_pushinteger(L, val->h);
				lua_pushinteger(L, val->s);
				lua_pushinteger(L, val->l);
				return 3;
			}
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_h(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->h = check_hsv_hvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->h);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_s(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->s = check_hsv_svvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->s);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_l(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->l = check_hsv_svvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->l);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_hsl(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		lua_pushinteger(L, val->h);
		lua_pushinteger(L, val->s);
		lua_pushinteger(L, val->l);
		return 3;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_rgb(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		HSLtoRGB(val, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsl_hsv(lua_State* L) {
	try {
		HSL* val = hsl_check(L, 1);
		RGB* c = new RGB;

		HSV* ret = reinterpret_cast<HSV*>(lua_newuserdata(L, sizeof(HSV)));
		luaL_getmetatable(L, TEXTMODULE_HSV);
		lua_setmetatable(L, -2);

		HSLtoRGB(val, c);
		RGBtoHSV(c, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_hsl(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//hsv
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HSL_REG);
		lua_setfield(L, -2, name);

		//hsv (metatable)
		luaL_newmetatable(L, TEXTMODULE_HSL); //add metatable
		luaL_register(L, NULL, TEXTMODULE_HSL_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HSL_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}