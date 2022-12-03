#include "ease.hpp"

#include <lua.hpp>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_ease.hpp"
#include "textmodule_option.hpp"

int ease_linear(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_linear(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inQuad(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inQuad(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outQuad(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outQuad(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutQuad(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutQuad(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInQuad(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInQuad(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inCubic(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inCubic(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outCubic(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outCubic(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutCubic(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutCubic(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInCubic(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInCubic(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inQuart(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inQuart(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outQuart(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outQuart(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutQuart(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutQuart(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInQuart(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInQuart(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inQuint(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inQuint(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outQuint(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outQuint(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutQuint(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutQuint(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInQuint(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInQuint(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inSine(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inSine(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outSine(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outSine(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutSine(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutSine(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInSine(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInSine(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inExpo(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inExpo(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outExpo(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outExpo(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutExpo(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutExpo(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInExpo(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInExpo(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inCirc(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inCirc(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outCirc(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outCirc(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutCirc(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutCirc(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInCirc(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInCirc(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inElastic(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number a;
		lua_Number p;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_inElastic(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			a = tm_tonumber(L, 5);
			p = tm_tonumber(L, 6);
			lua_pushnumber(L, e_inElastic(t, b, c, d, a, p));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outElastic(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number a;
		lua_Number p;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_outElastic(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			a = tm_tonumber(L, 5);
			p = tm_tonumber(L, 6);
			lua_pushnumber(L, e_outElastic(t, b, c, d, a, p));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutElastic(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number a;
		lua_Number p;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_inOutElastic(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			a = tm_tonumber(L, 5);
			p = tm_tonumber(L, 6);
			lua_pushnumber(L, e_inOutElastic(t, b, c, d, a, p));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInElastic(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number a;
		lua_Number p;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_outInElastic(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			a = tm_tonumber(L, 5);
			p = tm_tonumber(L, 6);
			lua_pushnumber(L, e_outInElastic(t, b, c, d, a, p));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inBack(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number s;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_inBack(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			s = tm_tonumber(L, 5);
			lua_pushnumber(L, e_inBack(t, b, c, d, s));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outBack(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number s;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_outBack(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			s = tm_tonumber(L, 5);
			lua_pushnumber(L, e_outBack(t, b, c, d, s));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutBack(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number s;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_inOutBack(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			s = tm_tonumber(L, 5);
			lua_pushnumber(L, e_inOutBack(t, b, c, d, s));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInBack(lua_State* L) {
	try {
		lua_Number t;
		lua_Number b;
		lua_Number c;
		lua_Number d;
		lua_Number s;

		switch (lua_gettop(L)) {
		case 3:
		case 4:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber_s(L, 4, 1);
			lua_pushnumber(L, e_outInBack(t, b, c, d));
			return 1;
		default:
			t = tm_tonumber(L, 1);
			b = tm_tonumber(L, 2);
			c = tm_tonumber(L, 3);
			d = tm_tonumber(L, 4);
			s = tm_tonumber(L, 5);
			lua_pushnumber(L, e_outInBack(t, b, c, d, s));
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int ease_inBounce(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inBounce(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outBounce(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outBounce(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_inOutBounce(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_inOutBounce(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}
int ease_outInBounce(lua_State* L) {
	try {
		lua_Number t = tm_tonumber(L, 1);
		lua_Number b = tm_tonumber(L, 2);
		lua_Number c = tm_tonumber(L, 3);
		lua_Number d = tm_tonumber_s(L, 4, 1);

		lua_pushnumber(L, e_outInBounce(t, b, c, d));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_EASE_REG[] = {
	{"linear", ease_linear},

	{"inQuad", ease_inQuad},
	{"outQuad", ease_outQuad},
	{"inOutQuad", ease_inOutQuad},
	{"outInQuad", ease_outInQuad},

	{"inCubic", ease_inCubic},
	{"outCubic", ease_outCubic},
	{"inOutCubic", ease_inOutCubic},
	{"outInCubic", ease_outInCubic},

	{"inQuart", ease_inQuart},
	{"outQuart", ease_outQuart},
	{"inOutQuart", ease_inOutQuart},
	{"outInQuart", ease_outInQuart},

	{"inQuint", ease_inQuint},
	{"outQuint", ease_outQuint},
	{"inOutQuint", ease_inOutQuint},
	{"outInQuint", ease_outInQuint},

	{"inSine", ease_inSine},
	{"outSine", ease_outSine},
	{"inOutSine", ease_inOutSine},
	{"outInSine", ease_outInSine},

	{"inExpo", ease_inExpo},
	{"outExpo", ease_outExpo},
	{"inOutExpo", ease_inOutExpo},
	{"outInExpo", ease_outInExpo},

	{"inCirc", ease_inCirc},
	{"outCirc", ease_outCirc},
	{"inOutCirc", ease_inOutCirc},
	{"outInCirc", ease_outInCirc},

	{"inElastic", ease_inElastic},
	{"outElastic", ease_outElastic},
	{"inOutElastic", ease_inOutElastic},
	{"outInElastic", ease_outInElastic},

	{"inBack", ease_inBack},
	{"outBack", ease_outBack},
	{"inOutBack", ease_inOutBack},
	{"outInBack", ease_outInBack},

	{"outBounce", ease_outBounce},
	{"inBounce", ease_inBounce},
	{"inOutBounce", ease_inOutBounce},
	{"outInBounce", ease_outInBounce},

	{nullptr, nullptr}
};

void luaReg_ease(lua_State* L, lua_Option opt) {
	if (opt["api"]["ease"]) {
		tm_debuglog_apiloaded(opt, "ease");

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_EASE_REG);
		lua_setfield(L, -2, "ease");
	}
	else {
		tm_debuglog_apinoloaded(opt, "ease");
	}
}