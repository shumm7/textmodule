#include "textmodule_image.hpp"

#include <iostream>
#include <utility>
#include <cstdio>
#include <memory>
#include <windows.h>

#include "textmodule_exception.hpp"
#include "textmodule_lua.hpp"

// Image
/*
lua_Cache* lua_tocache(lua_State* L, int idx) {;
	return reinterpret_cast<lua_Cache*>(lua_touserdata(L, idx));
}

lua_Cache* tm_tocache(lua_State* L, int idx) {
	if (!lua_isuserdata(L, idx)) luaL_argerror(L, idx, "userdata expected");
	return lua_tocache(L, idx);
}

lua_Image* lua_toimage(lua_State* L, int idx) {
	return reinterpret_cast<lua_Image*>(luaL_checkudata(L, idx, TEXTMODULE_IMAGE));
}

lua_Image* tm_toimage(lua_State* L, int idx) {
	int tp = lua_type(L, idx);
	luaL_argcheck(L, (tp == LUA_TUSERDATA && luaL_checkmetatable(L, idx, TEXTMODULE_IMAGE)), idx, "image expected");
	return lua_toimage(L, idx);
}

lua_Image* lua_newimage(lua_State* L, int width, int height) {
	std::unique_ptr<st_imgpixel[]> data = std::make_unique<st_imgpixel[]>(width * height);

	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			data[x + y * width] = { 0, 0, 0, 0 };

	lua_Image img{ data.get(), width, height };
	return &img;
}


lua_Image* lua_pushimage(lua_State* L, lua_Image image) {
	lua_Image* ret = reinterpret_cast<lua_Image*>(lua_newuserdata(L, sizeof(lua_Image)));
	luaL_getmetatable(L, TEXTMODULE_IMAGE);
	lua_setmetatable(L, -2);

	ret->image = image.image;
	ret->width = image.width;
	ret->height = image.height;
	return ret;
}

void lua_copytocache(lua_State* L, lua_Cache* dest, int width, int height, lua_Image* image) {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			int i = get_imgindex(lua_Vector2(x, y), width, height);

			if (image->width <= x || image->height <= y) {
				dest[i].b = 0;
				dest[i].g = 0;
				dest[i].r = 0;
				dest[i].a = 0;
			}
			else {
				dest[i].b = image->image[i].b;
				dest[i].g = image->image[i].g;
				dest[i].r = image->image[i].r;
				dest[i].a = image->image[i].a;
			}
		}
	}
}

void lua_copyfromcache(lua_State* L, lua_Image* dest, lua_Cache* cache, int width, int height) {
	for (int x = 0; x < dest->width; x++) {
		for (int y = 0; y < dest->height; y++) {
			int i = get_imgindex_s(lua_Vector2(x, y), width, height);

			if (i == -1) {
				dest->image[i].b = 0;
				dest->image[i].g = 0;
				dest->image[i].r = 0;
				dest->image[i].a = 0;
			}
			else {
				dest->image[i].b = cache[i].b;
				dest->image[i].g = cache[i].g;
				dest->image[i].r = cache[i].r;
				dest->image[i].a = cache[i].a;
			}
		}
	}
}


int get_imgindex(lua_Vector2 coordinate, int width, int height) {
	int i = (coordinate.x() - 1) + width * (coordinate.y() - 1);
	if (width * height <= i || i < 0)
		throw std::overflow_error(IMAGE_OUT_OF_RANGE);
	return i;
}

int get_imgindex_s(lua_Vector2 coordinate, int width, int height) {
	int i = (coordinate.x() - 1) + width * (coordinate.y() - 1);
	if (width * height <= i || i < 0)
		return -1;
	return i;
}
*/