#include "u8.hpp"

#include <lua.hpp>
#include "textmodule_lua.hpp"

#define MAXUNICODE 0x10FFFFu
#define MAXUTF 0x7FFFFFFFu
#define iscont(p) ((*(p) & 0xC0) == 0x80)

const char* u8_decode(const char* s, unsigned int* val, int strict) {
    static const unsigned int limits[] =
    { ~(unsigned int)0, 0x80, 0x800, 0x10000u, 0x200000u, 0x4000000u };
    unsigned int c = (unsigned char)s[0];
    unsigned int res = 0;  /* final result */
    if (c < 0x80)  /* ascii? */
        res = c;
    else {
        int count = 0;  /* to count number of continuation bytes */
        for (; c & 0x40; c <<= 1) {  /* while it needs continuation bytes... */
            unsigned int cc = (unsigned char)s[++count];  /* read next byte */
            if ((cc & 0xC0) != 0x80)  /* not a continuation byte? */
                return NULL;  /* invalid byte sequence */
            res = (res << 6) | (cc & 0x3F);  /* add lower 6 bits from cont. byte */
        }
        res |= ((unsigned int)(c & 0x7F) << (count * 5));  /* add first byte */
        if (count > 5 || res > MAXUTF || res < limits[count])
            return NULL;  /* invalid byte sequence */
        s += count;  /* skip continuation bytes read */
    }
    if (strict) {
        /* check for invalid code points; too large or surrogates */
        if (res > MAXUNICODE || (0xD800u <= res && res <= 0xDFFFu))
            return NULL;
    }
    if (val) *val = res;
    return s + 1;  /* +1 to include first byte */
}

lua_Integer u8_posrelat(lua_Integer pos, size_t len) {
    if (pos >= 0) return pos;
    else if (0u - (size_t)pos > len) return 0;
    else return (lua_Integer)len + pos + 1;
}

void u8_pushutfchar(lua_State* L, int arg) {
    lua_Unsigned code = (lua_Unsigned)luaL_checkinteger(L, arg);
    luaL_argcheck(L, code <= MAXUTF, arg, "value out of range");
    lua_pushfstring(L, "%U", (long)code);
}

int u8_iter_aux(lua_State* L, int strict) {
    size_t len;
    const char* s = luaL_checklstring(L, 1, &len);
    lua_Unsigned n = (lua_Unsigned)lua_tointeger(L, 2);
    if (n < len) {
        while (iscont(s + n)) n++;  /* skip continuation bytes */
    }
    if (n >= len)  /* (also handles original 'n' being negative) */
        return 0;  /* no more codepoints */
    else {
        unsigned int code;
        const char* next = u8_decode(s + n, &code, strict);
        if (next == NULL)
            return luaL_error(L, "invalid UTF-8 code");
        lua_pushinteger(L, n + 1);
        lua_pushinteger(L, code);
        return 2;
    }
}

int u8_iter_auxstrict(lua_State* L) {
    return u8_iter_aux(L, 1);
}

int u8_iter_auxlax(lua_State* L) {
    return u8_iter_aux(L, 0);
}

std::string u8_charpattern() {
    std::u8string pattern = u8"[\0-\x7F\xC2-\xFD][\x80-\xBF]*";
    std::string ret;
    for (int i = 0; i < pattern.size(); i++)
        ret += pattern[i];
    return ret.c_str();
}


