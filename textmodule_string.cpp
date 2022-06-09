#include "textmodule_string.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <codecvt>

#include <windows.h>
#include <atlconv.h>

#include <unicode/datefmt.h>
#include <unicode/dtfmtsym.h>
#include <unicode/gregocal.h>
#include <unicode/timezone.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>
#include <unicode/dtptngen.h>
#include <unicode/dtitvfmt.h>
#include <unicode/translit.h>
#include <unicode/ucnv.h>

#include <boost/shared_ptr.hpp>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "textmodule_exception.hpp"
#include "textmodule_type.hpp"

#pragma comment(lib, "atls.lib")
#pragma comment(lib, "afxnmcd.lib")
#pragma comment(lib, "icuuc.lib")

#define isU16charLowSurrogate(ch) (0xDC00 <= ch && ch < 0xE000)
#define isU16charHighSurrogate(ch) (0xD800 <= ch && ch < 0xDC00)

using namespace icu;

//ワイド文字 - マルチバイト文字　相互変換
std::string WstrToStr(std::wstring str) {
	USES_CONVERSION_EX;

	const auto pwstr = W2A_EX(str.c_str(), str.length());
	if (pwstr != NULL) {
		std::string dst(pwstr);
		return dst;
	}
	throw std::runtime_error("string conversion failed");
}

std::wstring StrToWstr(std::string str) {
	USES_CONVERSION_EX;

	const auto pwstr = A2W_EX(str.c_str(), str.length());
	if (pwstr != NULL) {
		std::wstring dst(pwstr);
		return dst;
	}
	throw std::runtime_error(STRING_COVERSION_FAILED);
}

std::string UstrToStr(icu::UnicodeString str) {
	int length = str.extract(0, str.length(), NULL, "shift_jis");

	std::vector<char> result(length + 1);
	str.extract(0, str.length(), &result[0], "shift_jis");

	return std::string(result.begin(), result.end() - 1);
}

std::wstring UstrToWstr(icu::UnicodeString str) {

	return StrToWstr(UstrToStr(str));
}

icu::UnicodeString StrToUstr(std::string str) {
	return icu::UnicodeString(str.c_str());
}

icu::UnicodeString WstrToUstr(std::wstring str) {
	return icu::UnicodeString(str.c_str());
}

std::u8string StrToU8str(std::string str) {
	icu::UnicodeString d(str.c_str(), "shift_jis");
	int length = d.extract(0, str.length(), NULL, "utf8");

	std::vector<char> result(length + 1);
	d.extract(0, str.length(), &result[0], "utf8");

	return std::u8string(result.begin(), result.end() - 1);
}

std::u8string WstrToU8str(std::wstring str) {
	return StrToU8str(WstrToStr(str));
}

std::string U8strToStr(std::u8string str) {
	icu::UnicodeString d((const char*)str.c_str(), "utf8");
	int length = d.extract(0, str.length(), NULL, "shift_jis");

	std::vector<char> result(length + 1);
	d.extract(0, str.length(), &result[0], "shift_jis");

	return std::string(result.begin(), result.end() - 1);
}

std::wstring U8strToWstr(std::u8string str) {
	return StrToWstr(U8strToStr(str));
}

bool convU32charToU16char(const char32_t u32Ch, std::array<char16_t, 2>& u16Ch) {
	if (u32Ch < 0 || u32Ch > 0x10FFFF) {
		return false;
	}

	if (u32Ch < 0x10000) {
		u16Ch[0] = char16_t(u32Ch);
		u16Ch[1] = 0;
	}
	else {
		u16Ch[0] = char16_t((u32Ch - 0x10000) / 0x400 + 0xD800);
		u16Ch[1] = char16_t((u32Ch - 0x10000) % 0x400 + 0xDC00);
	}

	return true;
}

bool convU16charToU32char(const std::array<char16_t, 2>& u16Ch, char32_t& u32Ch) {
	if (isU16charHighSurrogate(u16Ch[0])) {
		if (isU16charLowSurrogate(u16Ch[1])) {
			u32Ch = 0x10000 + (char32_t(u16Ch[0]) - 0xD800) * 0x400 +
				(char32_t(u16Ch[1]) - 0xDC00);
		}
		else if (u16Ch[1] == 0) {
			u32Ch = u16Ch[0];
		}
		else {
			return false;
		}
	}
	else if (isU16charLowSurrogate(u16Ch[0])) {
		if (u16Ch[1] == 0) {
			u32Ch = u16Ch[0];
		}
		else {
			return false;
		}
	}
	else {
		u32Ch = u16Ch[0];
	}

	return true;
}

std::u32string StrToU32str(std::string str) {
	return WstrToU32str(StrToWstr(str));
}

