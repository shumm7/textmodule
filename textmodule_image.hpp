#pragma once
#include "textmodule_lua.hpp"

lua_Cache* lua_tocache(lua_State* L, int idx);
lua_Cache* tm_tocache(lua_State* L, int idx);
lua_Image* lua_toimage(lua_State* L, int idx);
lua_Image* tm_toimage(lua_State* L, int idx);
lua_Image* lua_newimage(lua_State* L, int width, int height)

lua_Image* lua_pushimage(lua_State* L, lua_Image image);
void lua_copytocache(lua_State* L, lua_Cache* dest, int width, int height, lua_Image* image);
void lua_copyfromcache(lua_State* L, lua_Image* dest, lua_Cache* cache, int width, int height);

int get_imgindex(lua_Vector2 coordinate, int width, int height);
int get_imgindex_s(lua_Vector2 coordinate, int width, int height);