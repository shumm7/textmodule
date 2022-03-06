#include <lua.hpp>

#include <filesystem>
#include <iostream>
#include <direct.h>

#include "filesystem.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"
#include "textmodule_exception.h"

int fs_current(lua_State* L) {
	try {
		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TSTRING, 1, "string/none expected");

		if (tp == LUA_TNONE) {
			std::filesystem::path p = std::filesystem::current_path();

			lua_pushsstring(L, p.string());
			return 1;
		}
		else if (tp == LUA_TSTRING) {
			std::filesystem::path p = lua_tostring(L, 1);
			std::filesystem::current_path(p);
			return 0;
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_absolute(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		std::wstring res = std::filesystem::absolute(dir).wstring();
		lua_pushwstring(L, res);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_relative(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		std::wstring res = std::filesystem::relative(dir).wstring();
		lua_pushwstring(L, res);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_proximate(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		std::wstring res = std::filesystem::proximate(dir).wstring();
		lua_pushwstring(L, res);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_canonical(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		std::wstring res = std::filesystem::canonical(dir).wstring();
		lua_pushwstring(L, res);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_create(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		if (std::filesystem::create_directory(dir)) {
			lua_pushboolean(L, true);
		}
		else {
			lua_pushboolean(L, false);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_create_all(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		if (std::filesystem::create_directories(dir)) {
			lua_pushboolean(L, true);
		}
		else {
			lua_pushboolean(L, false);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_exists(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		if (std::filesystem::exists(dir)) {
			lua_pushboolean(L, true);
		}
		else {
			lua_pushboolean(L, false);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_remove(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		if (std::filesystem::remove(dir)) {
			lua_pushboolean(L, true);
		}
		else {
			lua_pushboolean(L, false);
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_remove_all(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		int cnt = static_cast<int>(std::filesystem::remove_all(dir));
		if (cnt>=1) {
			lua_pushboolean(L, true);
			lua_pushinteger(L, cnt);
		}
		else {
			lua_pushboolean(L, false);
			lua_pushinteger(L, 0);
		}

		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_copy(lua_State* L) {
	try {
		std::wstring from = tm_towstring(L, 1);
		std::wstring to = tm_towstring(L, 2);

		int cnt = 3;
		std::filesystem::copy_options options = std::filesystem::copy_options::none;

		while (lua_type(L, cnt) == LUA_TSTRING) {
			std::wstring mode = lua_towstring(L, cnt);

			if (mode == L"none") options = options | std::filesystem::copy_options::none;
			else if (mode == L"skip_existing") options = options | std::filesystem::copy_options::skip_existing;
			else if (mode == L"overwrite_existing") options = options | std::filesystem::copy_options::overwrite_existing;
			else if (mode == L"update_existing") options = options | std::filesystem::copy_options::update_existing;
			else if (mode == L"recursive") options = options | std::filesystem::copy_options::recursive;
			else if (mode == L"copy_symlinks") options = options | std::filesystem::copy_options::copy_symlinks;
			else if (mode == L"skip_symlinks") options = options | std::filesystem::copy_options::skip_symlinks;
			else if (mode == L"directories_only") options = options | std::filesystem::copy_options::directories_only;
			else if (mode == L"create_symlinks") options = options | std::filesystem::copy_options::create_symlinks;
			else if (mode == L"create_hard_links") options = options | std::filesystem::copy_options::create_hard_links;

			cnt++;
		}

		std::filesystem::copy(from, to, options);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_copy_file(lua_State* L) {
	try {
		std::wstring from = tm_towstring(L, 1);
		std::wstring to = tm_towstring(L, 2);

		int cnt = 3;
		std::filesystem::copy_options options = std::filesystem::copy_options::none;

		while (lua_type(L, cnt) == LUA_TSTRING) {
			std::wstring mode = lua_towstring(L, cnt);

			if (mode == L"none") options = options | std::filesystem::copy_options::none;
			else if (mode == L"skip_existing") options = options | std::filesystem::copy_options::skip_existing;
			else if (mode == L"overwrite_existing") options = options | std::filesystem::copy_options::overwrite_existing;
			else if (mode == L"update_existing") options = options | std::filesystem::copy_options::update_existing;
			else if (mode == L"recursive") options = options | std::filesystem::copy_options::recursive;
			else if (mode == L"copy_symlinks") options = options | std::filesystem::copy_options::copy_symlinks;
			else if (mode == L"skip_symlinks") options = options | std::filesystem::copy_options::skip_symlinks;
			else if (mode == L"directories_only") options = options | std::filesystem::copy_options::directories_only;
			else if (mode == L"create_symlinks") options = options | std::filesystem::copy_options::create_symlinks;
			else if (mode == L"create_hard_links") options = options | std::filesystem::copy_options::create_hard_links;

			cnt++;
		}

		std::filesystem::copy_file(from, to, options);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_rename(lua_State* L) {
	try {
		std::wstring from = tm_towstring(L, 1);
		std::wstring to = tm_towstring(L, 2);

		std::filesystem::rename(from, to);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_type(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		std::filesystem::file_type type = std::filesystem::status(dir).type();
		switch (type) {
		case std::filesystem::file_type::none:
			lua_pushstring(L, "none");
			break;
		case std::filesystem::file_type::not_found:
			lua_pushstring(L, "not_found");
			break;
		case std::filesystem::file_type::regular:
			lua_pushstring(L, "regular");
			break;
		case std::filesystem::file_type::directory:
			lua_pushstring(L, "directory");
			break;
		case std::filesystem::file_type::symlink:
			lua_pushstring(L, "symlink");
			break;
		case std::filesystem::file_type::block:
			lua_pushstring(L, "block");
			break;
		case std::filesystem::file_type::character:
			lua_pushstring(L, "character");
			break;
		case std::filesystem::file_type::fifo:
			lua_pushstring(L, "fifo");
			break;
		case std::filesystem::file_type::socket:
			lua_pushstring(L, "socket");
			break;
		case std::filesystem::file_type::unknown:
			lua_pushstring(L, "unknown");
			break;
		default:
			lua_pushstring(L, "implementation-defined");
			break;
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int fs_size(lua_State* L) {
	try {
		std::wstring dir = tm_towstring(L, 1);

		int size = (int)std::filesystem::file_size(dir);
		lua_pushinteger(L, size);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_filesystem(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_FILESYSTEM_REG);
		lua_setfield(L, -2, name);
	}
}