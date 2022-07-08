#include "bit.hpp"

#include <lua.hpp>
#include <bit>
#include <bitset>
#include <sstream>

#include "textmodule_lua.hpp"

int bit_lshift(lua_State* L) {
    try {
        if (tm_callmetan(L, 1, "__shl"))
            return 1;

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
        if (tm_callmetan(L, 1, "__shr"))
            return 1;

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
        if (tm_callmetan(L, 1, "__lrot"))
            return 1;

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
        if (tm_callmetan(L, 1, "__rrot"))
            return 1;

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
        if (tm_callmetan(L, 1, "__bnot"))
            return 1;

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
        if (tm_callmetan(L, 1, "__band"))
            return 1;

        lua_Unsigned ret = tm_tounsigned(L, 1) & tm_tounsigned(L, 2);
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
        if (tm_callmetan(L, 1, "__bor"))
            return 1;

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
        if (tm_callmetan(L, 1, "__bxor"))
            return 1;

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

int bit_binary(lua_State* L) {
    try {
        lua_Unsigned v = tm_tounsigned(L, 1);
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
  {"binary", bit_binary},
  {nullptr, nullptr}
};

void luaReg_bit(lua_State* L, lua_Option opt) {
    if (opt["api"]["bit"]) {
        tm_debuglog_apiloaded(opt, "bit");
        lua_newtable(L);
        luaL_register(L, NULL, TEXTMODULE_BIT_REG);
        lua_setfield(L, -2, "bit");
    }
    else {
        tm_debuglog_apinoloaded(opt, "bit");
    }
}