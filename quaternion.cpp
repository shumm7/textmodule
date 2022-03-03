#include <lua.hpp>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>

#include "textmodule_lua.h"
#include "textmodule_string.h"

#include "quaternion.h"

typedef Eigen::Quaternion<double> Quat;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Matrix3d Matrix3;
typedef Eigen::AngleAxisd AngleAxis;

#define quaternion_check(L, n) (reinterpret_cast<Quat*>(luaL_checkudata(L, n, TEXTMODULE_QUATERNION)))

double q_norm(Quat* q) {
	return std::pow(q->w(), 2) + std::pow(q->x(), 2) + std::pow(q->y(), 2) + std::pow(q->z(), 2);
}

double q_abs(Quat* q) {
	return std::sqrt(q_norm(q));
}


int quaternion_new(lua_State* L) {
	try {
		double w = 0;
		double x = 0;
		double y = 0;
		double z = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			w = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			w = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			x = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			x = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			y = lua_tonumber(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			y = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 4) == LUA_TNUMBER) {
			z = lua_tonumber(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNIL || lua_type(L, 4) == LUA_TNONE) {
			z = 0;
		}
		else {
			return 0;
		}

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

int quaternion_enew(lua_State* L) {
	try {
		double w = 0;
		double x = 0;
		double y = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			w = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			w = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			x = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			x = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			y = lua_tonumber(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			y = 0;
		}
		else {
			return 0;
		}

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
		double w = 0;
		double x = 0;
		double y = 0;
		double z = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			w = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			w = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			x = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			x = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			y = lua_tonumber(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			y = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 4) == LUA_TNUMBER) {
			z = lua_tonumber(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNIL || lua_type(L, 4) == LUA_TNONE) {
			z = 0;
		}
		else {
			return 0;
		}

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*ret = AngleAxis(w, Vector3(x, y, z).normalized());

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_twovectors(lua_State* L) {
	try {
		double x1 = 0;
		double y1 = 0;
		double z1 = 0;
		double x2 = 0;
		double y2 = 0;
		double z2 = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			x1 = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			x1 = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			y1 = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			y1 = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TNUMBER) {
			z1 = lua_tonumber(L, 3);
		}
		else if (lua_type(L, 3) == LUA_TNIL || lua_type(L, 3) == LUA_TNONE) {
			z1 = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 4) == LUA_TNUMBER) {
			x2 = lua_tonumber(L, 4);
		}
		else if (lua_type(L, 4) == LUA_TNIL || lua_type(L, 4) == LUA_TNONE) {
			x2 = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 5) == LUA_TNUMBER) {
			y2 = lua_tonumber(L, 5);
		}
		else if (lua_type(L, 5) == LUA_TNIL || lua_type(L, 5) == LUA_TNONE) {
			y2 = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 6) == LUA_TNUMBER) {
			z2 = lua_tonumber(L, 6);
		}
		else if (lua_type(L, 6) == LUA_TNIL || lua_type(L, 6) == LUA_TNONE) {
			z2 = 0;
		}
		else {
			return 0;
		}

		Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		luaL_getmetatable(L, TEXTMODULE_QUATERNION);
		lua_setmetatable(L, -2);

		*ret = Quat::FromTwoVectors(Vector3(x1, y1, z1), Vector3(x2, y2, z2));

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
		Quat* val;
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = quaternion_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->w() = lua_tonumber(L, 2);
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
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
		Quat* val = new Quat(0, 0, 0, 0);
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = quaternion_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->x() = lua_tonumber(L, 2);
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
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
		Quat* val = new Quat(0, 0, 0, 0);
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = quaternion_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->y() = lua_tonumber(L, 2);
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
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
		Quat* val = new Quat(0, 0, 0, 0);
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = quaternion_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->z() = lua_tonumber(L, 2);
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
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
		Quat* val = new Quat(0, 0, 0, 0);
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = quaternion_check(L, 1);
		}
		else {
			return 0;
		}

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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
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
		Quat* val2 = new Quat(0, 0, 0, 0);

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
		}

		Quat* vret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
		vret->w() = 0;
		vret->x() = 0;
		vret->y() = 0;
		vret->z() = 0;
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

int quaternion____div(lua_State* L) {
	try {
		Quat* val1 = new Quat(0, 0, 0, 0);
		Quat* val2 = new Quat(0, 0, 0, 0);

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
			val1->x() = 0;
			val1->y() = 0;
			val1->z() = 0;
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
		}

		lua_pushboolean(L, q_abs(val1) < q_abs(val2));
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
		}

		lua_pushboolean(L, q_abs(val1) <= q_abs(val2));
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = quaternion_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->w() = lua_tonumber(L, 2);
		}
		else {
			return 0;
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

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = quaternion_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->w() = lua_tonumber(L, 1);
		}
		else {
			return 0;
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
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_QUATERNION_REG);
	lua_setglobal(L, name);
}