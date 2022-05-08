#pragma once
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <unicode/unistr.h>
#include <unicode/ustring.h>

std::string WstrToStr(std::wstring str);
std::wstring StrToWstr(std::string str);
std::wstring UstrToWstr(icu::UnicodeString str);
std::string UstrToStr(icu::UnicodeString str);
icu::UnicodeString StrToUstr(std::string str);
icu::UnicodeString WstrToUstr(std::wstring str);

icu::UnicodeString HiraganaToKatakana(icu::UnicodeString str);
icu::UnicodeString KatakanaToHiragana(icu::UnicodeString str);
icu::UnicodeString LatinToHiragana(icu::UnicodeString str);
icu::UnicodeString LatinToKatakana(icu::UnicodeString str);
icu::UnicodeString LatinBGNToHiragana(icu::UnicodeString str);
icu::UnicodeString LatinBGNToKatakana(icu::UnicodeString str);
icu::UnicodeString HiraganaToLatin(icu::UnicodeString str);
icu::UnicodeString KatakanaToLatin(icu::UnicodeString str);
icu::UnicodeString HiraganaToLatinBGN(icu::UnicodeString str);
icu::UnicodeString KatakanaToLatinBGN(icu::UnicodeString str);
icu::UnicodeString HalfwidthToFullwidth(icu::UnicodeString str);
icu::UnicodeString FullwidthToHalfwidth(icu::UnicodeString str);

std::wstring toRoundNumber(std::wstring string, bool invert);

unsigned long long UnicodeToUTF8(unsigned long long code);
unsigned long long UTF8ToUnicode(unsigned long long code);

std::wstring DecToHex(int num);
int HexToDec(std::wstring num);
std::wstring tostring(double num);
std::wstring tostring_n(double num);

std::wstring lowerString(std::wstring type);
std::string lowerString(std::string type);
std::wstring upperString(std::wstring type);
std::string upperString(std::string type);

std::vector<std::wstring> split(std::wstring str, wchar_t del);

void debug_string(std::wstring message);
void debug_string(std::string message);
void debug_string(double message);