std::u32string WstrToU32str(std::wstring str) {
	std::u32string ret;

	for (auto u16It = str.begin(); u16It != str.end(); ++u16It) {
		std::array<char16_t, 2> u16Ch;
		if (isU16charHighSurrogate((*u16It))) {
			u16Ch[0] = (*u16It);
			++u16It;
			if (u16It == str.end())
				throw std::runtime_error(STRING_COVERSION_FAILED);

			u16Ch[1] = (*u16It);
		}
		else {
			u16Ch[0] = (*u16It);
			u16Ch[1] = 0;
		}

		char32_t u32Ch;
		if (!convU16charToU32char(u16Ch, u32Ch))
			throw std::runtime_error(STRING_COVERSION_FAILED);

		ret.push_back(u32Ch);
	}

	return ret;
}

std::string U32strToStr(std::u32string str) {
	return WstrToStr(U32strToWstr(str));
}

std::wstring U32strToWstr(std::u32string str) {
	std::wstring ret;

	for (auto u32It = str.begin(); u32It != str.end(); ++u32It) {
		std::array<char16_t, 2> u16Ch;
		if (!convU32charToU16char((*u32It), u16Ch))
			throw std::runtime_error(STRING_COVERSION_FAILED);

		if (u16Ch[0] != 0)
			ret.push_back(u16Ch[0]);
		if (u16Ch[1] != 0)
			ret.push_back(u16Ch[1]);
	}
	return ret;
}

std::string StrToEUCstr(std::string str) {
	icu::UnicodeString d(str.c_str(), "shift_jis");
	int length = d.extract(0, str.length(), NULL, "euc_jp");

	std::vector<char> result(length + 1);
	d.extract(0, str.length(), &result[0], "euc_jp");

	return std::string(result.begin(), result.end() - 1);
}

std::string EUCstrToStr(std::string str) {
	icu::UnicodeString d(str.c_str(), "euc_jp");
	int length = d.extract(0, str.length(), NULL, "shift_jis");

	std::vector<char> result(length + 1);
	d.extract(0, str.length(), &result[0], "shift_jis");

	return std::string(result.begin(), result.end() - 1);
}


//置換
std::wstring _jreplace(std::wstring String1, std::wstring String2, std::wstring String3, bool invert)
{
	if (invert) {
		std::wstring temp = String3;
		String3 = String2;
		String2 = temp;
	}

	std::string::size_type  Pos(String1.find(String2));

	while (Pos != std::string::npos)
	{
		String1.replace(Pos, String2.length(), String3);
		Pos = String1.find(String2, Pos + String3.length());
	}

	return String1;
}

icu::UnicodeString StrTransliterate(icu::UnicodeString str, const char* conversion) {
	UErrorCode status = U_ZERO_ERROR;
	boost::shared_ptr<Transliterator> trans(
		Transliterator::createInstance(conversion, UTRANS_FORWARD, status)
	);
	trans->transliterate(str);

	return str;
}



unsigned long long UnicodeToUTF8(unsigned long long code) {

	std::string bin;
	unsigned int mask = (int)1 << (sizeof(unsigned int) * CHAR_BIT - 1);
	do bin += (mask & code ? '1' : '0');
	while (mask >>= 1);
	int m = bin.size();

	std::string ret;

	if (0x0000 <= code && code <= 0x007F) {
		ret = "0" + bin.substr(m - 7, 7);
	}
	else if (0x0080 <= code && code <= 0x07FF) {
		ret = "110" + bin.substr(m - 11, 5) + "10" + bin.substr(m - 6, 6);
	}
	else if (0x0890 <= code && code <= 0xFFFF) {
		ret = "1110" + bin.substr(m - 16, 4) + "10" + bin.substr(m - 12, 6) + "10" + bin.substr(m - 6, 6);
	}
	else if (0x10000 <= code && code <= 0x10FFFF) {
		ret = "11110" + bin.substr(m - 21, 3) + "10" + bin.substr(m - 18, 6) + "10" + bin.substr(m - 12, 6) + "10" + bin.substr(m - 6, 6);
	}
	else {
		return -1;
	}

	return std::stoull(ret, 0, 2);
}

unsigned long long UTF8ToUnicode(unsigned long long code) {

	std::string bin;
	unsigned int mask = (int)1 << (sizeof(unsigned int) * CHAR_BIT - 1);
	do bin += (mask & code ? '1' : '0');
	while (mask >>= 1);
	int m = bin.size();

	std::string ret;

	if (0x0000 <= code && code <= 0x007F) { //U+0000 - U+007F
		ret = bin.substr(m - 7, 7);
	}
	else if (0x0080 <= code && code <= 0xDFBF) { //U+0080 - U+07FF
		ret = bin.substr(m - 13, 5) + bin.substr(m - 6, 6);
	}
	else if (0xE08080 <= code && code <= 0xEFBFBF) { //U+0800 - U+FFFF
		ret = bin.substr(m - 20, 4) + bin.substr(m - 14, 6) + bin.substr(m - 6, 6);
	}
	else if (0xF0808080 <= code && code <= 0xF7BFBFBF) { //U+10000 - U+10FFFF
		ret = bin.substr(m - 27, 3) + bin.substr(m - 22, 6) + bin.substr(m - 14, 6) + bin.substr(m - 6, 6);
	}
	else {
		return -1;
	}

	return std::stoull(ret, 0, 2);
}


