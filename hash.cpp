#include <lua.hpp>
#include <iostream>
#include <algorithm>

#include "hash-library/sha256.h"
#include "hash-library/sha3.h"
#include "hash-library/sha1.h"
#include "hash-library/md5.h"
#include "hash-library/keccak.h"
#include "hash-library/crc32.h"
#include "hash-library/hmac.h"

#include "hash.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

int hash_sha256(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		SHA256 hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_sha3(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		SHA3 hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_sha1(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		SHA1 hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_md5(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		MD5 hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_keccak(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		Keccak hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_crc32(lua_State* L) {
	try {
		std::string str;
		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		CRC32 hash;
		lua_pushsstring(L, hash(str));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int hash_hmac(lua_State* L) {
	try {
		std::string str;
		std::string key;
		std::string type;

		if (lua_type(L, 1) == LUA_TSTRING) {
			str = lua_tostring(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TSTRING) {
			key = lua_tostring(L, 2);
		}
		else {
			return 0;
		}

		if (lua_type(L, 3) == LUA_TSTRING) {
			type = lowerString(lua_tostring(L, 3));
		}
		else {
			return 0;
		}

		if (type == "sha256") {
			lua_pushsstring(L, hmac<SHA256>(str, key));
		}
		else if (type == "sha1") {
			lua_pushsstring(L, hmac<SHA1>(str, key));
		}
		else if (type == "md5") {
			lua_pushsstring(L, hmac<MD5>(str, key));
		}
		else {
			return 0;
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_hash(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HASH_REG);
		lua_setfield(L, -2, name);
	}
}

void luaGlobal_hash(lua_State* L, const char* name, bool reg) {
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_HASH_REG);
	lua_setglobal(L, name);
}