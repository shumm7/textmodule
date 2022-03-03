#pragma once
#include <iostream>
#include <vector>

std::string WstrToStr(std::wstring str);
std::wstring StrToWstr(std::string str);

std::wstring _jreplace(std::wstring String1, std::wstring String2, std::wstring String3, bool invert);
unsigned long long UnicodeToUTF8(unsigned long long code);
unsigned long long UTF8ToUnicode(unsigned long long code);
std::wstring toKatakana(std::wstring string, bool invert);
std::wstring toHalfwidth(std::wstring string, bool invert, bool space);

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