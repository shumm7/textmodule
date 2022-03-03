#pragma once
#include <lua.hpp>

int hash_sha256(lua_State* L);
int hash_sha3(lua_State* L);
int hash_sha1(lua_State* L);
int hash_md5(lua_State* L);
int hash_keccak(lua_State* L);
int hash_crc32(lua_State* L);
int hash_hmac(lua_State* L);

void luaReg_hash(lua_State* L, const char* name, bool reg);
void luaGlobal_hash(lua_State* L, const char* name, bool reg);

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