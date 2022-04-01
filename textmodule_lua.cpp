#include <lua.hpp>
#include <iostream>
#include <format>

#include "textmodule_lua.h"
#include "textmodule_color.h"
#include "textmodule_string.h"
#include "textmodule_math.h"
#include "textmodule_exception.h"
#include "textmodule_geometry.h"

// String
lua_Wstring lua_towstring(lua_State* L, int idx) {
	return StrToWstr(lua_tostring(L, idx));
}

lua_Wstring tm_towstring(lua_State* L, int idx) {
	return StrToWstr(luaL_checkstring(L, idx));
}

lua_Wstring tm_towstring_s(lua_State* L, int idx, lua_Wstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_towstring(L, idx);
	}
}

lua_Wstring tm_towstring_s(lua_State* L, int idx) {
	return tm_towstring_s(L, idx, L"");
}

lua_Sstring lua_tosstring(lua_State* L, int idx) {
	return lua_tostring(L, idx);
}

lua_Sstring tm_tosstring(lua_State* L, int idx) {
	return luaL_checkstring(L, idx);
}

lua_Sstring tm_tosstring_s(lua_State* L, int idx, lua_Sstring def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tostring(L, idx);
	}
}

lua_Sstring tm_tosstring_s(lua_State* L, int idx) {
	return tm_tosstring_s(L, idx, "");
}

lua_String tm_tostring(lua_State* L, int idx) {
	return luaL_checkstring(L, idx);
}

lua_String tm_tostring_s(lua_State* L, int idx, lua_String def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, idx, "string/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tostring(L, idx);
	}
}

lua_String tm_tostring_s(lua_State* L, int idx) {
	return tm_tostring_s(L, idx, "");
}

void lua_pushwstring(lua_State* L, lua_Wstring s) {
	lua_pushstring(L, WstrToStr(s).c_str());
}

void lua_pushsstring(lua_State* L, lua_Sstring s) {
	lua_pushstring(L, s.c_str());
}

//Number
lua_Integer tm_tointeger(lua_State* L, int idx) {
	return luaL_checkinteger(L, idx);
}

lua_Integer tm_tointeger_s(lua_State* L, int idx, lua_Integer def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tointeger(L, idx);
	}
}

lua_Integer tm_tointeger_s(lua_State* L, int idx) {
	return tm_tointeger_s(L, idx, 0);
}

lua_Number tm_todouble(lua_State* L, int idx) {
	return static_cast<double>(luaL_checknumber(L, idx));
}

lua_Number tm_tonumber(lua_State* L, int idx) {
	return tm_todouble(L, idx);
}

lua_Number tm_tonumber_s(lua_State* L, int idx, lua_Number def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, idx, "number/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_tonumber(L, idx);
	}
}

lua_Number tm_tonumber_s(lua_State* L, int idx) {
	return tm_tonumber_s(L, idx, 0);
}

lua_Float tm_tofloat(lua_State* L, int idx) {
	return static_cast<float>(luaL_checknumber(L, idx));
}

lua_Unsigned tm_tounsigned(lua_State* L, int idx) {
	return static_cast<unsigned long>(luaL_checkinteger(L, idx));
}

// Boolean
lua_Boolean tm_toboolean(lua_State* L, int idx) {
	if(lua_type(L, idx)!=LUA_TBOOLEAN)
		luaL_typerror(L, idx, lua_typename(L, LUA_TBOOLEAN));
	return lua_toboolean(L, idx);
}

lua_Boolean tm_toboolean_s(lua_State* L, int idx, lua_Boolean def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TBOOLEAN, idx, "boolean/none expected");

	if (tp == LUA_TNONE) {
		return def;
	}
	else {
		return lua_toboolean(L, idx);
	}
}

lua_Boolean tm_toboolean_s(lua_State* L, int idx) {
	return tm_toboolean_s(L, idx, false);
}

