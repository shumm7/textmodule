#include <lua.hpp>

#include "hsv.h"
#include "rgb.h"
#include "hsl.h"
#include "color.h"
#include "vector3.h"

#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_color.h"
#include "textmodule_exception.h"

std::string get_hsvmsg() {
	std::string t = "number/string/";
	t += TEXTMODULE_HSV;
	t += " expected";
	return t;
}

std::string get_hsvmsg(std::string first) {
	std::string t = first + "/";
	t += TEXTMODULE_HSV;
	t += " expected";
	return t;
}

int hsv_new(lua_State* L) {
	try {
		int tp1 = lua_type(L, 1);
		int tp2 = lua_type(L, 2);
		int tp3 = lua_type(L, 3);

		luaL_argcheck(L, tp1 == LUA_TNUMBER || tp1 == LUA_TUSERDATA, 1, get_hsvmsg("number/").c_str());
		luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE), 2, "number/none expected");
		luaL_argcheck(L, (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) || (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE), 3, "number/none expected");
		
		int h = 0;
		int s = 0;
		int v = 0;

		if (tp1 == LUA_TNUMBER && tp2 == LUA_TNUMBER && tp3 == LUA_TNUMBER) {
			h = tm_tointeger(L, 1);
			s = tm_tointeger(L, 2);
			v = tm_tointeger(L, 3);
		}
		else if (tp1 == LUA_TUSERDATA && tp2 == LUA_TNONE && tp3 == LUA_TNONE) {
			if (luaL_checkmetatable(L, 1, TEXTMODULE_HSV)) {
				HSV* val = hsv_check(L, 1);
				h = val->h;
				s = val->s;
				v = val->v;
			}
			else if (luaL_checkmetatable(L, 1, TEXTMODULE_VECTOR3)) {
				Vector3* val = vector3_check(L, 1);
				h = val->x();
				s = val->y();
				v = val->z();
			}
		}

		HSV* ret = reinterpret_cast<HSV*>(lua_newuserdata(L, sizeof(HSV)));
		luaL_getmetatable(L, TEXTMODULE_HSV);
		lua_setmetatable(L, -2);

		ret->h = check_hsv_hvalue(h);
		ret->s = check_hsv_svvalue(s);
		ret->v = check_hsv_svvalue(v);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv____tostring(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);
		std::wstring ret = L"(" + tostring_n(val->h)
			+ L"," + tostring_n(val->s)
			+ L"," + tostring_n(val->v)
			+ L")";

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv____index(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

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
				lua_pushinteger(L, val->v);
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
			else if (l == "v") {
				lua_pushinteger(L, val->v);
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

int hsv____newindex(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

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
				val->v = value;
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
			else if (l == "v") {
				val->v = value;
			}
			else {
				return 0;
			}
		}

		HSV* ret = reinterpret_cast<HSV*>(lua_newuserdata(L, sizeof(HSV)));
		luaL_getmetatable(L, TEXTMODULE_HSV);
		lua_setmetatable(L, -2);
		ret = val;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv____call(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);
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
			else if (w == "v") {
				lua_pushinteger(L, val->v);
				return 1;
			}
			else if (w == "hsv") {
				lua_pushinteger(L, val->h);
				lua_pushinteger(L, val->s);
				lua_pushinteger(L, val->v);
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

int hsv_h(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

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

int hsv_s(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

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

int hsv_v(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->v = check_hsv_svvalue(tm_tointeger(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushinteger(L, val->v);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv_hsv(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

		lua_pushinteger(L, val->h);
		lua_pushinteger(L, val->s);
		lua_pushinteger(L, val->v);
		return 3;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv_rgb(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);

		RGB* ret = reinterpret_cast<RGB*>(lua_newuserdata(L, sizeof(RGB)));
		luaL_getmetatable(L, TEXTMODULE_RGB);
		lua_setmetatable(L, -2);

		HSVtoRGB(val, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hsv_hsl(lua_State* L) {
	try {
		HSV* val = hsv_check(L, 1);
		RGB* c = new RGB;

		HSL* ret = reinterpret_cast<HSL*>(lua_newuserdata(L, sizeof(HSL)));
		luaL_getmetatable(L, TEXTMODULE_HSL);
		lua_setmetatable(L, -2);

		HSVtoRGB(val, c);
		RGBtoHSL(c, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_hsv(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//hsv
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HSV_REG);
		lua_setfield(L, -2, name);

		//hsv (metatable)
		luaL_newmetatable(L, TEXTMODULE_HSV); //add metatable
		luaL_register(L, NULL, TEXTMODULE_HSV_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HSV_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}