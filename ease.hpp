#pragma once
#include <lua.hpp>

int ease_linear(lua_State* L);

int ease_inQuad(lua_State* L);
int ease_outQuad(lua_State* L);
int ease_inOutQuad(lua_State* L);
int ease_outInQuad(lua_State* L);

int ease_inCubic(lua_State* L);
int ease_outCubic(lua_State* L);
int ease_inOutCubic(lua_State* L);
int ease_outInCubic(lua_State* L);

int ease_inQuart(lua_State* L);
int ease_outQuart(lua_State* L);
int ease_inOutQuart(lua_State* L);
int ease_outInQuart(lua_State* L);

int ease_inQuint(lua_State* L);
int ease_outQuint(lua_State* L);
int ease_inOutQuint(lua_State* L);
int ease_outInQuint(lua_State* L);

int ease_inSine(lua_State* L);
int ease_outSine(lua_State* L);
int ease_inOutSine(lua_State* L);
int ease_outInSine(lua_State* L);

int ease_inExpo(lua_State* L);
int ease_outExpo(lua_State* L);
int ease_inOutExpo(lua_State* L);
int ease_outInExpo(lua_State* L);

int ease_inCirc(lua_State* L);
int ease_outCirc(lua_State* L);
int ease_inOutCirc(lua_State* L);
int ease_outInCirc(lua_State* L);

int ease_inElastic(lua_State* L);
int ease_outElastic(lua_State* L);
int ease_inOutElastic(lua_State* L);
int ease_outInElastic(lua_State* L);

int ease_inBack(lua_State* L);
int ease_outBack(lua_State* L);
int ease_inOutBack(lua_State* L);
int ease_outInBack(lua_State* L);

int ease_outBounce(lua_State* L);
int ease_inBounce(lua_State* L);
int ease_inOutBounce(lua_State* L);
int ease_outInBounce(lua_State* L);

void luaReg_ease(lua_State* L, const char* name, bool reg);

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