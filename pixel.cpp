#include "pixel.hpp"

#include <lua.hpp>
#include <iostream>

#include "textmodule.hpp"
#include "textmodule_math.hpp"
#include "textmodule_string.hpp"
#include "textmodule_color.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"

int pixel_new(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER || tp == LUA_TUSERDATA || tp == LUA_TNONE, 1, "string/number/vector3/vector4/none expected");
		lua_Pixel c;

		if (tp == LUA_TSTRING) {
			c_hex_to_pixel(&c, tm_towstring(L, 1));
			lua_pushpixel(L, c);
			return 1;
		}
		else if (tp == LUA_TNUMBER) {
			switch (lua_gettop(L)) {
			case 1:
			case 2:
				c_hex_to_pixel(&c, tm_tointeger(L, 1), tm_tointeger_s(L, 2, 0));
				lua_pushpixel(L, c);
				return 1;
			default:
				lua_pushpixel(L, tm_tonumber_s(L, 1), tm_tonumber_s(L, 2), tm_tonumber_s(L, 3), tm_tonumber_s(L, 4));
				return 1;
			}
		}
		else if (tp == LUA_TUSERDATA) {
			if (luaL_checkmetatable(L, 1, TEXTMODULE_VECTOR4)) {
				lua_Vector4* v4 = tm_tovector4(L, 1);
				lua_pushpixel(L, v4->x(), v4->y(), v4->z(), v4->w());
				return 1;
			}
		}
		else {
			lua_pushcolor(L);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int pixel____tostring(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);
		lua_Wstring ret = L"(" + tostring_n(val->r)
			+ L"," + tostring_n(val->g)
			+ L"," + tostring_n(val->b)
			+ L"," + tostring_n(val->a)
			+ L")";

		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____add(lua_State* L) {
	try {
		lua_Pixel* val1 = tm_topixel(L, 1);
		lua_Pixel* val2 = tm_topixel(L, 2);

		lua_pushpixel(L,
			(double)val1->r + (double)val2->r,
			(double)val1->g + (double)val2->g,
			(double)val1->b + (double)val2->b,
			(double)val1->a + (double)val2->a
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____sub(lua_State* L) {
	try {
		lua_Pixel* val1 = tm_topixel(L, 1);
		lua_Pixel* val2 = tm_topixel(L, 2);

		lua_pushpixel(L,
			(double)val1->r - (double)val2->r,
			(double)val1->g - (double)val2->g,
			(double)val1->b - (double)val2->b,
			(double)val1->a - (double)val2->a
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____mul(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA, 1, "number/color expected");

		if (tp == LUA_TUSERDATA) {
			lua_Pixel* val1 = tm_topixel(L, 1);
			if (lua_type(L, 2) == LUA_TNUMBER) {
				lua_Number val2 = tm_tonumber(L, 2);

				lua_pushpixel(L,
					val2 * (double)val1->r,
					val2 * (double)val1->g,
					val2 * (double)val1->b,
					val2 * (double)val1->a
				);
				return 1;
			}
			else {
				lua_Pixel* val2 = tm_topixel(L, 2);
				lua_pushpixel(L,
					(double)val1->r * (double)val2->r,
					(double)val1->g * (double)val2->g,
					(double)val1->b * (double)val2->b,
					(double)val1->a * (double)val2->a
				);
				return 1;
			}
		}
		else if (tp == LUA_TNUMBER) {
			lua_Number val1 = tm_tonumber(L, 1);
			lua_Pixel* val2 = tm_topixel(L, 2);

			lua_pushpixel(L,
				val1 * (double)val2->r,
				val1 * (double)val2->g,
				val1 * (double)val2->b,
				val1 * (double)val2->a
			);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____div(lua_State* L) {
	try {
		lua_Pixel* val1 = tm_topixel(L, 1);
		lua_Number val2 = tm_tonumber(L, 2);

		lua_pushpixel(L,
			(double)val1->r / val2,
			(double)val1->g / val2,
			(double)val1->b / val2,
			(double)val1->a / val2
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____lt(lua_State* L) {
	try {
		lua_pushboolean(L, c_pixel_norm(tm_topixel(L, 1)) < c_pixel_norm(tm_topixel(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____le(lua_State* L) {
	try {
		lua_pushboolean(L, c_pixel_norm(tm_topixel(L, 1)) <= c_pixel_norm(tm_topixel(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____index(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				lua_pushnumber(L, val->r);
				return 1;
			case 2:
				lua_pushnumber(L, val->g);
				return 1;
			case 3:
				lua_pushnumber(L, val->b);
				return 1;
			case 4:
				lua_pushnumber(L, val->a);
				return 1;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "r") {
				lua_pushnumber(L, val->r);
				return 1;
			}
			else if (l == "g") {
				lua_pushnumber(L, val->g);
				return 1;
			}
			else if (l == "b") {
				lua_pushnumber(L, val->b);
				return 1;
			}
			else if (l == "a") {
				lua_pushnumber(L, val->a);
				return 1;
			}
			else
				return 0;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel____newindex(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		lua_Number value = tm_tonumber(L, 3);

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
			case 4:
				val->a = value;
				break;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "r") {
				val->r = value;
			}
			else if (l == "g") {
				val->g = value;
			}
			else if (l == "b") {
				val->b = value;
			}
			else if (l == "a") {
				val->a = value;
			}
			else
				return 0;
		}

		lua_pushpixel(L, *val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int pixel_r(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->r = clamp_s(tm_tonumber(L, 2), 0, 255);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->r);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel_g(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->g = clamp_s(tm_tonumber(L, 2), 0, 255);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->g);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel_b(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->b = clamp_s(tm_tonumber(L, 2), 0, 255);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->b);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel_a(lua_State* L) {
	try {
		lua_Pixel* val = tm_topixel(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->a = clamp_s(tm_tonumber(L, 2), 0, 255);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->a);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int pixel_color(lua_State* L) {
	lua_Pixel* val1 = tm_topixel(L, 1);
	lua_Color* ret = lua_pushcolor(L);
	c_pixel_to_color(ret, val1);
	return 1;
}

void luaReg_pixel(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//pixel
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_PIXEL_REG);
		lua_setfield(L, -2, name);

		//pixel (metatable)
		luaL_newmetatable(L, TEXTMODULE_PIXEL); //add metatable
		luaL_register(L, NULL, TEXTMODULE_PIXEL_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_PIXEL_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}