// Table
void lua_settablevalue(lua_State* L, int key, lua_Number value) {
	lua_pushinteger(L, key);
	lua_pushnumber(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Integer value) {
	lua_pushinteger(L, key);
	lua_pushinteger(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Boolean value) {
	lua_pushinteger(L, key);
	lua_pushboolean(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_String value) {
	lua_pushinteger(L, key);
	lua_pushstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Sstring value) {
	lua_pushinteger(L, key);
	lua_pushsstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, int key, lua_Wstring value) {
	lua_pushinteger(L, key);
	lua_pushwstring(L, value);
	lua_settable(L, -3);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Number value) {
	lua_pushnumber(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Integer value) {
	lua_pushinteger(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Boolean value) {
	lua_pushboolean(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_String value) {
	lua_pushstring(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Sstring value) {
	lua_pushsstring(L, value);
	lua_setfield(L, -2, key);
}

void lua_settablevalue(lua_State* L, const char* key, lua_Wstring value) {
	lua_pushwstring(L, value);
	lua_setfield(L, -2, key);
}

// Complex
lua_Complex* lua_tocomplex(lua_State* L, int idx) {
	return complex_check(L, idx);
}

lua_Complex* tm_tocomplex(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, idx, "number/complex expected");
	std::complex<double>* val = new std::complex<double>;

	if (tp == LUA_TUSERDATA) {
		val = complex_check(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->real(lua_tonumber(L, idx));
		val->imag(0);
	}

	return val;
}

lua_Complex* tm_tocomplex_s(lua_State* L, int idx, lua_Complex def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER || tp == LUA_TNONE, idx, "number/complex/none expected");
	std::complex<double>* val = new std::complex<double>;

	if (tp == LUA_TUSERDATA) {
		val = complex_check(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->real(lua_tonumber(L, idx));
		val->imag(0);
	}
	else if (tp == LUA_TNONE) {
		val->real(def.real());
		val->imag(def.imag());
	}

	return val;
}

lua_Complex* tm_tocomplex_s(lua_State* L, int idx) {
	return tm_tocomplex_s(L, idx, lua_Complex(0, 0));
}

lua_Complex* lua_pushcomplex(lua_State* L, double real, double imag) {
	std::complex<double>* ret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
	luaL_getmetatable(L, TEXTMODULE_COMPLEX);
	lua_setmetatable(L, -2);
	ret->real(real);
	ret->imag(imag);

	return ret;
}

lua_Complex* lua_pushcomplex(lua_State* L, lua_Complex complex) {
	return lua_pushcomplex(L, complex.real(), complex.imag());
}

lua_Complex* lua_pushcomplex(lua_State* L) {
	return lua_pushcomplex(L, 0, 0);
}

// Quaternion
lua_Quaternion* lua_toquaternion(lua_State* L, int idx) {
	return quaternion_check(L, idx);
}

lua_Quaternion* tm_toquaternion(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER, idx, "number/quaternion expected");
	Quat* val = new Quat();

	if (tp == LUA_TUSERDATA) {
		val = quaternion_check(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->w() = lua_tonumber(L, idx);
	}

	return val;
}

lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx, lua_Quaternion def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNUMBER || LUA_TNONE, idx, "number/quaternion/none expected");
	Quat* val = new Quat();

	if (tp == LUA_TUSERDATA) {
		val = quaternion_check(L, idx);
	}
	else if (tp == LUA_TNUMBER) {
		val->w() = lua_tonumber(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->w() = def.w();
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
	}

	return val;
}

lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx) {
	return tm_toquaternion_s(L, idx, lua_Quaternion(0, 0, 0, 0));
}

lua_Quaternion* lua_pushquaternion(lua_State* L, double w, double x, double y, double z) {
	Quat* ret = reinterpret_cast<Quat*>(lua_newuserdata(L, sizeof(Quat)));
	luaL_getmetatable(L, TEXTMODULE_QUATERNION);
	lua_setmetatable(L, -2);

	ret->w() = w;
	ret->x() = x;
	ret->y() = y;
	ret->z() = z;

	return ret;
}

lua_Quaternion* lua_pushquaternion(lua_State* L, lua_Quaternion quaternion) {
	return lua_pushquaternion(L, quaternion.w(), quaternion.x(), quaternion.y(), quaternion.z());
}

lua_Quaternion* lua_pushquaternion(lua_State* L) {
	return lua_pushquaternion(L, 0, 0, 0, 0);
}

// Vector2
lua_Vector2* lua_tovector2(lua_State* L, int idx) {
	return vector2_check(L, idx);
}

lua_Vector2* tm_tovector2(lua_State* L, int idx) {
	return lua_tovector2(L, idx);
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx, lua_Vector2 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp==LUA_TNONE, idx, "vector2/none expected");
	Vector2* val = new Vector2();

	if (tp == LUA_TUSERDATA) {
		val = vector2_check(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
	}

	return val;
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx, double x, double y) {
	return tm_tovector2_s(L, idx, lua_Vector2(x, y));
}

lua_Vector2* tm_tovector2_s(lua_State* L, int idx) {
	return tm_tovector2_s(L, idx, lua_Vector2(0, 0));
}

lua_Vector2* lua_pushvector2(lua_State* L, double x, double y) {
	Vector2* ret = reinterpret_cast<Vector2*>(lua_newuserdata(L, sizeof(Vector2)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR2);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	return ret;
}

lua_Vector2* lua_pushvector2(lua_State* L, lua_Vector2 vector) {
	return lua_pushvector2(L, vector.x(), vector.y());
}

lua_Vector2* lua_pushvector2(lua_State* L) {
	return lua_pushvector2(L, 0, 0);
}

// Vector3
lua_Vector3* lua_tovector3(lua_State* L, int idx) {
	return vector3_check(L, idx);
}

lua_Vector3* tm_tovector3(lua_State* L, int idx) {
	return lua_tovector3(L, idx);
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx, lua_Vector3 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "vector3/none expected");
	Vector3* val = new Vector3();

	if (tp == LUA_TUSERDATA) {
		val = vector3_check(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
	}

	return val;
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx, double x, double y, double z) {
	return tm_tovector3_s(L, idx, lua_Vector3(x, y, z));
}

lua_Vector3* tm_tovector3_s(lua_State* L, int idx) {
	return tm_tovector3_s(L, idx, lua_Vector3(0, 0,0));
}

lua_Vector3* lua_pushvector3(lua_State* L, double x, double y, double z) {
	Vector3* ret = reinterpret_cast<Vector3*>(lua_newuserdata(L, sizeof(Vector3)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR3);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	ret->z() = z;
	return ret;
}

lua_Vector3* lua_pushvector3(lua_State* L, lua_Vector3 vector) {
	return lua_pushvector3(L, vector.x(), vector.y(), vector.z());
}

lua_Vector3* lua_pushvector3(lua_State* L) {
	return lua_pushvector3(L, 0, 0, 0);
}

// Vector4
lua_Vector4* lua_tovector4(lua_State* L, int idx) {
	return vector4_check(L, idx);
}

lua_Vector4* tm_tovector4(lua_State* L, int idx) {
	return lua_tovector4(L, idx);
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx, lua_Vector4 def) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, tp == LUA_TUSERDATA || tp == LUA_TNONE, idx, "vector4/none expected");
	Vector4* val = new Vector4();

	if (tp == LUA_TUSERDATA) {
		val = vector4_check(L, idx);
	}
	else if (tp == LUA_TNONE) {
		val->x() = def.x();
		val->y() = def.y();
		val->z() = def.z();
		val->w() = def.w();
	}

	return val;
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx, double x, double y, double z, double w) {
	return tm_tovector4_s(L, idx, lua_Vector4(x,y,z,w));
}

lua_Vector4* tm_tovector4_s(lua_State* L, int idx) {
	return tm_tovector4_s(L, idx, lua_Vector4(0, 0, 0, 0));
}

lua_Vector4* lua_pushvector4(lua_State* L, double x, double y, double z, double w) {
	Vector4* ret = reinterpret_cast<Vector4*>(lua_newuserdata(L, sizeof(Vector4)));
	luaL_getmetatable(L, TEXTMODULE_VECTOR4);
	lua_setmetatable(L, -2);

	ret->x() = x;
	ret->y() = y;
	ret->z() = z;
	ret->w() = w;
	return ret;
}

lua_Vector4* lua_pushvector4(lua_State* L, lua_Vector4 vector) {
	return lua_pushvector4(L, vector.x(), vector.y(), vector.z(), vector.w());
}

lua_Vector4* lua_pushvector4(lua_State* L) {
	return lua_pushvector4(L, 0, 0, 0, 0);
}

// Misc
bool luaL_checkmetatable(lua_State* L, int ud, const char* tname) {
	if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
		lua_getfield(L, LUA_REGISTRYINDEX, tname);  /* get correct metatable */
		if (lua_rawequal(L, -1, -2)) {  /* does it have the correct mt? */
			lua_pop(L, 2);
			return true;
		}
		lua_pop(L, 2);
	}
	return false;
}

const char* tm_convtostring(lua_State* L, int idx) {
	if (lua_type(L, idx) == LUA_TNONE)
		return "none";
	else {
		if (luaL_callmeta(L, idx, "__tostring")) {
			const char* s = lua_tostring(L, -1);
			lua_pop(L, 1);
			return s;
		}

		switch (lua_type(L, idx)) {
		case LUA_TSTRING:
		case LUA_TNUMBER:
			return lua_tostring(L, idx);
		case LUA_TBOOLEAN:
			return (lua_toboolean(L, idx) ? "true" : "false");
		case LUA_TNIL:
			return "nil";
		default:
			lua_Sstring _f = std::format("{0:s}: {1:p}", luaL_typename(L, idx), lua_topointer(L, idx));
			const char* f = _f.c_str();
			return f;
		}
	}
}

const char* tm_typename(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	if (tp == LUA_TUSERDATA) {
		if (luaL_checkmetatable(L, idx, TEXTMODULE_COMPLEX))
			return "complex";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_QUATERNION))
			return "quaternion";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR2))
			return "vector2";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR3))
			return "vector3";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_VECTOR4))
			return "vector4";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_RGB))
			return "rgb";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_HSV))
			return "hsv";
		else if (luaL_checkmetatable(L, idx, TEXTMODULE_HSL))
			return "hsl";
		else if (luaL_checkmetatable(L, idx, LUA_FILEHANDLE))
			return "filehandle";
	}
	else if (tp == LUA_TTABLE) {
		if (luaL_checkmetatable(L, idx, TEXTMODULE_COLORLIST))
			return "colorlist";
	}

	return lua_typename(L, tp);
}

