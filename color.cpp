#include "color.hpp"

#include <lua.hpp>
#include <iostream>
#include <algorithm>

#include "colorlist.hpp"
#include "textmodule_math.hpp"
#include "textmodule_color.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

#define NOMINMAX

int color_new(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA || tp == LUA_TNONE, 1, "number/vector4/none expected");

		lua_Number r;
		lua_Number g;
		lua_Number b;
		lua_Number a;

		if (tp == LUA_TNUMBER || tp == LUA_TNONE) {
			r = tm_tonumber_s(L, 1, 0);
			g = tm_tonumber_s(L, 2, 0);
			b = tm_tonumber_s(L, 3, 0);
			a = tm_tonumber_s(L, 4, 0);
		}
		else if (tp == LUA_TUSERDATA) {
			lua_Vector4* v = tm_tovector4(L, 1);
			r = v->x();
			g = v->y();
			b = v->z();
			a = v->w();
		}
		else
			return 0;

		lua_pushcolor(L, r, g, b, a);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int color____tostring(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);
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

int color____add(lua_State* L) {
	try {
		lua_Color* val1 = tm_tocolor(L, 1);
		lua_Color* val2 = tm_tocolor(L, 2);

		lua_pushcolor(L,
			val1->r + val2->r,
			val1->g + val2->g,
			val1->b + val2->b,
			val1->a + val2->a
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____sub(lua_State* L) {
	try {
		lua_Color* val1 = tm_tocolor(L, 1);
		lua_Color* val2 = tm_tocolor(L, 2);

		lua_pushcolor(L,
			val1->r - val2->r,
			val1->g - val2->g,
			val1->b - val2->b,
			val1->a - val2->a
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____mul(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA, 1, "number/color expected");

		if (tp == LUA_TUSERDATA) {
			lua_Color* val1 = tm_tocolor(L, 1);
			if (lua_type(L, 2) == LUA_TNUMBER) {
				lua_Number val2 = tm_tonumber(L, 2);

				lua_pushcolor(L,
					val2 * val1->r,
					val2 * val1->g,
					val2 * val1->b,
					val2 * val1->a
				);
				return 1;
			}
			else {
				lua_Color* val2 = tm_tocolor(L, 2);
				lua_pushcolor(L,
					val1->r * val2->r,
					val1->g * val2->g,
					val1->b * val2->b,
					val1->a * val2->a
				);
				return 1;
			}
		}
		else if (tp == LUA_TNUMBER) {
			lua_Number val1 = tm_tonumber(L, 1);
			lua_Color* val2 = tm_tocolor(L, 2);

			lua_pushcolor(L,
				val1 * val2->r,
				val1 * val2->g,
				val1 * val2->b,
				val1 * val2->a
			);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____div(lua_State* L) {
	try {
		lua_Color* val1 = tm_tocolor(L, 1);
		lua_Number val2 = tm_tonumber(L, 2);

		lua_pushcolor(L,
			val1->r / val2,
			val1->g / val2,
			val1->b / val2,
			val1->a / val2
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____lt(lua_State* L) {
	try {
		lua_pushboolean(L, c_color_norm(tm_tocolor(L, 1)) < c_color_norm(tm_tocolor(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____le(lua_State* L) {
	try {
		lua_pushboolean(L, c_color_norm(tm_tocolor(L, 1)) <= c_color_norm(tm_tocolor(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____index(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

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

int color____newindex(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

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

		lua_pushcolor(L, *val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color____type(lua_State* L) {
	try {
		lua_pushstring(L, "color");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int color_r(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->r = tm_tonumber(L, 2);
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

int color_g(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->g = tm_tonumber(L, 2);
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

int color_b(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->b = tm_tonumber(L, 2);
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

int color_a(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TNONE, 2, "number/none expexted");

		if (tp == LUA_TNUMBER) {
			val->a = tm_tonumber(L, 2);
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


int color_opposite(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);
		lua_pushcolor(L, 1 - val->r, 1 - val->g, 1 - val->b, val->a);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_comp(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);

		double max = (std::max)({ val->r, val->g, val->b });
		double min = (std::min)({ val->r, val->g, val->b });

		lua_pushcolor(L, (max + min) - (val->r), (max + min) - (val->g), (max + min) - (val->b), val->a);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_average(lua_State* L) {
	try {
		lua_Color* val1 = tm_tocolor(L, 1);
		lua_Color* val2 = tm_tocolor(L, 2);

		lua_pushcolor(L,
			(val1->r + val2->r) / 2.0,
			(val1->g + val2->g) / 2.0,
			(val1->b + val2->b) / 2.0,
			(val1->a + val2->a) / 2.0
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_max(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);
		lua_pushnumber(L, (std::max)({ val->r, val->g, val->b }));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_min(lua_State* L) {
	try {
		lua_Color* val = tm_tocolor(L, 1);
		lua_pushnumber(L, (std::min)({ val->r, val->g, val->b }));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_clamp(lua_State* L) {
	try {
		lua_Color* val1 = tm_tocolor(L, 1);
		lua_Color* ret = lua_pushcolor(L);
		c_clamp_color(ret, val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int color_pixel(lua_State* L) {
	lua_Color* val1 = tm_tocolor(L, 1);
	lua_Pixel* ret = lua_pushpixel(L);
	c_color_to_pixel(ret, val1);
	return 1;
}


static luaL_Reg TEXTMODULE_COLOR_REG[] = {
	{"new", color_new},

	{"r", color_r},
	{"g", color_g},
	{"b", color_b},
	{"a", color_a},

	{"opposite", color_opposite},
	{"comp", color_comp},
	{"average", color_average},
	{"max", color_max},
	{"min", color_min},
	{"clamp", color_clamp},
	{"pixel", color_pixel},
	{nullptr, nullptr}
};

static luaL_Reg TEXTMODULE_COLOR_META_REG[] = {
	{"__tostring", color____tostring},
	{"__add", color____add},
	{"__sub", color____sub},
	{"__mul", color____mul},
	{"__div", color____div},
	{"__lt", color____lt},
	{"__le", color____le},
	{"__index", color____index},
	{"__newindex", color____newindex},
	{"__type", color____type},

	{"r", color_r},
	{"g", color_g},
	{"b", color_b},
	{"a", color_a},

	{"opposite", color_opposite},
	{"comp", color_comp},
	{"average", color_average},
	{"max", color_max},
	{"min", color_min},
	{"clamp", color_clamp},
	{"pixel", color_pixel},

	{nullptr, nullptr}
};

void luaReg_color(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_COLOR, TEXTMODULE_COLOR_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COLOR_REG);
		lua_setfield(L, -2, name);
	}
}
