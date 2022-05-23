#include "textmodule_string.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

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

#include <boost/shared_ptr.hpp>

#include "textmodule_exception.hpp"

#pragma comment(lib, "atls.lib")
#pragma comment(lib, "afxnmcd.lib")

using namespace icu;

//ƒƒCƒh•¶š - ƒ}ƒ‹ƒ`ƒoƒCƒg•¶š@‘ŠŒİ•ÏŠ·
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


//’uŠ·
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


//•¶š—ñƒ[ƒJƒ‰ƒCƒY
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


std::wstring toRoundNumber(std::wstring string, bool invert)
{
	string = _jreplace(string, L"20", L"‡S", invert);
	string = _jreplace(string, L"19", L"‡R", invert);
	string = _jreplace(string, L"18", L"‡Q", invert);
	string = _jreplace(string, L"17", L"‡P", invert);
	string = _jreplace(string, L"16", L"‡O", invert);
	string = _jreplace(string, L"15", L"‡N", invert);
	string = _jreplace(string, L"14", L"‡M", invert);
	string = _jreplace(string, L"13", L"‡L", invert);
	string = _jreplace(string, L"12", L"‡K", invert);
	string = _jreplace(string, L"11", L"‡J", invert);
	string = _jreplace(string, L"10", L"‡I", invert);
	string = _jreplace(string, L"9", L"‡H", invert);
	string = _jreplace(string, L"8", L"‡G", invert);
	string = _jreplace(string, L"7", L"‡F", invert);
	string = _jreplace(string, L"6", L"‡E", invert);
	string = _jreplace(string, L"5", L"‡D", invert);
	string = _jreplace(string, L"4", L"‡C", invert);
	string = _jreplace(string, L"3", L"‡B", invert);
	string = _jreplace(string, L"2", L"‡A", invert);
	string = _jreplace(string, L"1", L"‡@", invert);

	string = _jreplace(string, L"‚Q‚O", L"‡S", invert);
	string = _jreplace(string, L"‚P‚X", L"‡R", invert);
	string = _jreplace(string, L"‚P‚W", L"‡Q", invert);
	string = _jreplace(string, L"‚P‚V", L"‡P", invert);
	string = _jreplace(string, L"‚P‚U", L"‡O", invert);
	string = _jreplace(string, L"‚P‚T", L"‡N", invert);
	string = _jreplace(string, L"‚P‚S", L"‡M", invert);
	string = _jreplace(string, L"‚P‚R", L"‡L", invert);
	string = _jreplace(string, L"‚P‚Q", L"‡K", invert);
	string = _jreplace(string, L"‚P‚P", L"‡J", invert);
	string = _jreplace(string, L"‚P‚O", L"‡I", invert);
	string = _jreplace(string, L"‚X", L"‡H", invert);
	string = _jreplace(string, L"‚W", L"‡G", invert);
	string = _jreplace(string, L"‚V", L"‡F", invert);
	string = _jreplace(string, L"‚U", L"‡E", invert);
	string = _jreplace(string, L"‚T", L"‡D", invert);
	string = _jreplace(string, L"‚S", L"‡C", invert);
	string = _jreplace(string, L"‚R", L"‡B", invert);
	string = _jreplace(string, L"‚Q", L"‡A", invert);
	string = _jreplace(string, L"‚P", L"‡@", invert);

	return string;
}


//Unicode  - UTF8@‘ŠŒİ•ÏŠ·
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

//Œ^•ÏŠ·
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

//‘å•¶š¬•¶š•ÏŠ·
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

//•¶š—ñ•ªŠ„
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

//ƒfƒoƒbƒO—pŠÖ”
void debug_string(std::wstring message) {
	OutputDebugString(WstrToStr(message).c_str());
}

void debug_string(std::string message) {
	OutputDebugString(message.c_str());
}

void debug_string(double message) {
	OutputDebugString(WstrToStr(tostring(message)).c_str());
}