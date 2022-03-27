#pragma once
#include <lua.hpp>
#include <iostream>
#include <complex>
#include <Eigen/Geometry>
#include <Eigen/Dense>

typedef Eigen::Quaternion<double> Quat;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Vector2d Vector2;

typedef std::string lua_Sstring;
typedef std::wstring lua_Wstring;

// String
std::wstring lua_towstring(lua_State* L, int idx);
std::wstring tm_towstring(lua_State* L, int idx);
std::wstring tm_towstring_s(lua_State* L, int idx);
std::wstring tm_towstring_s(lua_State* L, int idx, std::wstring def);
std::string lua_tosstring(lua_State* L, int idx);
std::string tm_tosstring(lua_State* L, int idx);
std::string tm_tosstring_s(lua_State* L, int idx);
std::string tm_tosstring_s(lua_State* L, int idx, const char* def);
const char* tm_tostring(lua_State* L, int idx);
const char* tm_tostring_s(lua_State* L, int idx);
const char* tm_tostring_s(lua_State* L, int idx, const char* def);
void lua_pushwstring(lua_State* L, std::wstring s);
void lua_pushsstring(lua_State* L, std::string s);

// Number
int tm_tointeger(lua_State* L, int idx);
int tm_tointeger_s(lua_State* L, int idx);
int tm_tointeger_s(lua_State* L, int idx, int def);
float tm_tofloat(lua_State* L, int idx);
double tm_todouble(lua_State* L, int idx);
double tm_tonumber(lua_State* L, int idx);
double tm_tonumber_s(lua_State* L, int idx);
double tm_tonumber_s(lua_State* L, int idx, double def);
unsigned long tm_tounsigned(lua_State* L, int idx);

// Boolean
bool tm_toboolean_s(lua_State* L, int idx);
bool tm_toboolean_s(lua_State* L, int idx, bool def);

// Metatable
bool luaL_checkmetatable(lua_State* L, int ud, const char* tname);

// Table
void lua_settablevalue(lua_State* L, int key, double value);
void lua_settablevalue(lua_State* L, int key, int value);
void lua_settablevalue(lua_State* L, int key, bool value);
void lua_settablevalue(lua_State* L, int key, const char* value);
void lua_settablevalue(lua_State* L, int key, std::string value);
void lua_settablevalue(lua_State* L, int key, std::wstring value);
void lua_settablevalue(lua_State* L, const char* key, double value);
void lua_settablevalue(lua_State* L, const char* key, int value);
void lua_settablevalue(lua_State* L, const char* key, bool value);
void lua_settablevalue(lua_State* L, const char* key, const char* value);
void lua_settablevalue(lua_State* L, const char* key, std::string value);
void lua_settablevalue(lua_State* L, const char* key, std::wstring value);

// Geometry
std::complex<double>* tm_tocomplex_s(lua_State* L, int idx);
std::complex<double>* lua_pushcomplex(lua_State* L, double real, double imag);
std::complex<double>* lua_pushcomplex(lua_State* L, std::complex<double> complex);
std::complex<double>* lua_pushcomplex(lua_State* L);
Quat* tm_toquaternion_s(lua_State* L, int idx);
Quat* lua_pushquaternion(lua_State* L, double w, double x, double y, double z);
Quat* lua_pushquaternion(lua_State* L, Quat quaternion);
Quat* lua_pushquaternion(lua_State* L);
Vector2* lua_pushvector2(lua_State* L, double x, double y);
Vector2* lua_pushvector2(lua_State* L, Vector2 vector);
Vector2* lua_pushvector2(lua_State* L);
Vector3* lua_pushvector3(lua_State* L, double x, double y, double z);
Vector3* lua_pushvector3(lua_State* L, Vector3 vector);
Vector3* lua_pushvector3(lua_State* L);