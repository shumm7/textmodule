#include <iostream>

#define MODULE_NAME "textmodule"
#define MODULE_VERSION 21

#define API_BASE "base"
#define API_STRING "string"
#define API_TMSTRING "tmstring"
#define API_CMATH "math"
#define API_OS "os"
#define API_UTF8 "utf8"
#define API_COLOR "color"
#define API_CLIPBOARD "clipboard"
#define API_FILESYSTEM "filesystem"
#define API_COMPLEX "complex"
#define API_QUATERNION "quaternion"
#define API_HASH "hash"
#define API_HTTP "http"

#define API_COLOR_BASE "base"
#define API_RGB "rgb"
#define API_HSV "hsv"
#define API_HSL "hsl"

#define ALIAS_MODULE_NAME "tm"
#define ALIAS_API_TMSTRING "tmstr"
#define ALIAS_API_FILESYSTEM "fs"

std::wstring getVersionNum(int num);