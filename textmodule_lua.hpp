#pragma once
#include <lua.hpp>
#include <iostream>
#include <chrono>

#include <Eigen/Geometry>
#include <unicode/unistr.h>
#include <unicode/ustring.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

#include <nlohmann/json.hpp>

#include "textmodule_type.hpp"

#define TEXTMODULE_VECTOR2 "Eigen::Vector2d*"
#define TEXTMODULE_VECTOR3 "Eigen::Vector3d*"
#define TEXTMODULE_VECTOR4 "Eigen::Vector4d*"
#define TEXTMODULE_COMPLEX "std::complex<double>*"
#define TEXTMODULE_QUATERNION "Eigen::Quaterniond*"
#define TEXTMODULE_JSON "nlohmann::json*"
#define TEXTMODULE_COLORLIST "table ColorList"
#define TEXTMODULE_COLOR "st_rgba*"
#define TEXTMODULE_PIXEL "st_rgba32*"
#define TEXTMODULE_IMAGE "st_imgpixel*"
#define TEXTMODULE_CLOCK "std::chrono::utc_clock::time_point*"
#define TEXTMODULE_BIGNUMBER "boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1024>>"

//Type for wide string (std::wstring)
typedef std::wstring lua_Wstring;
//Type for multibyte string (std::string)
typedef std::string lua_Sstring;
//Type of unicode string (icu::UnicodeString)
typedef icu::UnicodeString lua_Ustring;
//Type for lua string (const char*)
typedef const char* lua_String;
//Type for float number
typedef float lua_Float;
//Type for unsigned integer
typedef unsigned long lua_Unsigned;
//Type for boolean
typedef bool lua_Boolean;
//Type for time point
typedef utc_clock lua_Clock;
//Type for 1024 bit integer
typedef dec_float lua_Bignumber;
// Type for json
typedef nlohmann::json lua_Json;

//Type for complex class
typedef Complex lua_Complex;
//Type for quaternion class
typedef Quat	lua_Quaternion;
//Type for vector2 class
typedef Vector2	lua_Vector2;
//Type for vector3 class
typedef Vector3	lua_Vector3;
//Type for vector4 class
typedef Vector4	lua_Vector4;

//Type for rgba class
typedef st_rgba lua_Color;
//Type for value of rgba class
typedef double lua_Colorvar;
//Type for 32bit rgba class
typedef st_rgba32 lua_Pixel;
//Type for value of 32bit rgba class
typedef unsigned char lua_Pixelvar;
//Type of 32bit bgra array
typedef st_imgpixel lua_Image;

// String
lua_Wstring lua_towstring(lua_State* L, int idx);
lua_Wstring tm_towstring(lua_State* L, int idx);
lua_Wstring tm_towstring_s(lua_State* L, int idx, lua_Wstring def);
lua_Wstring tm_towstring_s(lua_State* L, int idx);
lua_Wstring lua_tolwstring(lua_State* L, int idx, size_t* len);
lua_Wstring tm_tolwstring(lua_State* L, int idx, size_t* len);
lua_Wstring tm_tolwstring_s(lua_State* L, int idx, size_t* len, lua_Wstring def);
lua_Wstring tm_tolwstring_s(lua_State* L, int idx, size_t* len);
void lua_pushwstring(lua_State* L, lua_Wstring s);
void lua_pushlwstring(lua_State* L, lua_Wstring s, size_t l);

// Sstring
lua_Sstring lua_tosstring(lua_State* L, int idx);
lua_Sstring tm_tosstring(lua_State* L, int idx);
lua_Sstring tm_tosstring_s(lua_State* L, int idx, lua_Sstring def);
lua_Sstring tm_tosstring_s(lua_State* L, int idx);
lua_Sstring tm_tolsstring(lua_State* L, int idx, size_t* len);
lua_Sstring tm_tolsstring_s(lua_State* L, int idx, size_t* len, lua_Sstring def);
lua_Sstring tm_tolsstring_s(lua_State* L, int idx, size_t* len);
void lua_pushsstring(lua_State* L, lua_Sstring s);
void lua_pushlsstring(lua_State* L, lua_Sstring s, size_t l);

// Ustring
lua_Ustring lua_toustring(lua_State* L, int idx);
lua_Ustring tm_toustring(lua_State* L, int idx);
lua_Ustring tm_toustring_s(lua_State* L, int idx, lua_Ustring def);
lua_Ustring tm_toustring_s(lua_State* L, int idx);
void lua_pushustring(lua_State* L, lua_Ustring s);

// String
lua_String tm_tostring(lua_State* L, int idx);
lua_String tm_tostring_s(lua_State* L, int idx, lua_String def);
lua_String tm_tostring_s(lua_State* L, int idx);
lua_String tm_tolstring(lua_State* L, int idx, size_t* len);
lua_String tm_tolstring_s(lua_State* L, int idx, size_t* len, lua_String def);
lua_String tm_tolstring_s(lua_State* L, int idx, size_t* len);

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

