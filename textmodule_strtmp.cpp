#include "textmodule_strtmp.hpp"
#include <stdexcept>
#include <crtdbg.h>
#include <fstream>

void myInvalidParameterHandler(const wchar_t* expression, const wchar_t* function, const wchar_t* file, unsigned int line, uintptr_t pReserved) {
	throw std::invalid_argument(INVALID_FORMAT_STRING);
}

lua_Sstring string_template_format(lua_State* L, lua_Sstring str, int idx) {
	try {
		auto store = fmt::dynamic_format_arg_store<fmt::format_context>();

		lua_formatargs_store(L, &store, idx+1, lua_gettop(L));

		_invalid_parameter_handler oldHandler, newHandler;
		newHandler = myInvalidParameterHandler;
		oldHandler = _set_thread_local_invalid_parameter_handler(newHandler);
		_CrtSetReportMode(_CRT_ASSERT, 0);
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