#pragma once
#include <iostream>
#include <windows.h>

#define MODULE_NAME "textmodule"
#define MODULE_VERSION 31

//API
#define API_BASE "base"
#define API_DEBUG "debug"
#define API_STRING "string"
#define API_CMATH "math"
#define API_RANDOM "random"
#define API_OS "os"
#define API_UTF8 "utf8"
#define API_COLOR "color"
#define API_CLIPBOARD "clipboard"
#define API_FILESYSTEM "filesystem"
#define API_HASH "hash"
#define API_HTTP "http"
#define API_BIT "bit"
#define API_QRCODE "qrcode"
#define API_OBJ "object"
#define API_EASE "ease"
#define API_DEVICE "device"
#define API_TIME "time"
#define API_JSON "json" 

//API_COLOR
#define API_COLOR "color"
#define API_PIXEL "pixel"
#define API_IMAGE "image"

//API_GEOMETRY
#define API_GEOMETRY "geometry"
#define API_COMPLEX "complex"
#define API_VECTOR2 "vector2"
#define API_VECTOR3 "vector3"
#define API_VECTOR4 "vector4"
#define API_QUATERNION "quaternion"
#define API_MATRIX2 "matrix2"
#define API_MATRIX3 "matrix3"

//ALIAS
#define ALIAS_MODULE_NAME "tm"
#define ALIAS_API_FILESYSTEM "fs"
#define ALIAS_API_RANDOM "rand"
#define ALIAS_API_OBJ "obj"

std::wstring getVersionNum(int num);
void SetDllPath();
HWND GetAviUtlWindowHandle();