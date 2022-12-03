#pragma once
#include <lua.hpp>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

const char* lua_typeexception(std::vector<std::string> type);
const char* lua_typeexception(std::string type);
int luaL_argerror(lua_State* L, int numarg, std::string extramsg);
int luaL_typeexception(lua_State* L, int numarg, std::vector<std::string> type);
int luaL_typeexception(lua_State* L, int numarg, std::string type);

void tm_debuglog(std::string message, nlohmann::json option);


//general
#define WRONG_NUMBER_OF_ARGS "wrong number of arguments"
#define INVALID_TYPE "invalid type of argument"
#define OUT_OF_RANGE "the value is out of range"

//device
#define JOYSTICK_NOTFOUND "the specified joystick is not connected"
#define GET_OSVERSION_FAILED "failed to get the os version"

//cmath
#define CLAMP_OUT_OF_RANGE "the value which you tried to clamp is out of range"
#define COMBINATION_ZERO "combination less than 0 undefined"
#define N_LESSER_THAN_R "n must be greater than or equal to r"
#define N_LESSER_THAN_ONE "n must be greater than or equal to 1"
#define FACTORIAL_ZERO "factorial less than 0 is undefined"
#define PERMUTATION_ZERO "permutation less than 0 undefined"
#define CIRCULAR_PERMUTATION_ONE "circular permutation less than 1 is undefined"
#define NOT_SEQUENCE "must be a sequence containing 2 or more numbers"

//color
#define INVALID_SEARCH_MODE "invalid search mode"
#define IMAGE_OUT_OF_RANGE "pixel coordinate is out of range"
#define IMAGE_IS_EMPTY "the specified image is empty"
#define WRONG_IMAGE_ARRAY_DIMENSION "wrong image array dimension"

//string
#define STRING_COVERSION_FAILED "string conversion failed"
#define INVALID_CHARACTER "invalid character"
#define INVALID_FORMAT_STRING "invalid format string"

//obj
#define EXEDIT_AUF_NOTFOUND "exedit.auf was not found"