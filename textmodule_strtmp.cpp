#include "textmodule_strtmp.hpp"

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx) {
	try {
		fmt::dynamic_format_arg_store<fmt::format_context> store;

		int i = idx + 1;
		while (true) {
			int tp = lua_type(L, i);

			if (tp == LUA_TNUMBER)
				store.push_back(lua_tonumber(L, i));
			else if (tp == LUA_TBOOLEAN)
				store.push_back(lua_toboolean(L, i));
			else if (tp == LUA_TSTRING)
				store.push_back(lua_tostring(L, i));
			else if (tp == LUA_TNIL)
				store.push_back("nil");
			else if (tp == LUA_TNONE)
				break;
			else if (tp == LUA_TUSERDATA) {
					store.push_back(lua_topointer(L, i));
			}
			else
				store.push_back(lua_topointer(L, i));

			i++;
		};

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