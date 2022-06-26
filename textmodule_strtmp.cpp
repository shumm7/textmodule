#include "textmodule_strtmp.hpp"

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx) {
	try {
		fmt::dynamic_format_arg_store<fmt::format_context> store;

		lua_formatargs_store(L, &store, idx+1, lua_gettop(L));

		return fmt::vformat(str, store);
	}
	catch (fmt::format_error) {
		return str;
	}
}

lua_Wstring string_template_format(lua_State* L, lua_Wstring str, int idx) {
	return StrToWstr(string_template_format(L, WstrToStr(str), idx));
}

int string_dump_writer(lua_State* L, const void* b, size_t size, void* B) {
	(void)L;
	luaL_addlstring((luaL_Buffer*)B, (const char*)b, size);
	return 0;
}

luaL_Buffer* string_template_dump(lua_State* L) {
	luaL_Buffer b;
	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_settop(L, 1);
	luaL_buffinit(L, &b);
	if (lua_dump(L, string_dump_writer, &b) != 0)
		luaL_error(L, "unable to dump given function");
	return &b;
}