//文字列ローカライズ
icu::UnicodeString HiraganaToKatakana(icu::UnicodeString str) {
	return StrTransliterate(str, "Hiragana-Katakana");
}

icu::UnicodeString KatakanaToHiragana(icu::UnicodeString str) {
	return StrTransliterate(str, "Hiragana-Katakana");
}

icu::UnicodeString LatinToHiragana(icu::UnicodeString str) {
	return StrTransliterate(str, "Latin-Hiragana");
}

icu::UnicodeString LatinToKatakana(icu::UnicodeString str) {
	return StrTransliterate(str, "Latin-Katakana");
}

icu::UnicodeString LatinBGNToHiragana(icu::UnicodeString str) {
	return StrTransliterate(str, "Latin/BGN-Hiragana");
}

icu::UnicodeString LatinBGNToKatakana(icu::UnicodeString str) {
	return StrTransliterate(str, "Latin/BGN-Katakana");
}

icu::UnicodeString HiraganaToLatin(icu::UnicodeString str) {
	return StrTransliterate(str, "Hiragana-Latin");
}

icu::UnicodeString KatakanaToLatin(icu::UnicodeString str) {
	return StrTransliterate(str, "Katakana-Latin");
}

icu::UnicodeString HiraganaToLatinBGN(icu::UnicodeString str) {
	return StrTransliterate(str, "Hiragana-Latin/BGN");
}

icu::UnicodeString KatakanaToLatinBGN(icu::UnicodeString str) {
	return StrTransliterate(str, "Katakana-Latin/BGN");
}

icu::UnicodeString HalfwidthToFullwidth(icu::UnicodeString str) {
	return StrTransliterate(str, "Halfwidth-Fullwidth");
}

icu::UnicodeString FullwidthToHalfwidth(icu::UnicodeString str) {
	return StrTransliterate(str, "Fullwidth-Halfwidth");
}

//型変換
std::wstring DecToHex(int num) {
	std::ostringstream os;
	os << std::hex << num;
	return L"0x" + StrToWstr(os.str());
}

int HexToDec(std::wstring num) {
	return std::stoi(num, nullptr, 16);
}

std::wstring tostring(double num) {
	return StrToWstr(std::to_string(num));
}

std::wstring tostring_n(double num) {
	std::wstring str = StrToWstr(std::to_string(num));

	if (str.find(L".") == std::string::npos) {
		return str;
	}

	int l = str.length();
	for (int i = 0; i < l; i++) {
		const wchar_t s = str[l - (i + 1)];

		if (s == L'0') {
			str.pop_back();
		}
		else if (s == L'.') {
			str.pop_back();
			break;
		}
		else if (s == L'\0') {
			str.pop_back();
		}
		else {
			break;
		}
	}

	return str;
}

//大文字小文字変換
std::wstring lowerString(std::wstring type) {
	std::transform(type.cbegin(), type.cend(), type.begin(), tolower);
	return type;
}
std::string lowerString(std::string type) {
	std::transform(type.cbegin(), type.cend(), type.begin(), tolower);
	return type;
}
std::wstring upperString(std::wstring type) {
	std::transform(type.cbegin(), type.cend(), type.begin(), toupper);
	return type;
}
std::string upperString(std::string type) {
	std::transform(type.cbegin(), type.cend(), type.begin(), toupper);
	return type;
}

//文字列分割
std::vector<std::wstring> split(std::wstring str, wchar_t del) {
	std::vector<std::wstring> result;
	std::wstring subStr;

	for (const wchar_t c : str) {
		if (c == del) {
			result.push_back(subStr);
			subStr.clear();
		}
		else {
			subStr += c;
		}
	}

	result.push_back(subStr);
	return result;
}

std::vector<std::string> split(std::string str, char del) {
	std::vector<std::string> result;
	std::string subStr;

	for (const char c : str) {
		if (c == del) {
			result.push_back(subStr);
			subStr.clear();
		}
		else {
			subStr += c;
		}
	}

	result.push_back(subStr);
	return result;
}

//デバッグ用関数
void debug_string(std::wstring message) {
	OutputDebugString(WstrToStr(message).c_str());
}

void debug_string(std::string message) {
	OutputDebugString(message.c_str());
}

void debug_string(double message) {
	OutputDebugString(WstrToStr(tostring(message)).c_str());
}