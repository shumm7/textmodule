#include <lua.hpp>
#include <bit>
#include <bitset>
#include <sstream>

#include "bit.h"
#include "textmodule_lua.h"

int bit_lshift(lua_State* L) {
    try {
        lua_pushnumber(L, tm_tounsigned(L, 1) << tm_tointeger(L, 2));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_rshift(lua_State* L) {
    try {
        lua_pushnumber(L, tm_tounsigned(L, 1) >> tm_tointeger(L, 2));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_lrotate(lua_State* L) {
    try {
        lua_pushnumber(L, std::rotl(tm_tounsigned(L, 1), tm_tointeger(L, 2)));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_rrotate(lua_State* L) {
    try {
        lua_pushnumber(L, std::rotr(tm_tounsigned(L, 1), tm_tointeger(L, 2)));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_not(lua_State* L) {
    try {
        lua_pushnumber(L, ~tm_tounsigned(L, 1));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_and(lua_State* L) {
    try {
        unsigned long ret = tm_tounsigned(L, 1) & tm_tounsigned(L, 2);
        int idx = 3;
        while (lua_type(L, idx) == LUA_TNUMBER) {
            ret = ret & tm_tounsigned(L, 3);
            idx++;
        }

        lua_pushnumber(L, ret);
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_or(lua_State* L) {
    try {
        unsigned long ret = tm_tounsigned(L, 1) | tm_tounsigned(L, 2);
        int idx = 3;
        while (lua_type(L, idx) == LUA_TNUMBER) {
            ret = ret | tm_tounsigned(L, 3);
            idx++;
        }

        lua_pushnumber(L, ret);
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_xor(lua_State* L) {
    try {
        unsigned long ret = tm_tounsigned(L, 1) ^ tm_tounsigned(L, 2);
        int idx = 3;
        while (lua_type(L, idx) == LUA_TNUMBER) {
            ret = ret ^ tm_tounsigned(L, 3);
            idx++;
        }

        lua_pushnumber(L, ret);
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_ceil(lua_State* L) {
    try {
        lua_pushnumber(L, std::bit_ceil(tm_tounsigned(L, 1)));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_floor(lua_State* L) {
    try {
        lua_pushnumber(L, std::bit_floor(tm_tounsigned(L, 1)));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_popcount(lua_State* L) {
    try {
        lua_pushnumber(L, std::popcount(tm_tounsigned(L, 1)));
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int bit_string(lua_State* L) {
    try {
        unsigned long v = tm_tounsigned(L, 1);
        std::wstringstream ss;
        ss << std::bitset<sizeof(v) * CHAR_BIT>(v);

        lua_pushwstring(L, L"0b"+ss.str());
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

void luaReg_bit(lua_State* L, const char* name, bool reg) {
    if (reg) {
        lua_newtable(L);
        luaL_register(L, NULL, TEXTMODULE_BIT_REG);
        lua_setfield(L, -2, name);
    }
}