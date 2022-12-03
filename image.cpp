#include "image.hpp"

#include <lua.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "textmodule_image.hpp"
#include "textmodule_math.hpp"
#include "textmodule_color.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_option.hpp"

/*
int image_new(lua_State* L) {
	try {
		int width = tm_tointeger(L, 1);
		int height = tm_tointeger(L, 2);
		lua_Pixel pixel = *tm_topixel_s(L, 3, lua_Pixel{.r=0, .g=0, .b=0, .a=0});

		lua_Image* img = lua_newimage(L, width, height);
		lua_pushimage(L, *img);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int image_imread(lua_State* L) {
	try {
		lua_Sstring dir = tm_tosstring(L, 1);
		cv::Mat picture = cv::imread(dir, -1);

		cv::Size s = picture.size();
		lua_Image* img = lua_newimage(L, s.width, s.height);

		for (int x = 0; x < s.width; x++) {
			for (int y = 0; y < s.height; y++) {
				int i = get_imgindex(lua_Vector2(x, y), s.width, s.height);
				img->image[i].b = picture.at<cv::Vec3b>(y, x)[0];
				img->image[i].g = picture.at<cv::Vec3b>(y, x)[1];
				img->image[i].r = picture.at<cv::Vec3b>(y, x)[2];
				img->image[i].a = picture.at<cv::Vec3b>(y, x)[3];
			}
		}

		lua_pushimage(L, *img);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int image_input(lua_State* L) {
	try {
		lua_Cache* cache = tm_tocache(L, 1);
		int width = tm_tointeger(L, 2);
		int height = tm_tointeger(L, 3);
		lua_Image* image = tm_toimage(L, 4);

		lua_copyfromcache(L, image, cache, width, height);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int image_output(lua_State* L) {
	try {
		lua_Image* image = tm_toimage(L, 1);
		lua_Cache* cache = tm_tocache(L, 2);
		int width = tm_tointeger(L, 3);
		int height = tm_tointeger(L, 4);

		lua_copytocache(L, cache, width, height, image);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int image_show(lua_State* L) {
	try {
		lua_Image* img = tm_toimage(L, 1);
		lua_Sstring wnd = tm_tosstring_s(L, 2, "");

		cv::Mat mat = cv::Mat::zeros(img->height, img->width, CV_8UC4);
		cv::Size s = mat.size();
		for (int x = 0; x < s.width; x++) {
			for (int y = 0; y < s.height; y++) {
				int i = get_imgindex(lua_Vector2(x, y), s.width, s.height);
				mat.at<cv::Vec3b>(y, x)[0] = img->image[i].b;
				img->image[i].g = picture.at<cv::Vec3b>(y, x)[1];
				img->image[i].r = picture.at<cv::Vec3b>(y, x)[2];
				img->image[i].a = picture.at<cv::Vec3b>(y, x)[3];
			}
		}

		cv::imshow(wnd, mat);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
*/

static luaL_Reg TEXTMODULE_IMAGE_REG[] = {
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_IMAGE_META_REG[] = {
	{ nullptr, nullptr }
};

void luaReg_image(lua_State* L, lua_Option opt) {
	if (opt["api"]["color"]["image"]) {
		tm_debuglog_apiloaded(opt, "image");
		luaL_newmetatable(L, TEXTMODULE_IMAGE, TEXTMODULE_IMAGE_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_IMAGE_REG);
		lua_setfield(L, -2, "image");
	}
	else {
		tm_debuglog_apinoloaded(opt, "image");
	}
}
