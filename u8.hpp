#include <lua.hpp>

int u8_offset(lua_State* L);
int u8_codepoint(lua_State* L);
int u8_char(lua_State* L);
int u8_len(lua_State* L);
int u8_codes(lua_State* L);

void luaReg_u8(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_U8_REG [] = {
  {"offset", u8_offset},
  {"codepoint", u8_codepoint},
  {"char", u8_char},
  {"len", u8_len},
  {"codes", u8_codes},
  {nullptr, nullptr}
};