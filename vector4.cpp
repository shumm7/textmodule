#include "vector4.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"

int vector4_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__vector4"))
			return 1;

		lua_Number x = tm_tonumber_s(L, 1, 0);
		lua_Number y = tm_tonumber_s(L, 2, 0);
		lua_Number z = tm_tonumber_s(L, 3, 0);
		lua_Number w = tm_tonumber_s(L, 4, 0);

		lua_pushvector4(L, x, y, z, w);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4_identity(lua_State* L) {
	try {
		lua_pushvector4(L, lua_Vector4::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4_one(lua_State* L) {
	try {
		lua_pushvector4(L, 1, 1, 1, 1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4_zero(lua_State* L) {
	try {
		lua_pushvector4(L, 0, 0, 0, 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int vector4__x(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

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

int vector4__y(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

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

int vector4__z(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

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

int vector4__w(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->w() = lua_tonumber(L, 2);
			return 0;
		}
		else if (tp == LUA_TNONE) {
			lua_pushnumber(L, val->w());
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____tostring(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		lua_Wstring ret = L"("
			+ tostring_n(val->x()) + L","
			+ tostring_n(val->y()) + L","
			+ tostring_n(val->z()) + L","
			+ tostring_n(val->w())
			+ L")";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____gc(lua_State* L) {
	try {
		lua_Vector4* c = tm_tovector4(L, 1);
		if (c != nullptr)
			free(c);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____add(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Vector4* val2 = tm_tovector4(L, 2);

		lua_pushvector4(L,
			val1->x() + val2->x(),
			val1->y() + val2->y(),
			val1->z() + val2->z(),
			val1->w() + val2->w()
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____sub(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Vector4* val2 = tm_tovector4(L, 2);

		lua_pushvector4(L,
			val1->x() - val2->x(),
			val1->y() - val2->y(),
			val1->z() - val2->z(),
			val1->w() - val2->w()
		);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____mul(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, "number/vector4 expected");

		if (tp == LUA_TUSERDATA) { // Vector4 * Number
			lua_Vector4* val1 = tm_tovector4(L, 1);
			lua_Number val2 = tm_tonumber(L, 2);

			lua_pushvector4(L, (*val1) * val2);
			return 1;
		}
		else if (tp == LUA_TNUMBER) { // Number * Vector4
			lua_Number val1 = tm_tonumber(L, 1);
			lua_Vector4* val2 = tm_tovector4(L, 2);

			lua_pushvector4(L, val1 * (*val2));
			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____div(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Number val2 = tm_tonumber(L, 2);

		lua_pushvector4(L, (*val1) / val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____unm(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		lua_pushvector4(L, -(val->x()), -(val->y()), -(val->z()), -(val->w()));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____lt(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector4(L, 1)) < geometry_norm(*tm_tovector4(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____le(lua_State* L) {
	try {
		lua_pushboolean(L, geometry_norm(*tm_tovector4(L, 1)) <= geometry_norm(*tm_tovector4(L, 2)));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____index(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

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
			case 4:
				lua_pushnumber(L, val1->w());
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
			else if (l == "w") {
				lua_pushnumber(L, val1->w());
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

int vector4____newindex(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

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
			case 4:
				val1->w() = value;
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
			else if (l == "w") {
				val1->w() = value;
			}
			else {
				return 0;
			}
		}

		lua_pushvector4(L, *val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____type(lua_State* L) {
	try {
		lua_pushstring(L, "vector4");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____call(lua_State* L) {
	try {
		lua_Vector4* val = lua_tovector4(L, 1);
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
			case 4:
				lua_pushnumber(L, val->w());
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
			case 4:
				val->w() = tm_tonumber(L, 3);
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

int vector4__abs(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

		lua_pushnumber(L, geometry_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__norm(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

		lua_pushnumber(L, geometry_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__normalize(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

		lua_pushvector4(L, val1->normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__dot(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Vector4* val2 = tm_tovector4(L, 2);

		lua_pushnumber(L, val1->dot(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__scale(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Vector4* val2 = tm_tovector4(L, 2);

		lua_pushvector4(L, val1->x() * val2->x(), val1->y() * val2->y(), val1->z() * val2->z(), val1->w() * val2->w());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__distance(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);
		lua_Vector4* val2 = tm_tovector4(L, 2);

		lua_Vector4 ret = (*val1) - (*val2);
		lua_pushnumber(L, geometry_abs(ret));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__conj(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

		lua_pushvector4(L, val1->conjugate());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__table(lua_State* L) {
	try {
		lua_Vector4* val1 = tm_tovector4(L, 1);

		lua_newtable(L);
		lua_settablevalue(L, 1, val1->x());
		lua_settablevalue(L, 2, val1->y());
		lua_settablevalue(L, 3, val1->z());
		lua_settablevalue(L, 4, val1->w());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__quaternion(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		lua_pushquaternion(L, val->x(), val->y(), val->z(), val->w());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__vector2(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		lua_Vector2* ret = lua_pushvector2(L, val->x(), val->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__vector3(lua_State* L) {
	try {
		lua_Vector4* val = tm_tovector4(L, 1);

		lua_Vector3* ret = lua_pushvector3(L, val->x(), val->y(), val->z());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_VECTOR4_REG[] = {
	{"new", vector4_new},
	{"identity", vector4_identity},
	{"one", vector4_one},
	{"zero", vector4_zero},

	{"x", vector4__x},
	{"y", vector4__y},
	{"z", vector4__z},
	{"w", vector4__w},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_VECTOR4_META_REG[] = {
	{"x", vector4__x},
	{"y", vector4__y},
	{"z", vector4__z},
	{"w", vector4__w},

	{"__tostring", vector4____tostring},
	{"__add", vector4____add},
	{"__sub", vector4____sub},
	{"__mul", vector4____mul},
	{"__div", vector4____div},
	{"__unm", vector4____unm},
	{"__lt", vector4____lt},
	{"__le", vector4____le},
	//{"__index", vector4____index},
	{"__newindex", vector4____newindex},
	{"__type", vector4____type},
	{"__call", vector4____call},
	{"__abs", vector4__abs},
	{"__norm", vector4__norm},
	{"__normalize", vector4__normalize},
	{"__dot", vector4__dot},
	{"__conj", vector4__conj},
	{"__scale", vector4__scale},
	{"__distance", vector4__distance},
	{"__table", vector4__table},
	{"__quaternion", vector4__quaternion},
	{"__vector2", vector4__vector2},
	{"__vector3", vector4__vector3},

	{"abs", vector4__abs},
	{"norm", vector4__norm},
	{"normalize", vector4__normalize},
	{"dot", vector4__dot},
	{"conj", vector4__conj},
	{"scale", vector4__scale},
	{"distance", vector4__distance},

	{nullptr, nullptr}
};

void luaReg_vector4(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_VECTOR4, TEXTMODULE_VECTOR4_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR4_REG);
		lua_setfield(L, -2, name);
	}
}