// Bignumber
lua_Bignumber lua_tobignumber(lua_State* L, int idx);
lua_Bignumber tm_tobignumber(lua_State* L, int idx);
lua_Bignumber tm_tobignumber_s(lua_State* L, int idx, lua_Bignumber def);
lua_Bignumber tm_tobignumber_s(lua_State* L, int idx);
lua_Bignumber lua_pushbignumber(lua_State* L, lua_Bignumber value);
lua_Bignumber lua_pushbignumber(lua_State* L);

// Table
void lua_settablevalue(lua_State* L, int key, lua_Number value);
void lua_settablevalue(lua_State* L, int key, lua_Integer value);
void lua_settablevalue(lua_State* L, int key, lua_Boolean value);
void lua_settablevalue(lua_State* L, int key, lua_String value);
void lua_settablevalue(lua_State* L, int key, lua_Sstring value);
void lua_settablevalue(lua_State* L, int key, lua_Wstring value);
void lua_settablevalue(lua_State* L, int key, lua_Bignumber value);
void lua_settablevalue(lua_State* L, const char* key, lua_Number value);
void lua_settablevalue(lua_State* L, const char* key, lua_Integer value);
void lua_settablevalue(lua_State* L, const char* key, lua_Boolean value);
void lua_settablevalue(lua_State* L, const char* key, lua_String value);
void lua_settablevalue(lua_State* L, const char* key, lua_Sstring value);
void lua_settablevalue(lua_State* L, const char* key, lua_Wstring value);
void lua_settablevalue(lua_State* L, const char* key, lua_Bignumber value);
void lua_setfield(lua_State* L, int idx, lua_Sstring k);
void lua_setfield(lua_State* L, int idx, lua_Wstring k);
bool lua_isarray(lua_State* L, int idx);

// Clock
lua_Clock* lua_toclock(lua_State* L, int idx);
lua_Clock* tm_toclock(lua_State* L, int idx);
lua_Clock* tm_toclock_s(lua_State* L, int idx, lua_Clock def);
lua_Clock* tm_toclock_s(lua_State* L, int idx);
lua_Clock* lua_pushclock(lua_State* L, lua_Clock clock);
lua_Clock* lua_pushclock(lua_State* L);

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

// Color
lua_Color* lua_tocolor(lua_State* L, int idx);
lua_Color* tm_tocolor(lua_State* L, int idx);
lua_Color* tm_tocolor_s(lua_State* L, int idx, lua_Color def);
lua_Color* tm_tocolor_s(lua_State* L, int idx, double r, double g, double b, double a);
lua_Color* tm_tocolor_s(lua_State* L, int idx);
lua_Color* lua_pushcolor(lua_State* L, double r, double g, double b, double a);
lua_Color* lua_pushcolor(lua_State* L, lua_Color def);
lua_Color* lua_pushcolor(lua_State* L, lua_Vector4 def);
lua_Color* lua_pushcolor(lua_State* L);

// Pixel
lua_Pixel* lua_topixel(lua_State* L, int idx);
lua_Pixel* tm_topixel(lua_State* L, int idx);
lua_Pixel* tm_topixel_s(lua_State* L, int idx, lua_Pixel def);
lua_Pixel* tm_topixel_s(lua_State* L, int idx, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
lua_Pixel* tm_topixel_s(lua_State* L, int idx, double r, double g, double b, double a);
lua_Pixel* tm_topixel_s(lua_State* L, int idx);
lua_Pixel* lua_pushpixel(lua_State* L, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
lua_Pixel* lua_pushpixel(lua_State* L, double r, double g, double b, double a);
lua_Pixel* lua_pushpixel(lua_State* L, lua_Pixel def);
lua_Pixel* lua_pushpixel(lua_State* L);

// Image
lua_Image* lua_toimage(lua_State* L, int idx);
lua_Image* tm_toimage(lua_State* L, int idx);
lua_Image* lua_convertcache(lua_State* L, int idx);

// Misc
bool luaL_checkmetatable(lua_State* L, int ud, const char* tname);
const char* tm_convtostring(lua_State* L, int idx);
const char* tm_typename(lua_State* L, int idx);
void lua_printstack(lua_State* L);
int lua_pushtmstruct(lua_State* L, std::tm* tmstruct);
void lua_totmstruct(lua_State* L, int idx, std::tm* out);
bool tm_callmeta(lua_State* L, int obj, const char* event);
bool tm_callmetan(lua_State* L, int obj, const char* event, int nargs);

// Json Utility
lua_Json tm_jsonparse(lua_Sstring str);
lua_Sstring tm_jsondump(lua_Json* j);
lua_Sstring tm_jsondump(lua_Json* j, int l);
void tm_pushjson(lua_State* L, lua_Json* j);
lua_Json tm_tabletojson(lua_State* L, int idx);
lua_Json tm_tojson(lua_State* L, int idx);