#include "quaternion.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"

int quaternion_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__quaternion"))
			return 1;

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA || tp == LUA_TNONE, 1, "number/quaternion expected");

		lua_Number w = 0;
		lua_Number x = 0;
		lua_Number y = 0;
		lua_Number z = 0;

		if (tp == LUA_TNUMBER || tp == LUA_TNONE) {
			w = tm_tonumber(L, 1);
			x = tm_tonumber(L, 2);
			y = tm_tonumber(L, 3);
			z = tm_tonumber(L, 4);
		}
		else if (tp == LUA_TUSERDATA && lua_isquaternion(L, 1)) {
			auto q = tm_toquaternion(L, 1);
			w = q->w();
			x = q->x();
			y = q->y();
			z = q->z();
		}

		lua_pushquaternion(L, w, x, y, z);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_euler_new(lua_State* L) {
	try {
		lua_Number x = tm_tonumber(L, 1);
		lua_Number y = tm_tonumber(L, 2);
		lua_Number z = tm_tonumber(L, 3);

		lua_Quaternion* ret = lua_pushquaternion(L);
		*ret = AngleAxis(x, Vector3::UnitX()) * AngleAxis(y, Vector3::UnitY()) * AngleAxis(z, Vector3::UnitZ());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_angleaxis(lua_State* L) {
	try {
		lua_Number r = tm_tonumber(L, 1);
		lua_Vector3* axis = tm_tovector3(L, 2);

		lua_Quaternion* ret = lua_pushquaternion(L);
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
		lua_Vector3* v1 = tm_tovector3(L, 1);
		lua_Vector3* v2 = tm_tovector3(L, 2);

		lua_pushquaternion(L, Quat::FromTwoVectors(*v1, *v2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_lookrot(lua_State* L) {
	try {
		lua_Vector3* v1;
		lua_Vector3* v2;

		if (lua_type(L, 1) == LUA_TNONE)
			v1 = new lua_Vector3(0, 0, 1);
		else
			v1 = tm_tovector3(L, 1);

		if (lua_type(L, 2) == LUA_TNONE)
			v2 = new lua_Vector3(0, 1, 0);
		else
			v2 = tm_tovector3(L, 2);


		lua_Quaternion* ret = lua_pushquaternion(L);

		if (v1->norm() == 0) {
			*ret = ret->Identity();
			return 1;
		}

		if (v1 != v2) {
			v2->normalize();
			auto v = (*v1) + (*v2) * (- v1->dot(*v2));
			auto q = Quat::FromTwoVectors(Vector3(0,0,1), v);

			*ret = Quat::FromTwoVectors(v, *v1) * q;
			return 1;
		}
		else {
			*ret = Quat::FromTwoVectors(Vector3(0, 0, 1), *v1);
			return 1;
		}

	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion_identity(lua_State* L) {
	lua_pushquaternion(L, lua_Quaternion::Identity());
	return 1;
}

int quaternion_zero(lua_State* L) {
	lua_pushquaternion(L);
	return 1;
}

int quaternion__w(lua_State* L) {
	try {
		lua_Quaternion* val= tm_toquaternion(L, 1);

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
		lua_Quaternion* val = tm_toquaternion(L, 1);

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
		lua_Quaternion* val = tm_toquaternion(L, 1);

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
		lua_Quaternion* val = tm_toquaternion(L, 1);

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
		lua_Quaternion* val = tm_toquaternion(L, 1);

		lua_Wstring ret = L"("
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
		lua_Quaternion* c = tm_toquaternion(L, 1);
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
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushquaternion(L,
			val1->w() + val2->w(),
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

int quaternion____sub(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushquaternion(L,
			val1->w() - val2->w(),
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

int quaternion____mul(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, 2, "number/quaternion/vector3 expected");

		if (tp == LUA_TUSERDATA) {
			if (luaL_checkmetatable(L, 2, TEXTMODULE_QUATERNION)) {
				lua_Quaternion* val2 = tm_toquaternion(L, 2);
				lua_pushquaternion(L, (*val1) * (*val2));
				return 1;
			}
			else if (luaL_checkmetatable(L, 2, TEXTMODULE_VECTOR3)) {
				lua_Vector3* val2 = tm_tovector3(L, 2);
				lua_pushvector3(L, (*val1) * (*val2));
				return 1;
			}
			else
				return luaL_argerror(L, 2, "number/quaternion/vector3 expected");
		}
		else if (tp == LUA_TNUMBER) {
			lua_Quaternion* val2 = new lua_Quaternion(lua_tonumber(L, 2),0,0,0);
			lua_pushquaternion(L, (*val1) * (*val2));
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
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_Quaternion* vret = lua_pushquaternion(L);
		*vret = (*val1) * ( val2->conjugate());
		double d = geometry_norm(*val2);
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
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_Quaternion* vret = lua_pushquaternion(L);
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
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushboolean(L, geometry_norm(*val1) < geometry_norm(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____le(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushboolean(L, geometry_norm(*val1) <= geometry_norm(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____index(lua_State* L) {
	try {
		lua_Quaternion* val1 = lua_toquaternion(L, 1);

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
			lua_Sstring l = tm_tostring(L, 2);
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
		lua_Quaternion* val1 = lua_toquaternion(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TSTRING || tp == LUA_TNUMBER, 2, "string/number expected");
		lua_Number value = tm_tonumber(L, 3);

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
			lua_Sstring l = tm_tostring(L, 2);
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

		lua_pushquaternion(L, *val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____type(lua_State* L) {
	try {
		lua_pushstring(L, "quaternion");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____tonumber(lua_State* L) {
	try {
		lua_Quaternion* val = tm_toquaternion(L, 1);

		lua_Wstring ret = tostring_n(val->w()) + L"+" + tostring_n(val->x()) + L"i+" + tostring_n(val->y()) + L"j+" + tostring_n(val->z()) + L"k";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion____call(lua_State* L) {
	try {
		lua_Quaternion* val = lua_toquaternion(L, 1);
		int idx = tm_tointeger(L, 2);

		if (lua_isnoneornil(L, 3)) {
			switch (idx) {
			case 1:
				lua_pushnumber(L, val->w());
				return 1;
			case 2:
				lua_pushnumber(L, val->x());
				return 1;
			case 3:
				lua_pushnumber(L, val->y());
				return 1;
			case 4:
				lua_pushnumber(L, val->z());
				return 1;
			default:
				return 0;
			}
		}
		else {
			switch (idx) {
			case 1:
				val->w() = tm_tonumber(L, 3);
				return 0;
			case 2:
				val->x() = tm_tonumber(L, 3);
				return 0;
			case 3:
				val->y() = tm_tonumber(L, 3);
				return 0;
			case 4:
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

int quaternion__abs(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushnumber(L, geometry_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__norm(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushnumber(L, geometry_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__conj(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushquaternion(L, val1->conjugate());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__euler(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushvector3(L, (*val1).toRotationMatrix().eulerAngles(0, 1, 2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__inverse(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushquaternion(L, val1->inverse());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__normalize(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);

		lua_pushquaternion(L, val1->normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__dot(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushnumber(L, val1->dot(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__cross(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_pushquaternion(L, (*val1) * (*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__slerp(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion(L, 1);
		lua_Quaternion* val2 = tm_toquaternion(L, 2);

		lua_Quaternion res(val1->w(), val1->x(), val1->y(), val1->z());
		lua_Quaternion p(val2->w(), val2->x(), val2->y(), val2->z());
		lua_Number t = tm_tonumber(L, 3);

		lua_pushquaternion(L, res.slerp(t, p));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int quaternion__table(lua_State* L) {
	try {
		lua_Quaternion* val1 = tm_toquaternion_s(L, 1);

		lua_newtable(L);
		lua_settablevalue(L, 1, val1->w());
		lua_settablevalue(L, 2, val1->x());
		lua_settablevalue(L, 3, val1->y());
		lua_settablevalue(L, 4, val1->z());

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_QUATERNION_REG[] = {
	{"new", quaternion_new},
	{"euler_new", quaternion_euler_new},
	{"enew", quaternion_euler_new},
	{"angleaxis", quaternion_angleaxis},
	{"twovectors", quaternion_twovectors},
	{"lookrot", quaternion_lookrot},
	{"identity", quaternion_identity},
	{"zero", quaternion_zero},

	{"w", quaternion__w},
	{"x", quaternion__x},
	{"y", quaternion__y},
	{"z", quaternion__z},

	{"slerp", quaternion__slerp},
	{"euler", quaternion__euler},
	{"inverse", quaternion__inverse},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_QUATERNION_META_REG[] = {
	{"w", quaternion__w},
	{"x", quaternion__x},
	{"y", quaternion__y},
	{"z", quaternion__z},

	{"__tostring", quaternion____tostring},
	{"__add", quaternion____add},
	{"__sub", quaternion____sub},
	{"__mul", quaternion____mul},
	{"__div", quaternion____div},
	{"__unm", quaternion____unm},
	{"__lt", quaternion____lt},
	{"__le", quaternion____le},
	//{"__index", quaternion____index},
	{"__newindex", quaternion____newindex},
	{"__type", quaternion____type},
	{"__tonumber", quaternion____tonumber},
	{"__call", quaternion____call},
	{"__abs", quaternion__abs},
	{"__norm", quaternion__norm},
	{"__conj", quaternion__conj},
	{"__dot", quaternion__dot},
	{"__cross", quaternion__cross},
	{"__normalize", quaternion__normalize},
	{"__lerp", quaternion__slerp},
	{"__table", quaternion__table},

	{"abs", quaternion__abs},
	{"norm", quaternion__norm},
	{"conj", quaternion__conj},
	{"dot", quaternion__dot},
	{"cross", quaternion__cross},
	{"normalize", quaternion__normalize},
	{"slerp", quaternion__slerp},
	{"euler", quaternion__euler},
	{"inverse", quaternion__inverse},
	{nullptr, nullptr}
};

void luaReg_quaternion(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_QUATERNION, TEXTMODULE_QUATERNION_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_QUATERNION_REG);
		lua_setfield(L, -2, name);
	}
}