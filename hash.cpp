#include "hash.hpp"

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

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"

int hash_sha256(lua_State* L) {
	try {
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);

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
		lua_Sstring str = tm_tostring(L, 1);
		lua_Sstring key = tm_tostring(L, 2);
		lua_Sstring type = lowerString(tm_tostring_s(L, 3, "sha256"));

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


static luaL_Reg TEXTMODULE_HASH_REG[] = {
	{"sha256", hash_sha256},
	{"sha3", hash_sha3},
	{"sha1", hash_sha1},
	{"md5", hash_md5},
	{"keccak", hash_keccak},
	{"crc32", hash_crc32},
	{"hmac", hash_hmac},
	{ nullptr, nullptr }
};

void luaReg_hash(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_HASH_REG);
		lua_setfield(L, -2, name);
	}
}