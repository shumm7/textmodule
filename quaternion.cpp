#include <lua.hpp>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"
#include "quaternion.h"
#include "vector3.h"

double q_norm(Quat* q) {
	return std::pow(q->w(), 2) + std::pow(q->x(), 2) + std::pow(q->y(), 2) + std::pow(q->z(), 2);
}

double q_abs(Quat* q) {
	return std::sqrt(q_norm(q));
}

std::string get_qargmsg() {
	std::string m = "number/";
	m.append(TEXTMODULE_QUATERNION);
	m.append(" expected");

	return m;
}


int quaternion_new(lua_State* L) {
	try {
		double w = tm_tonumber_s(L, 1, 0);
		double x = tm_tonumber_s(L, 2, 0);
		double y = tm_tonumber_s(L, 3, 0);
		double z = tm_tonumber_s(L, 4, 0);

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		ret->w() = w;
		ret->x() = x;
		ret->y() = y;
		ret->z() = z;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_euler_new(lua_State* L) {
	try {
		double w = tm_tonumber_s(L, 1, 0);
		double x = tm_tonumber_s(L, 2, 0);
		double y = tm_tonumber_s(L, 3, 0);

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*ret = AngleAxis(w, Vector3::UnitX()) * AngleAxis(x, Vector3::UnitY()) * AngleAxis(y, Vector3::UnitZ());

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_angleaxis(lua_State* L) {
	try {
		double r = tm_tonumber_s(L, 1, 0);
		Vector3* axis = vector3_check(L, 2);

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*ret = AngleAxis(r, axis->normalized());

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_twovectors(lua_State* L) {
	try {
		Vector3* v1 = vector3_check(L, 1);
		Vector3* v2 = vector3_check(L, 2);

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*ret = Quat::FromTwoVectors(*v1, *v2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_identity(lua_State* L) {
	Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
	luaL_getmetatable(L, TEXTMODULE_QUATERNION);
	lua_setmetatable(L, -2);

	ret->w() = 1;
	ret->x() = 0;
	ret->y() = 0;
	ret->z() = 0;

	return 1;
}

int quaternion__w(lua_State* L) {
	try {
		Quat* val= quaternion_check(L, 1);

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

int quaternion__x(lua_State* L) {
	try {
		Quat* val = quaternion_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE|| tp == LUA_TNUMBER, 2, "number/none expected");

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

int quaternion__y(lua_State* L) {
	try {
		Quat* val = quaternion_check(L, 1);

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

int quaternion__z(lua_State* L) {
	try {
		Quat* val = quaternion_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE|| tp == LUA_TNUMBER, 2, "number/none expected");

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

int quaternion____tostring(lua_State* L) {
	try {
		Quat* val = quaternion_check(L, 1);

		std::wstring ret = L"("
			+ tostring_n(val->w()) + L","
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

int quaternion____gc(lua_State* L) {
	try {
		Quat* c = quaternion_check(L, 1);
		if (c != nullptr)
			free(c);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____add(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		vret->w() = val1->w() + val2->w();
		vret->x() = val1->x() + val2->x();
		vret->y() = val1->y() + val2->y();
		vret->z() = val1->z() + val2->z();

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____sub(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		vret->w() = val1->w() - val2->w();
		vret->x() = val1->x() - val2->x();
		vret->y() = val1->y() - val2->y();
		vret->z() = val1->z() - val2->z();

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____mul(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			if (luaL_checkmetatable(L, 2, TEXTMODULE_QUATERNION)) {
				Quat* val2 = quaternion_check(L, 2);

				Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
				luaL_getmetatable(L, TEXTMODULE_QUATERNION);
				lua_setmetatable(L, -2);
				*vret = (*val1) * (*val2);

				return 1;
			}
			else if (luaL_checkmetatable(L, 2, TEXTMODULE_VECTOR3)) {
				Vector3* val2 = vector3_check(L, 2);

				Vector3* vret = reinterpret_cast<Vector3*>(lua_newuserdata(L, sizeof(Vector3)));
				luaL_getmetatable(L, TEXTMODULE_VECTOR3);
				lua_setmetatable(L, -2);
				*vret = (*val1) * (*val2);

				return 1;
			}
		}
		else if (tp == LUA_TNUMBER) {
			Quat* val2 = new Quat(0,0,0,0);
			val2->w() = lua_tonumber(L, 2);

			Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
			luaL_getmetatable(L, TEXTMODULE_QUATERNION);
			lua_setmetatable(L, -2);
			*vret = (*val1) * (*val2);

			return 1;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____div(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
			val1->x() = 0;
			val1->y() = 0;
			val1->z() = 0;
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		*vret = (*val1) * ( val2->conjugate());
		double d = q_norm(val2);
		vret->w() /= d;
		vret->x() /= d;
		vret->y() /= d;
		vret->z() /= d;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____unm(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		vret->w() *= -1;
		vret->x() *= -1;
		vret->y() *= -1;
		vret->z() *= -1;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____lt(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}

		lua_pushboolean(L, q_norm(val1) < q_norm(val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____le(lua_State* L) {
	try {
		Quat* val1 = new Quat(0,0,0,0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}

		lua_pushboolean(L, q_norm(val1) <= q_norm(val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____index(lua_State* L) {
	try {
		Quat* val1 = quaternion_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
				case 1:
					lua_pushnumber(L, val1->w());
					return 1;
				case 2:
					lua_pushnumber(L, val1->x());
					return 1;
				case 3:
					lua_pushnumber(L, val1->y());
					return 1;
				case 4:
					lua_pushnumber(L, val1->z());
					return 1;
				default:
					return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "w") {
				lua_pushnumber(L, val1->w());
				return 1;
			}
			else if (l == "x") {
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
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____newindex(lua_State* L) {
	try {
		Quat* val1 = quaternion_check(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());
		double value = tm_tonumber(L, 3);

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
				case 1:
					val1->w() = value;
					break;
				case 2:
					val1->x() = value;
					break;
				case 3:
					val1->y() = value;
					break;
				case 4:
					val1->z() = value;
					break;
				default:
					return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			std::string l = tm_tostring(L, 2);
			if (l == "w") {
				val1->w() = value;
			}
			else if (l == "x") {
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

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		*vret = *val1;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__abs(lua_State* L) {
	try {
		Quat* val1 = new Quat(0,0,0,0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		lua_pushnumber(L, q_abs(val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__norm(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		lua_pushnumber(L, q_norm(val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__conj(lua_State* L) {
	try {
		Quat* val1 = new Quat(0,0,0,0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		*vret = val1->conjugate();

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__euler(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		Vector3 euler = (*val1).toRotationMatrix().eulerAngles(0, 1, 2);
		lua_pushnumber(L, euler[0]);
		lua_pushnumber(L, euler[1]);
		lua_pushnumber(L, euler[2]);

		return 3;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__inverse(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*vret = val1->inverse();

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__normalize(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*vret = val1->normalized();

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__dot(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}

		double a = val1->w() * val2->w() + val1->x() * val2->x() + val1->y() * val2->y() + val1->z() * val2->z();
		lua_pushnumber(L, a);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__table(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		lua_newtable(L);
		lua_pushinteger(L, 1);
		lua_pushnumber(L, val1->w());
		lua_settable(L, -3);

		lua_pushinteger(L, 2);
		lua_pushnumber(L, val1->x());
		lua_settable(L, -3);

		lua_pushinteger(L, 3);
		lua_pushnumber(L, val1->y());
		lua_settable(L, -3);

		lua_pushinteger(L, 4);
		lua_pushnumber(L, val1->z());
		lua_settable(L, -3);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__cross(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 1, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (tp == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}

		tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, get_qargmsg().c_str());

		if (tp == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (tp == LUA_TNUMBER) {
			val2->w() = tm_tonumber(L, 2);
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);
		*vret = (*val1) * (*val2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_quaternion(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//quaternion
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_QUATERNION_REG);
		lua_setfield(L, -2, name);

		//quaternion (metatable)
		luaL_newmetatable(L, TEXTMODULE_QUATERNION); //add metatable
		luaL_register(L, NULL, TEXTMODULE_QUATERNION_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_QUATERNION_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}

void luaGlobal_quaternion(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_QUATERNION_REG);
		lua_setglobal(L, name);
	}
}