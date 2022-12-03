#include "vector3.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_option.hpp"

int vector3_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__vector3"))
			return 1;

		lua_Number x = tm_tonumber_s(L, 1, 0);
		lua_Number y = tm_tonumber_s(L, 2, 0);
		lua_Number z = tm_tonumber_s(L, 3, 0);

		lua_pushvector3(L, x, y, z);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_identity(lua_State* L) {
	try {
		lua_pushvector3(L, lua_Vector3::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_back(lua_State* L) {
	try {
		lua_pushvector3(L, 0, 0, -1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_down(lua_State* L) {
	try {
		lua_pushvector3(L, 0, -1, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_forward(lua_State* L) {
	try {
		lua_pushvector3(L, 0, 0, 1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_left(lua_State* L) {
	try {
		lua_pushvector3(L, -1, 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_one(lua_State* L) {
	try {
		lua_pushvector3(L, 1, 1, 1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_right(lua_State* L) {
	try {
		lua_pushvector3(L, 1, 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_up(lua_State* L) {
	try {
		lua_pushvector3(L, 0, 1, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3_zero(lua_State* L) {
	try {
		lua_pushvector3(L, 0, 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int vector3__x(lua_State* L) {
	try {
		Vector3* val = tm_tovector3(L, 1);

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

int vector3__y(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

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

int vector3__z(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->z() = lua_tonumber(L, 2);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->z());
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____tostring(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

		lua_Wstring ret = L"("
			+ tostring_n(val->x()) + L","
			+ tostring_n(val->y()) + L","
			+ tostring_n(val->z())
			+ L")";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____gc(lua_State* L) {
	try {
		auto c = tm_tovector3(L, 1);
		std::destroy_at(c);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____add(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_pushvector3(L,
			val1->x() + val2->x(),
			val1->y() + val2->y(),
			val1->z() + val2->z()
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____sub(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_pushvector3(L,
			val1->x() - val2->x(),
			val1->y() - val2->y(),
			val1->z() - val2->z()
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____mul(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, "number/vector3 expected");

		if (tp == LUA_TUSERDATA) { // Vector3 * Number
			lua_Vector3* val1 = tm_tovector3(L, 1);
			lua_Number val2 = tm_tonumber(L, 2);

			lua_pushvector3(L, (*val1) * val2);
			return 1;
		}
		else if (tp == LUA_TNUMBER) { // Number * Vector3
			lua_Number val1 = tm_tonumber(L, 1);
			lua_Vector3* val2 = tm_tovector3(L, 2);

			lua_pushvector3(L, val1 * (*val2));
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____div(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Number val2 = tm_tonumber(L, 2);

		lua_pushvector3(L, (*val1) / val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____unm(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

		lua_pushvector3(L, -(val->x()), -(val->y()), -(val->z()));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____lt(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector3(L, 1)) < geometry_norm(*tm_tovector3(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____le(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector3(L, 1)) <= geometry_norm(*tm_tovector3(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____index(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

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
			case 3:
				lua_pushnumber(L, val1->z());
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
			else if (l == "z") {
				lua_pushnumber(L, val1->z());
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

int vector3____newindex(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

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
			case 3:
				val1->z() = value;
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
			else if (l == "z") {
				val1->z() = value;
			}
			else {
				return 0;
			}
		}

		lua_pushvector3(L, *val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____type(lua_State* L) {
	try {
		lua_pushstring(L, "vector3");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____call(lua_State* L) {
	try {
		lua_Vector3* val = lua_tovector3(L, 1);
		int idx = tm_tointeger(L, 2);

		if (lua_isnoneornil(L, 3)) {
			switch (idx) {
			case 1:
				lua_pushnumber(L, val->x());
				return 1;
			case 2:
				lua_pushnumber(L, val->y());
				return 1;
			case 3:
				lua_pushnumber(L, val->z());
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
			case 3:
				val->z() = tm_tonumber(L, 3);
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

int vector3__abs(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

		lua_pushnumber(L, geometry_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__norm(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

		lua_pushnumber(L, geometry_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__normalize(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

		lua_pushvector3(L, val1->normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__dot(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_pushnumber(L, val1->dot(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__cross(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_pushvector3(L, val1->cross(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__scale(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_pushvector3(L, val1->x() * val2->x(), val1->y() * val2->y(), val1->z() * val2->z());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__distance(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);
		lua_Vector3* val2 = tm_tovector3(L, 2);

		lua_Vector3 ret = (*val1) - (*val2);
		lua_pushnumber(L, geometry_abs(ret));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__conj(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

		lua_pushvector3(L, val1->conjugate());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__table(lua_State* L) {
	try {
		lua_Vector3* val1 = tm_tovector3(L, 1);

		lua_newtable(L);
		lua_settablevalue(L, 1, val1->x());
		lua_settablevalue(L, 2, val1->y());
		lua_settablevalue(L, 3, val1->z());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__vector2(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

		lua_pushvector2(L, val->x(), val->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__vector4(lua_State* L) {
	try {
		lua_Vector3* val = tm_tovector3(L, 1);

		lua_pushvector4(L, val->x(), val->y(), val->z(), 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_VECTOR3_REG[] = {
	{"new", vector3_new},
	{"identity", vector3_identity},
	{"back", vector3_back},
	{"down", vector3_down},
	{"forward", vector3_forward},
	{"left", vector3_left},
	{"one", vector3_one},
	{"right", vector3_right},
	{"up", vector3_up},
	{"zero", vector3_zero},

	{"x", vector3__x},
	{"y", vector3__y},
	{"z", vector3__z},

	{"table", vector3__table},
	{"vector2", vector3__vector2},
	{"vector4", vector3__vector4},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR3_META_REG[] = {
	{"x", vector3__x},
	{"y", vector3__y},
	{"z", vector3__z},

	{"__tostring", vector3____tostring},
	{"__add", vector3____add},
	{"__sub", vector3____sub},
	{"__mul", vector3____mul},
	{"__div", vector3____div},
	{"__unm", vector3____unm},
	{"__lt", vector3____lt},
	{"__le", vector3____le},
	{"__gc", vector3____gc},
	//{"__index", vector3____index},
	{"__newindex", vector3____newindex},
	{"__type", vector3____type},
	{"__call", vector3____call},
	{"__abs", vector3__abs},
	{"__norm", vector3__norm},
	{"__normalize", vector3__normalize},
	{"__dot", vector3__dot},
	{"__cross", vector3__cross},
	{"__conj", vector3__conj},
	{"__scale", vector3__scale},
	{"__distance", vector3__distance},
	{"__table", vector3__table},
	{"__vector2", vector3__vector2},
	{"__vector4", vector3__vector4},

	{"abs", vector3__abs},
	{"norm", vector3__norm},
	{"normalize", vector3__normalize},
	{"dot", vector3__dot},
	{"cross", vector3__cross},
	{"conj", vector3__conj},
	{"scale", vector3__scale},
	{"distance", vector3__distance},
	{nullptr, nullptr}
};

void luaReg_vector3(lua_State* L, lua_Option opt) {
	if (opt["api"]["geometry"]["vector3"]) {
		tm_debuglog_apiloaded(opt, "vector3");
		luaL_newmetatable(L, TEXTMODULE_VECTOR3, TEXTMODULE_VECTOR3_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR3_REG);
		lua_setfield(L, -2, "vector3");
	}
	else {
		tm_debuglog_apinoloaded(opt, "vector3");
	}
}