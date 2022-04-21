#pragma once
#include "textmodule_lua.h"

lua_Number range(lua_Number n, lua_Number min, lua_Number max);
lua_Number range(lua_Number n);

lua_Number clamp(lua_Number n, lua_Number min, lua_Number max);
lua_Number clamp(lua_Number n);

lua_Number clamp_s(lua_Number n, lua_Number min, lua_Number max);
lua_Number clamp_s(lua_Number n);

lua_Boolean isinteger(lua_Number n);
lua_Boolean isprime(lua_Integer n);

lua_Number combination(lua_Integer n, lua_Integer r);
lua_Number factorial(lua_Integer n);
lua_Number permutation(lua_Integer n, lua_Integer r);
lua_Number repetition_combination(lua_Integer n, lua_Integer r);
lua_Number repetition_permutation(lua_Integer n, lua_Integer r);
lua_Number circular_permutation(lua_Integer n);

lua_Number bernstein(lua_Number t, lua_Integer n, lua_Integer i);