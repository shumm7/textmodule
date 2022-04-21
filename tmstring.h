#pragma once
#include <lua.hpp>

#define S_NUMBER "0123456789"
#define S_HEX_DIGITS "0123456789abcdefABCDEF"
#define S_ALPHABET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define S_SMALL_ALPHABET "abcdefghijklmnopqrstuvwxyz"
#define S_CAPITAL_ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define S_ALPHABET_NUMBER "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
#define S_FULL_NUMBER "�O�P�Q�R�S�T�U�V�W�X"
#define S_FULL_ALPHABET "�����������������������������������������������������`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y"
#define S_FULL_SMALL_ALPHABET "����������������������������������������������������"
#define S_FULL_CAPITAL_ALPHABET "�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y"
#define S_FULL_ALPHABET_NUMBER "�����������������������������������������������������`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�O�P�Q�R�S�T�U�V�W�X"
#define S_SYMBOL "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
#define S_ASCII "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
#define S_HALF_KATAKANA "����������������������������������������������������������"
#define S_KATAKANA "�@�A�B�C�D�E�F�G�H�I�J�K�L�M�N�O�P�Q�R�S�T�U�V�W�X�Y�Z�[�\�]�^�_�`�a�b�c�d�e�f�g�h�i�j�k�l�m�n�o�p�q�r�s�t�u�v�w�x�y�z�{�|�}�~����������������������������������������������"
#define S_HIRAGANA "�����������������������������������������������������������������������ÂĂłƂǂȂɂʂ˂̂͂΂ςЂт҂ӂԂՂւׂ؂قڂۂ܂݂ނ߂��������������������"
#define S_HIRAGANA_N "�����������������������������������ĂƂȂɂʂ˂̂͂Ђӂւق܂݂ނ߂��������������"
#define S_IROHA "	����͂ɂقւƂ���ʂ���킩�悽�ꂻ�˂Ȃ�ނ���̂�����܂��ӂ����Ă�������߂݂���Ђ�������"
#define S_QUICK_BROWN_FOX "The quick brown fox jumps over the lazy dog"
#define S_PIPE "����������������������������������������������������������������"
#define S_LOREM_IPSUM "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
#define S_POLANO "���̃C�[�n�g�[���H�̂����Ƃ��������A�Ăł���ɗ₽������������A���������X�ŏ���ꂽ�����[�I�s�A�x�O�̂��炬��Ђ��鑐�̔g�B"

int tmstring_hiragana(lua_State* L);
int tmstring_katakana(lua_State* L);
int tmstring_halfwidth(lua_State* L);
int tmstring_fullwidth(lua_State* L);
int tmstring_mojibake(lua_State* L);

int tmstring_swapcase(lua_State* L);
int tmstring_left(lua_State* L);
int tmstring_right(lua_State* L);
int tmstring_cshift(lua_State* L);
int tmstring_wcshift(lua_State* L);
int tmstring_squeeze(lua_State* L);
int tmstring_capitalize(lua_State* L);
int tmstring_capitalize_words(lua_State* L);
int tmstring_random(lua_State* L);
int tmstring_roundnumber(lua_State* L);
int tmstring_anagram(lua_State* L);

void luaReg_tmstring(lua_State* L, const char* name, bool reg);

static luaL_Reg TEXTMODULE_TMSTRING_REG[] = {
	{"hiragana", tmstring_hiragana},
	{"katakana", tmstring_katakana},
	{"halfwidth", tmstring_halfwidth},
	{"fullwidth", tmstring_fullwidth},
	{"mojibake", tmstring_mojibake},
	{"swapcase", tmstring_swapcase},
	{"left", tmstring_left},
	{"right", tmstring_right},
	{"cshift", tmstring_cshift},
	{"wcshift", tmstring_wcshift},
	{"squeeze", tmstring_squeeze},
	{"capitalize", tmstring_capitalize},
	{"capitalize_words", tmstring_capitalize_words},
	{"random", tmstring_random},
	{"roundnumber",  tmstring_roundnumber},
	{"anagram", tmstring_anagram},
	{ nullptr, nullptr }
};