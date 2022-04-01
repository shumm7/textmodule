#pragma once
#include <lua.hpp>
#include <iostream>
#include "textmodule_geometry.h"
#include "textmodule_color.h"

// Type Define
typedef std::wstring lua_Wstring;
typedef std::string lua_Sstring;
typedef const char* lua_String;
typedef float lua_Float;
typedef unsigned long lua_Unsigned;
typedef bool lua_Boolean;

typedef std::complex<double> lua_Complex;
typedef Quat	lua_Quaternion;
typedef Vector2	lua_Vector2;
typedef Vector3	lua_Vector3;
typedef Vector4	lua_Vector4;


// String
lua_Wstring lua_towstring(lua_State* L, int idx);
lua_Wstring tm_towstring(lua_State* L, int idx);
lua_Wstring tm_towstring_s(lua_State* L, int idx, lua_Wstring def);
lua_Wstring tm_towstring_s(lua_State* L, int idx);
lua_Sstring lua_tosstring(lua_State* L, int idx);
lua_Sstring tm_tosstring(lua_State* L, int idx);
lua_Sstring tm_tosstring_s(lua_State* L, int idx, lua_Sstring def);
lua_Sstring tm_tosstring_s(lua_State* L, int idx);
lua_String tm_tostring(lua_State* L, int idx);
lua_String tm_tostring_s(lua_State* L, int idx, lua_String def);
lua_String tm_tostring_s(lua_State* L, int idx);
void lua_pushwstring(lua_State* L, lua_Wstring s);
void lua_pushsstring(lua_State* L, lua_Sstring s);

// Number
lua_Integer tm_tointeger(lua_State* L, int idx);
lua_Integer tm_tointeger_s(lua_State* L, int idx, lua_Integer def);
lua_Integer tm_tointeger_s(lua_State* L, int idx);
lua_Number tm_todouble(lua_State* L, int idx);
lua_Number tm_tonumber(lua_State* L, int idx);
lua_Number tm_tonumber_s(lua_State* L, int idx, lua_Number def);
lua_Number tm_tonumber_s(lua_State* L, int idx);
lua_Float tm_tofloat(lua_State* L, int idx);
lua_Unsigned tm_tounsigned(lua_State* L, int idx);

// Boolean
lua_Boolean tm_toboolean(lua_State* L, int idx);
lua_Boolean tm_toboolean_s(lua_State* L, int idx, lua_Boolean def);
lua_Boolean tm_toboolean_s(lua_State* L, int idx);

// Table
void lua_settablevalue(lua_State* L, int key, lua_Number value);
void lua_settablevalue(lua_State* L, int key, lua_Integer value);
void lua_settablevalue(lua_State* L, int key, lua_Boolean value);
void lua_settablevalue(lua_State* L, int key, lua_String value);
void lua_settablevalue(lua_State* L, int key, lua_Sstring value);
void lua_settablevalue(lua_State* L, int key, lua_Wstring value);
void lua_settablevalue(lua_State* L, const char* key, lua_Number value);
void lua_settablevalue(lua_State* L, const char* key, lua_Integer value);
void lua_settablevalue(lua_State* L, const char* key, lua_Boolean value);
void lua_settablevalue(lua_State* L, const char* key, lua_String value);
void lua_settablevalue(lua_State* L, const char* key, lua_Sstring value);
void lua_settablevalue(lua_State* L, const char* key, lua_Wstring value);

// Complex
lua_Complex* lua_tocomplex(lua_State* L, int idx);
lua_Complex* tm_tocomplex(lua_State* L, int idx);
lua_Complex* tm_tocomplex_s(lua_State* L, int idx, lua_Complex def);
lua_Complex* tm_tocomplex_s(lua_State* L, int idx);
lua_Complex* lua_pushcomplex(lua_State* L, double real, double imag);
lua_Complex* lua_pushcomplex(lua_State* L, lua_Complex complex);
lua_Complex* lua_pushcomplex(lua_State* L);

// Quaternion
lua_Quaternion* lua_toquaternion(lua_State* L, int idx);
lua_Quaternion* tm_toquaternion(lua_State* L, int idx);
lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx, lua_Quaternion def);
lua_Quaternion* tm_toquaternion_s(lua_State* L, int idx);
lua_Quaternion* lua_pushquaternion(lua_State* L, double w, double x, double y, double z);
lua_Quaternion* lua_pushquaternion(lua_State* L, lua_Quaternion quaternion);
lua_Quaternion* lua_pushquaternion(lua_State* L);

// Vector2
lua_Vector2* lua_tovector2(lua_State* L, int idx);
lua_Vector2* tm_tovector2(lua_State* L, int idx);
lua_Vector2* tm_tovector2_s(lua_State* L, int idx, lua_Vector2 def);
lua_Vector2* tm_tovector2_s(lua_State* L, int idx, double x, double y);
lua_Vector2* tm_tovector2_s(lua_State* L, int idx);
lua_Vector2* lua_pushvector2(lua_State* L, double x, double y);
lua_Vector2* lua_pushvector2(lua_State* L, lua_Vector2 vector);
lua_Vector2* lua_pushvector2(lua_State* L);

// Vector3
lua_Vector3* lua_tovector3(lua_State* L, int idx);
lua_Vector3* tm_tovector3(lua_State* L, int idx);
lua_Vector3* tm_tovector3_s(lua_State* L, int idx, lua_Vector3 def);
lua_Vector3* tm_tovector3_s(lua_State* L, int idx, double x, double y, double z);
lua_Vector3* tm_tovector3_s(lua_State* L, int idx);
lua_Vector3* lua_pushvector3(lua_State* L, double x, double y, double z);
lua_Vector3* lua_pushvector3(lua_State* L, lua_Vector3 vector);
lua_Vector3* lua_pushvector3(lua_State* L);

// Vector4
lua_Vector4* lua_tovector4(lua_State* L, int idx);
lua_Vector4* tm_tovector4(lua_State* L, int idx);
lua_Vector4* tm_tovector4_s(lua_State* L, int idx, lua_Vector4 def);
lua_Vector4* tm_tovector4_s(lua_State* L, int idx, double x, double y, double z, double w);
lua_Vector4* tm_tovector4_s(lua_State* L, int idx);
lua_Vector4* lua_pushvector4(lua_State* L, double x, double y, double z, double w);
lua_Vector4* lua_pushvector4(lua_State* L, lua_Vector4 vector);
lua_Vector4* lua_pushvector4(lua_State* L);

// Misc
bool luaL_checkmetatable(lua_State* L, int ud, const char* tname);
const char* tm_convtostring(lua_State* L, int idx);
const char* tm_typename(lua_State* L, int idx);