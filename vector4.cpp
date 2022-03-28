#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "vector4.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "textmodule_geometry.h"

int vector4_new(lua_State* L) {
	try {
		double x = tm_tonumber_s(L, 1, 0);
		double y = tm_tonumber_s(L, 2, 0);
		double z = tm_tonumber_s(L, 3, 0);
		double w = tm_tonumber_s(L, 4, 0);

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
		lua_pushvector4(L, Vector4::Identity());
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
		Vector4* val = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

		std::wstring ret = L"("
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
		Vector4* c = vector4_check(L, 1);
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
		Vector4* val1 = vector4_check(L, 1);
		Vector4* val2 = vector4_check(L, 2);

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
		Vector4* val1 = vector4_check(L, 1);
		Vector4* val2 = vector4_check(L, 2);

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
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, "number/" TEXTMODULE_VECTOR4 " expected");

		if (tp == LUA_TUSERDATA) { // Vector4 * Number
			Vector4* val1 = vector4_check(L, 1);
			double val2 = tm_tonumber(L, 2);

			lua_pushvector4(L, (*val1) * val2);
			return 1;
		}
		else if (tp == LUA_TNUMBER) { // Number * Vector4
			double val1 = lua_tonumber(L, 1);
			Vector4* val2 = vector4_check(L, 2);

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
		Vector4* val1 = vector4_check(L, 1);
		double val2 = tm_tonumber(L, 2);

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
		Vector4* val = vector4_check(L, 1);

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
		double val1 = g_vector4_norm(*vector4_check(L, 1));
		double val2 = g_vector4_norm(*vector4_check(L, 2));

		lua_pushboolean(L, val1 < val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____le(lua_State* L) {
	try {
		double val1 = g_vector4_norm(*vector4_check(L, 1));
		double val2 = g_vector4_norm(*vector4_check(L, 2));

		lua_pushboolean(L, val1 <= val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____index(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

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
			std::string l = tm_tostring(L, 2);
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
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4____newindex(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		double value = tm_tonumber(L, 3);

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
			std::string l = tm_tostring(L, 2);
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

int vector4__abs(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

		lua_pushnumber(L, g_vector4_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__norm(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

		lua_pushnumber(L, g_vector4_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__normalize(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

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
		Vector4* val1 = vector4_check(L, 1);
		Vector4* val2 = vector4_check(L, 2);

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
		Vector4* val1 = vector4_check(L, 1);
		Vector4* val2 = vector4_check(L, 2);

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
		Vector4* val1 = vector4_check(L, 1);
		Vector4* val2 = vector4_check(L, 2);

		Vector4 ret = (*val1) - (*val2);
		lua_pushnumber(L, g_vector4_abs(ret));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__conj(lua_State* L) {
	try {
		Vector4* val1 = vector4_check(L, 1);

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
		Vector4* val1 = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

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
		Vector4* val = vector4_check(L, 1);

		Vector2* ret = lua_pushvector2(L, val->x(), val->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector4__vector3(lua_State* L) {
	try {
		Vector4* val = vector4_check(L, 1);

		Vector3* ret = lua_pushvector3(L, val->x(), val->y(), val->z());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_vector4(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//vector4
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR4_REG);
		lua_setfield(L, -2, name);

		//vector4 (metatable)
		luaL_newmetatable(L, TEXTMODULE_VECTOR4); //add metatable
		luaL_register(L, NULL, TEXTMODULE_VECTOR4_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR4_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}

void luaGlobal_vector4(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR4_REG);
		lua_setglobal(L, name);
	}
}