int u8_offset(lua_State* L) {
    try {
        size_t len;
        const char* s = luaL_checklstring(L, 1, &len);
        lua_Integer n = luaL_checkinteger(L, 2);
        lua_Integer posi = (n >= 0) ? 1 : len + 1;
        posi = u8_posrelat(luaL_optinteger(L, 3, posi), len);
        luaL_argcheck(L, 1 <= posi && --posi <= (lua_Integer)len, 3,
            "position out of bounds");
        if (n == 0) {
            /* find beginning of current byte sequence */
            while (posi > 0 && iscont(s + posi)) posi--;
        }
        else {
            if (iscont(s + posi))
                return luaL_error(L, "initial position is a continuation byte");
            if (n < 0) {
                while (n < 0 && posi > 0) {  /* move back */
                    do {  /* find beginning of previous character */
                        posi--;
                    } while (posi > 0 && iscont(s + posi));
                    n++;
                }
            }
            else {
                n--;  /* do not move for 1st character */
                while (n > 0 && posi < (lua_Integer)len) {
                    do {  /* find beginning of next character */
                        posi++;
                    } while (iscont(s + posi));  /* (cannot pass final '\0') */
                    n--;
                }
            }
        }
        if (n == 0)  /* did it find given character? */
            lua_pushinteger(L, posi + 1);
        else  /* no such character */
            lua_pushnil(L);
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int u8_codepoint(lua_State* L) {
    try {
        size_t len;
        const char* s = luaL_checklstring(L, 1, &len);
        lua_Integer posi = u8_posrelat(luaL_optinteger(L, 2, 1), len);
        lua_Integer pose = u8_posrelat(luaL_optinteger(L, 3, posi), len);
        int lax = lua_toboolean(L, 4);
        int n;
        const char* se;
        luaL_argcheck(L, posi >= 1, 2, "out of bounds");
        luaL_argcheck(L, pose <= (lua_Integer)len, 3, "out of bounds");
        if (posi > pose) return 0;  /* empty interval; return no values */
        if (pose - posi >= INT_MAX)  /* (lua_Integer -> int) overflow? */
            return luaL_error(L, "string slice too long");
        n = (int)(pose - posi) + 1;  /* upper bound for number of returns */
        luaL_checkstack(L, n, "string slice too long");
        n = 0;  /* count the number of returns */
        se = s + pose;  /* string end */
        for (s += posi - 1; s < se;) {
            unsigned int code;
            s = u8_decode(s, &code, !lax);
            if (s == NULL)
                return luaL_error(L, "invalid UTF-8 code");
            lua_pushinteger(L, code);
            n++;
        }
        return n;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int u8_char(lua_State* L) {
    try {
        int n = lua_gettop(L);  /* number of arguments */
        if (n == 1)  /* optimize common case of single char */
            u8_pushutfchar(L, 1);
        else {
            int i;
            luaL_Buffer b;
            luaL_buffinit(L, &b);
            for (i = 1; i <= n; i++) {
                u8_pushutfchar(L, i);
                luaL_addvalue(&b);
            }
            luaL_pushresult(&b);
        }
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int u8_len(lua_State* L) {
    try {
        lua_Integer n = 0;  /* counter for the number of characters */
        size_t len;  /* string length in bytes */
        const char* s = luaL_checklstring(L, 1, &len);
        lua_Integer posi = u8_posrelat(luaL_optinteger(L, 2, 1), len);
        lua_Integer posj = u8_posrelat(luaL_optinteger(L, 3, -1), len);
        int lax = lua_toboolean(L, 4);
        luaL_argcheck(L, 1 <= posi && --posi <= (lua_Integer)len, 2,
            "initial position out of bounds");
        luaL_argcheck(L, --posj < (lua_Integer)len, 3,
            "final position out of bounds");
        while (posi <= posj) {
            const char* s1 = u8_decode(s + posi, NULL, !lax);
            if (s1 == NULL) {  /* conversion error? */
                lua_pushnil(L);  /* return fail ... */
                lua_pushinteger(L, posi + 1);  /* ... and current position */
                return 2;
            }
            posi = s1 - s;
            n++;
        }
        lua_pushinteger(L, n);
        return 1;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}

int u8_codes(lua_State* L) {
    try {
        int lax = lua_toboolean(L, 2);
        luaL_checkstring(L, 1);
        lua_pushcfunction(L, lax ? u8_iter_auxlax : u8_iter_auxstrict);
        lua_pushvalue(L, 1);
        lua_pushinteger(L, 0);
        return 3;
    }
    catch (std::exception& e) {
        luaL_error(L, e.what());
        return 1;
    }
}


void luaReg_u8(lua_State* L, const char* name, bool reg) {
    if (reg) {
        lua_newtable(L);
        luaL_register(L, NULL, TEXTMODULE_U8_REG);

        std::string UTF8PATT = u8_charpattern();
        lua_pushlstring(L, UTF8PATT.c_str(), sizeof(UTF8PATT) / sizeof(char) - 1);
        lua_setfield(L, -2, "charpattern");

        lua_setfield(L, -2, name);
    }
}