#include <lua.hpp>
#include <iostream>

#include "image.h"
#include "textmodule_math.h"
#include "textmodule_color.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"

//WIP

int image_set(lua_State* L) {
	try {
		lua_Image* val = lua_convertcache(L, 1);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int image_getpixel(lua_State* L) {
	try {
		lua_Image* val = tm_toimage(L, 1);
		lua_Integer width = tm_tointeger(L, 2);
		lua_Integer height = tm_tointeger(L, 3);
		lua_Integer x = tm_tointeger(L, 4);
		lua_Integer y = tm_tointeger(L, 5);


		int i = x + width * y;
		if (i > width * height || i < 0)
			throw std::out_of_range(IMAGE_OUT_OF_RANGE);

		lua_pushpixel(L, val[i].r, val[i].g, val[i].b, val[i].a);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int image_setpixel(lua_State* L) {
	try {
		lua_Image* val = tm_toimage(L, 1);
		lua_Integer width = tm_tointeger(L, 2);
		lua_Integer height = tm_tointeger(L, 3);
		lua_Pixel* col = tm_topixel(L, 4);
		lua_Integer x = tm_tointeger(L, 5);
		lua_Integer y = tm_tointeger(L, 6);

		int i = x + width * y;
		if (i > width * height || i < 0)
			throw std::out_of_range(IMAGE_OUT_OF_RANGE);

		val[i].r = col->r;
		val[i].g = col->g;
		val[i].b = col->b;
		val[i].a = col->a;
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_image(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//image
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_IMAGE_REG);
		lua_setfield(L, -2, name);

		//image (metatable)
		luaL_newmetatable(L, TEXTMODULE_IMAGE); //add metatable
		luaL_register(L, NULL, TEXTMODULE_IMAGE_META_REG);

		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_IMAGE_META_REG);
		lua_settable(L, -3);

		lua_pop(L, 1); //remove metatable
	}
}
