#pragma once
#include <lua.hpp>

int bit_rshift(lua_State* L);
int bit_lshift(lua_State* L);
int bit_rrotate(lua_State* L);
int bit_lrotate(lua_State* L);
int bit_not(lua_State* L);
int bit_and(lua_State* L);
int bit_or(lua_State* L);
int bit_xor(lua_State* L);
int bit_ceil(lua_State* L);
int bit_floor(lua_State* L);
int bit_popcount(lua_State* L);
int bit_string(lua_State* L);

void luaReg_bit(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_BIT_REG[] = {
  {"rshift", bit_rshift},
  {"lshift", bit_lshift},
  {"rrotate", bit_rrotate},
  {"lrotate", bit_lrotate},
  {"band", bit_and},
  {"bnot", bit_not},
  {"bor", bit_or},
  {"bxor", bit_xor},
  {"ceil", bit_ceil},
  {"floor", bit_floor},
  {"popcount", bit_popcount},
  {"string", bit_string},
  {nullptr, nullptr}
};