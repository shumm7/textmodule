#include "vector2.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"

int vector2_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__vector2"))
			return 1;

		lua_Number x = tm_tonumber_s(L, 1, 0);
		lua_Number y = tm_tonumber_s(L, 2, 0);

		lua_pushvector2(L, x, y);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_identity(lua_State* L) {
	try {
		lua_pushvector2(L, lua_Vector2::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_down(lua_State* L) {
	try {
		lua_pushvector2(L, 0, -1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_left(lua_State* L) {
	try {
		lua_pushvector2(L, -1, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_one(lua_State* L) {
	try {
		lua_pushvector2(L, 1, 1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_right(lua_State* L) {
	try {
		lua_pushvector2(L, 1, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_up(lua_State* L) {
	try {
		lua_pushvector2(L, 0, 1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2_zero(lua_State* L) {
	try {
		lua_pushvector2(L, 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int vector2__x(lua_State* L) {
	try {
		lua_Vector2* val = tm_tovector2(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->x() = lua_tonumber(L, 2);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->x());
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__y(lua_State* L) {
	try {
		lua_Vector2* val = tm_tovector2(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->y() = lua_tonumber(L, 2);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->y());
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____tostring(lua_State* L) {
	try {
		lua_Vector2* val = lua_tovector2(L, 1);

		lua_Wstring ret = L"("
			+ tostring_n(val->x()) + L","
			+ tostring_n(val->y())
			+ L")";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____gc(lua_State* L) {
	try {
		lua_Vector2* c = lua_tovector2(L, 1);
		if (c != nullptr)
			free(c);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____add(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Vector2* val2 = tm_tovector2(L, 2);

		lua_pushvector2(L, val1->x() + val2->x(), val1->y() + val2->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____sub(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Vector2* val2 = tm_tovector2(L, 2);

		lua_pushvector2(L, val1->x() - val2->x(), val1->y() - val2->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____mul(lua_State* L) {
	try {
		luaL_argcheck(L, lua_isvector2(L, 1) || lua_isnumber(L, 1), 1, "number/vector2 expected");

		if (lua_isvector2(L, 1)) {
			lua_Vector2* val1 = tm_tovector2(L, 1);
			lua_Number val2 = tm_tonumber(L, 2);
			lua_pushvector2(L, (*val1) * val2);
			return 1;
		}
		else if (lua_isnumber(L, 1)) { // Number * Vector2
			lua_Number val1 = tm_tonumber(L, 1);
			lua_Vector2* val2 = tm_tovector2(L, 2);

			lua_pushvector2(L, val1 * (*val2));
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____div(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Number val2 = tm_tonumber(L, 2);

		lua_pushvector2(L, (*val1) / val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____unm(lua_State* L) {
	try {
		lua_Vector2* val = tm_tovector2(L, 1);

		lua_pushvector2(L, -(val->x()), -(val->y()));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____lt(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector2(L, 1)) < geometry_norm(*tm_tovector2(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____le(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector2(L, 1)) <= geometry_norm(*tm_tovector2(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____index(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				lua_pushnumber(L, val1->x());
				return 1;
			case 2:
				lua_pushnumber(L, val1->y());
				return 1;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "x") {
				lua_pushnumber(L, val1->x());
				return 1;
			}
			else if (l == "y") {
				lua_pushnumber(L, val1->y());
				return 1;
			}
			else {
				return 0;
			}
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____newindex(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		lua_Number value = tm_tonumber(L, 3);

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				val1->x() = value;
				break;
			case 2:
				val1->y() = value;
				break;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "x") {
				val1->x() = value;
			}
			else if (l == "y") {
				val1->y() = value;
			}
			else {
				return 0;
			}
		}

		lua_pushvector2(L, *val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____type(lua_State* L) {
	try {
		lua_pushstring(L, "vector2");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2____call(lua_State* L) {
	try {
		lua_Vector2* val = lua_tovector2(L, 1);
		int idx = tm_tointeger(L, 2);

		if (lua_isnoneornil(L, 3)) {
			switch (idx) {
			case 1:
				lua_pushnumber(L, val->x());
				return 1;
			case 2:
				lua_pushnumber(L, val->y());
				return 1;
			default:
				return 0;
			}
		}
		else {
			switch (idx) {
			case 1:
				val->x() = tm_tonumber(L, 3);
				return 0;
			case 2:
				val->y() = tm_tonumber(L, 3);
				return 0;
			default:
				return 0;
			}
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__abs(lua_State* L) {
	try {
		lua_pushnumber(L, geometry_abs(*tm_tovector2(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__norm(lua_State* L) {
	try {
		lua_pushnumber(L, geometry_abs(*tm_tovector2(L, 1)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__normalize(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_pushvector2(L, val1->normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__dot(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Vector2* val2 = tm_tovector2(L, 2);

		lua_pushnumber(L, val1->dot(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__scale(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Vector2* val2 = tm_tovector2(L, 2);

		lua_pushvector2(L, val1->x() * val2->x(), val1->y() * val2->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__distance(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);
		lua_Vector2* val2 = tm_tovector2(L, 2);

		lua_Vector2 ret = (*val1) - (*val2);
		lua_pushnumber(L, geometry_abs(ret));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__conj(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_pushvector2(L, val1->conjugate());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__table(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_newtable(L);
		lua_settablevalue(L, 1, val1->x());
		lua_settablevalue(L, 2, val1->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__complex(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_pushcomplex(L, val1->x(), val1->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__vector3(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_pushvector3(L, val1->x(), val1->y(), 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector2__vector4(lua_State* L) {
	try {
		lua_Vector2* val1 = tm_tovector2(L, 1);

		lua_pushvector4(L, val1->x(), val1->y(), 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_VECTOR2_REG[] = {
	{"new", vector2_new},
	{"identity", vector2_identity},
	{"down", vector2_down},
	{"left", vector2_left},
	{"one", vector2_one},
	{"right", vector2_right},
	{"up", vector2_up},
	{"zero", vector2_zero},

	{"x", vector2__x},
	{"y", vector2__y},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR2_META_REG[] = {
	{"x", vector2__x},
	{"y", vector2__y},

	{"__tostring", vector2____tostring},
	{"__add", vector2____add},
	{"__sub", vector2____sub},
	{"__mul", vector2____mul},
	{"__div", vector2____div},
	{"__unm", vector2____unm},
	{"__lt", vector2____lt},
	{"__le", vector2____le},
	//{"__index", vector2____index},
	{"__newindex", vector2____newindex},
	{"__type", vector2____type},
	{"__call", vector2____call},

	{"__abs", vector2__abs},
	{"__norm", vector2__norm},
	{"__normalize", vector2__normalize},
	{"__dot", vector2__dot},
	{"__conj", vector2__conj},
	{"__scale", vector2__scale},
	{"__distance", vector2__distance},

	{"__table", vector2__table},
	{"__complex", vector2__complex},
	{"__vector3", vector2__vector3},
	{"__vector4", vector2__vector4},
	{nullptr, nullptr}
};

void luaReg_vector2(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_VECTOR2, TEXTMODULE_VECTOR2_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR2_REG);
		lua_setfield(L, -2, name);
	}
}