#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "vector3.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "textmodule_geometry.h"

int vector3_new(lua_State* L) {
	try {
		double x = tm_tonumber_s(L, 1, 0);
		double y = tm_tonumber_s(L, 2, 0);
		double z = tm_tonumber_s(L, 3, 0);

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
		lua_pushvector3(L, Vector3::Identity());
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
		Vector3* val = vector3_check(L, 1);

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
		Vector3* val = vector3_check(L, 1);

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
		Vector3* val = vector3_check(L, 1);

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
		Vector3* val = vector3_check(L, 1);

		std::wstring ret = L"("
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
		Vector3* c = vector3_check(L, 1);
		if (c != nullptr)
			free(c);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____add(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

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
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

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
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, "number/" TEXTMODULE_VECTOR3 " expected");

		if (tp == LUA_TUSERDATA) { // Vector3 * Number
			Vector3* val1 = vector3_check(L, 1);
			double val2 = tm_tonumber(L, 2);

			lua_pushvector3(L, (*val1) * val2);
			return 1;
		}
		else if (tp == LUA_TNUMBER) { // Number * Vector3
			double val1 = lua_tonumber(L, 1);
			Vector3* val2 = vector3_check(L, 2);

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
		Vector3* val1 = vector3_check(L, 1);
		double val2 = tm_tonumber(L, 2);

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
		Vector3* val = vector3_check(L, 1);

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
		double val1 = g_vector3_norm(*vector3_check(L, 1));
		double val2 = g_vector3_norm(*vector3_check(L, 2));

		lua_pushboolean(L, val1 < val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____le(lua_State* L) {
	try {
		double val1 = g_vector3_norm(*vector3_check(L, 1));
		double val2 = g_vector3_norm(*vector3_check(L, 2));

		lua_pushboolean(L, val1 <= val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3____index(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);

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
		Vector3* val1 = vector3_check(L, 1);

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

int vector3__abs(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);

		lua_pushnumber(L, g_vector3_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__norm(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);

		lua_pushnumber(L, g_vector3_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__normalize(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);

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
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

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
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

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
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

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
		Vector3* val1 = vector3_check(L, 1);
		Vector3* val2 = vector3_check(L, 2);

		Vector3 ret = (*val1) - (*val2);
		lua_pushnumber(L, g_vector3_abs(ret));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__conj(lua_State* L) {
	try {
		Vector3* val1 = vector3_check(L, 1);

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
		Vector3* val1 = vector3_check(L, 1);

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
		Vector3* val = vector3_check(L, 1);

		Vector2* ret = lua_pushvector2(L, val->x(), val->y());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int vector3__vector4(lua_State* L) {
	try {
		Vector3* val = vector3_check(L, 1);

		Vector4* ret = lua_pushvector4(L, val->x(), val->y(), val->z(), 0);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_vector3(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//vector3
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR3_REG);
		lua_setfield(L, -2, name);

		//vector3 (metatable)
		luaL_newmetatable(L, TEXTMODULE_VECTOR3); //add metatable
		luaL_register(L, NULL, TEXTMODULE_VECTOR3_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR3_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}

void luaGlobal_vector3(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_VECTOR3_REG);
		lua_setglobal(L, name);
	}
}
