#include <iostream>
#include <atlconv.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#pragma comment(lib, "atls.lib")
#pragma comment(lib, "afxnmcd.lib")

//ƒƒCƒh•¶š - ƒ}ƒ‹ƒ`ƒoƒCƒg•¶š@‘ŠŒİ•ÏŠ·
std::string WstrToStr(std::wstring str) {
	USES_CONVERSION_EX;

	const auto pwstr = W2A_EX(str.c_str(), str.length());
	if (pwstr != NULL) {
		std::string dst(pwstr);
		return dst;
	}
}

std::wstring StrToWstr(std::string str) {
	USES_CONVERSION_EX;

	const auto pwstr = A2W_EX(str.c_str(), str.length());
	if (pwstr != NULL) {
		std::wstring dst(pwstr);
		return dst;
	}
}


//’uŠ·
std::wstring _jreplace(std::wstring String1, std::wstring String2, std::wstring String3, bool invert)
{
	if (invert) {
		auto temp = String3;
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

std::wstring toKatakana(std::wstring string, bool invert)
{
	string = _jreplace(string, L"‚Ÿ", L"ƒ@", invert);
	string = _jreplace(string, L"‚ ", L"ƒA", invert);
	string = _jreplace(string, L"‚¡", L"ƒB", invert);
	string = _jreplace(string, L"‚¢", L"ƒC", invert);
	string = _jreplace(string, L"‚£", L"ƒD", invert);
	string = _jreplace(string, L"‚¤", L"ƒE", invert);
	string = _jreplace(string, L"‚¥", L"ƒF", invert);
	string = _jreplace(string, L"‚¦", L"ƒG", invert);
	string = _jreplace(string, L"‚§", L"ƒH", invert);
	string = _jreplace(string, L"‚¨", L"ƒI", invert);
	string = _jreplace(string, L"‚©", L"ƒJ", invert);
	string = _jreplace(string, L"‚ª", L"ƒK", invert);
	string = _jreplace(string, L"‚«", L"ƒL", invert);
	string = _jreplace(string, L"‚¬", L"ƒM", invert);
	string = _jreplace(string, L"‚­", L"ƒN", invert);
	string = _jreplace(string, L"‚®", L"ƒO", invert);
	string = _jreplace(string, L"‚¯", L"ƒP", invert);
	string = _jreplace(string, L"‚°", L"ƒQ", invert);
	string = _jreplace(string, L"‚±", L"ƒR", invert);
	string = _jreplace(string, L"‚²", L"ƒS", invert);
	string = _jreplace(string, L"‚³", L"ƒT", invert);
	string = _jreplace(string, L"‚´", L"ƒU", invert);
	string = _jreplace(string, L"‚µ", L"ƒV", invert);
	string = _jreplace(string, L"‚¶", L"ƒW", invert);
	string = _jreplace(string, L"‚·", L"ƒX", invert);
	string = _jreplace(string, L"‚¸", L"ƒY", invert);
	string = _jreplace(string, L"‚¹", L"ƒZ", invert);
	string = _jreplace(string, L"‚º", L"ƒ[", invert);
	string = _jreplace(string, L"‚»", L"ƒ\", invert);
	string = _jreplace(string, L"‚¼", L"ƒ]", invert);
	string = _jreplace(string, L"‚½", L"ƒ^", invert);
	string = _jreplace(string, L"‚¾", L"ƒ_", invert);
	string = _jreplace(string, L"‚¿", L"ƒ`", invert);
	string = _jreplace(string, L"‚À", L"ƒa", invert);
	string = _jreplace(string, L"‚Á", L"ƒb", invert);
	string = _jreplace(string, L"‚Â", L"ƒc", invert);
	string = _jreplace(string, L"‚Ã", L"ƒd", invert);
	string = _jreplace(string, L"‚Ä", L"ƒe", invert);
	string = _jreplace(string, L"‚Å", L"ƒf", invert);
	string = _jreplace(string, L"‚Æ", L"ƒg", invert);
	string = _jreplace(string, L"‚Ç", L"ƒh", invert);
	string = _jreplace(string, L"‚È", L"ƒi", invert);
	string = _jreplace(string, L"‚É", L"ƒj", invert);
	string = _jreplace(string, L"‚Ê", L"ƒk", invert);
	string = _jreplace(string, L"‚Ë", L"ƒl", invert);
	string = _jreplace(string, L"‚Ì", L"ƒm", invert);
	string = _jreplace(string, L"‚Í", L"ƒn", invert);
	string = _jreplace(string, L"‚Î", L"ƒo", invert);
	string = _jreplace(string, L"‚Ï", L"ƒp", invert);
	string = _jreplace(string, L"‚Ğ", L"ƒq", invert);
	string = _jreplace(string, L"‚Ñ", L"ƒr", invert);
	string = _jreplace(string, L"‚Ò", L"ƒs", invert);
	string = _jreplace(string, L"‚Ó", L"ƒt", invert);
	string = _jreplace(string, L"‚Ô", L"ƒu", invert);
	string = _jreplace(string, L"‚Õ", L"ƒv", invert);
	string = _jreplace(string, L"‚Ö", L"ƒw", invert);
	string = _jreplace(string, L"‚×", L"ƒx", invert);
	string = _jreplace(string, L"‚Ø", L"ƒy", invert);
	string = _jreplace(string, L"‚Ù", L"ƒz", invert);
	string = _jreplace(string, L"‚Ú", L"ƒ{", invert);
	string = _jreplace(string, L"‚Û", L"ƒ|", invert);
	string = _jreplace(string, L"‚Ü", L"ƒ}", invert);
	string = _jreplace(string, L"‚İ", L"ƒ~", invert);
	string = _jreplace(string, L"‚Ş", L"ƒ€", invert);
	string = _jreplace(string, L"‚ß", L"ƒ", invert);
	string = _jreplace(string, L"‚à", L"ƒ‚", invert);
	string = _jreplace(string, L"‚á", L"ƒƒ", invert);
	string = _jreplace(string, L"‚â", L"ƒ„", invert);
	string = _jreplace(string, L"‚ã", L"ƒ…", invert);
	string = _jreplace(string, L"‚ä", L"ƒ†", invert);
	string = _jreplace(string, L"‚å", L"ƒ‡", invert);
	string = _jreplace(string, L"‚æ", L"ƒˆ", invert);
	string = _jreplace(string, L"‚ç", L"ƒ‰", invert);
	string = _jreplace(string, L"‚è", L"ƒŠ", invert);
	string = _jreplace(string, L"‚é", L"ƒ‹", invert);
	string = _jreplace(string, L"‚ê", L"ƒŒ", invert);
	string = _jreplace(string, L"‚ë", L"ƒ", invert);
	string = _jreplace(string, L"‚ì", L"ƒ", invert);
	string = _jreplace(string, L"‚í", L"ƒ", invert);
	string = _jreplace(string, L"‚ğ", L"ƒ’", invert);
	string = _jreplace(string, L"‚ñ", L"ƒ“", invert);
	string = _jreplace(string, L"‚î", L"ƒ", invert);
	string = _jreplace(string, L"‚ï", L"ƒ‘", invert);

	return string;
}

std::wstring toHalfwidth(std::wstring string, bool invert, bool space) {
	string = _jreplace(string, L"‚O", L"0", invert);
	string = _jreplace(string, L"‚P", L"1", invert);
	string = _jreplace(string, L"‚Q", L"2", invert);
	string = _jreplace(string, L"‚R", L"3", invert);
	string = _jreplace(string, L"‚S", L"4", invert);
	string = _jreplace(string, L"‚T", L"5", invert);
	string = _jreplace(string, L"‚U", L"6", invert);
	string = _jreplace(string, L"‚V", L"7", invert);
	string = _jreplace(string, L"‚W", L"8", invert);
	string = _jreplace(string, L"‚X", L"9", invert);

	string = _jreplace(string, L"‚`", L"A", invert);
	string = _jreplace(string, L"‚a", L"B", invert);
	string = _jreplace(string, L"‚b", L"C", invert);
	string = _jreplace(string, L"‚c", L"D", invert);
	string = _jreplace(string, L"‚d", L"E", invert);
	string = _jreplace(string, L"‚e", L"F", invert);
	string = _jreplace(string, L"‚f", L"G", invert);
	string = _jreplace(string, L"‚g", L"H", invert);
	string = _jreplace(string, L"‚h", L"I", invert);
	string = _jreplace(string, L"‚i", L"J", invert);
	string = _jreplace(string, L"‚j", L"K", invert);
	string = _jreplace(string, L"‚k", L"L", invert);
	string = _jreplace(string, L"‚l", L"M", invert);
	string = _jreplace(string, L"‚m", L"N", invert);
	string = _jreplace(string, L"‚n", L"O", invert);
	string = _jreplace(string, L"‚o", L"P", invert);
	string = _jreplace(string, L"‚p", L"Q", invert);
	string = _jreplace(string, L"‚q", L"R", invert);
	string = _jreplace(string, L"‚r", L"S", invert);
	string = _jreplace(string, L"‚s", L"T", invert);
	string = _jreplace(string, L"‚t", L"U", invert);
	string = _jreplace(string, L"‚u", L"V", invert);
	string = _jreplace(string, L"‚v", L"W", invert);
	string = _jreplace(string, L"‚w", L"X", invert);
	string = _jreplace(string, L"‚x", L"Y", invert);
	string = _jreplace(string, L"‚y", L"Z", invert);

	string = _jreplace(string, L"‚", L"a", invert);
	string = _jreplace(string, L"‚‚", L"b", invert);
	string = _jreplace(string, L"‚ƒ", L"c", invert);
	string = _jreplace(string, L"‚„", L"d", invert);
	string = _jreplace(string, L"‚…", L"e", invert);
	string = _jreplace(string, L"‚†", L"f", invert);
	string = _jreplace(string, L"‚‡", L"g", invert);
	string = _jreplace(string, L"‚ˆ", L"h", invert);
	string = _jreplace(string, L"‚‰", L"i", invert);
	string = _jreplace(string, L"‚Š", L"j", invert);
	string = _jreplace(string, L"‚‹", L"k", invert);
	string = _jreplace(string, L"‚Œ", L"l", invert);
	string = _jreplace(string, L"‚", L"m", invert);
	string = _jreplace(string, L"‚", L"n", invert);
	string = _jreplace(string, L"‚", L"o", invert);
	string = _jreplace(string, L"‚", L"p", invert);
	string = _jreplace(string, L"‚‘", L"q", invert);
	string = _jreplace(string, L"‚’", L"r", invert);
	string = _jreplace(string, L"‚“", L"s", invert);
	string = _jreplace(string, L"‚”", L"t", invert);
	string = _jreplace(string, L"‚•", L"u", invert);
	string = _jreplace(string, L"‚–", L"v", invert);
	string = _jreplace(string, L"‚—", L"w", invert);
	string = _jreplace(string, L"‚˜", L"x", invert);
	string = _jreplace(string, L"‚™", L"y", invert);
	string = _jreplace(string, L"‚š", L"z", invert);

	string = _jreplace(string, L"ƒA", L"±", invert);
	string = _jreplace(string, L"ƒC", L"²", invert);
	string = _jreplace(string, L"ƒE", L"³", invert);
	string = _jreplace(string, L"ƒG", L"´", invert);
	string = _jreplace(string, L"ƒI", L"µ", invert);
	string = _jreplace(string, L"ƒJ", L"¶", invert);
	string = _jreplace(string, L"ƒL", L"·", invert);
	string = _jreplace(string, L"ƒN", L"¸", invert);
	string = _jreplace(string, L"ƒP", L"¹", invert);
	string = _jreplace(string, L"ƒR", L"º", invert);
	string = _jreplace(string, L"ƒT", L"»", invert);
	string = _jreplace(string, L"ƒV", L"¼", invert);
	string = _jreplace(string, L"ƒX", L"½", invert);
	string = _jreplace(string, L"ƒZ", L"¾", invert);
	string = _jreplace(string, L"ƒ\", L"¿", invert);
	string = _jreplace(string, L"ƒ^", L"À", invert);
	string = _jreplace(string, L"ƒ`", L"Á", invert);
	string = _jreplace(string, L"ƒc", L"Â", invert);
	string = _jreplace(string, L"ƒe", L"Ã", invert);
	string = _jreplace(string, L"ƒg", L"Ä", invert);
	string = _jreplace(string, L"ƒi", L"Å", invert);
	string = _jreplace(string, L"ƒj", L"Æ", invert);
	string = _jreplace(string, L"ƒk", L"Ç", invert);
	string = _jreplace(string, L"ƒl", L"È", invert);
	string = _jreplace(string, L"ƒm", L"É", invert);
	string = _jreplace(string, L"ƒn", L"Ê", invert);
	string = _jreplace(string, L"ƒq", L"Ë", invert);
	string = _jreplace(string, L"ƒt", L"Ì", invert);
	string = _jreplace(string, L"ƒw", L"Í", invert);
	string = _jreplace(string, L"ƒz", L"Î", invert);
	string = _jreplace(string, L"ƒ}", L"Ï", invert);
	string = _jreplace(string, L"ƒ~", L"Ğ", invert);
	string = _jreplace(string, L"ƒ€", L"Ñ", invert);
	string = _jreplace(string, L"ƒ", L"Ò", invert);
	string = _jreplace(string, L"ƒ‚", L"Ó", invert);
	string = _jreplace(string, L"ƒ„", L"Ô", invert);
	string = _jreplace(string, L"ƒ†", L"Õ", invert);
	string = _jreplace(string, L"ƒˆ", L"Ö", invert);
	string = _jreplace(string, L"ƒ‰", L"×", invert);
	string = _jreplace(string, L"ƒŠ", L"Ø", invert);
	string = _jreplace(string, L"ƒ‹", L"Ù", invert);
	string = _jreplace(string, L"ƒŒ", L"Ú", invert);
	string = _jreplace(string, L"ƒ", L"Û", invert);
	string = _jreplace(string, L"ƒ", L"Ü", invert);
	string = _jreplace(string, L"ƒ’", L"¦", invert);
	string = _jreplace(string, L"ƒ“", L"İ", invert);
	string = _jreplace(string, L"ƒ”", L"³Ş", invert);
	string = _jreplace(string, L"ƒK", L"¶Ş", invert);
	string = _jreplace(string, L"ƒM", L"·Ş", invert);
	string = _jreplace(string, L"ƒO", L"¸Ş", invert);
	string = _jreplace(string, L"ƒQ", L"¹Ş", invert);
	string = _jreplace(string, L"ƒS", L"ºŞ", invert);
	string = _jreplace(string, L"ƒU", L"»Ş", invert);
	string = _jreplace(string, L"ƒW", L"¼Ş", invert);
	string = _jreplace(string, L"ƒY", L"½Ş", invert);
	string = _jreplace(string, L"ƒ[", L"¾Ş", invert);
	string = _jreplace(string, L"ƒ]", L"¿Ş", invert);
	string = _jreplace(string, L"ƒ_", L"ÀŞ", invert);
	string = _jreplace(string, L"ƒa", L"ÁŞ", invert);
	string = _jreplace(string, L"ƒd", L"ÂŞ", invert);
	string = _jreplace(string, L"ƒf", L"ÃŞ", invert);
	string = _jreplace(string, L"ƒh", L"ÄŞ", invert);
	string = _jreplace(string, L"ƒo", L"ÊŞ", invert);
	string = _jreplace(string, L"ƒr", L"ËŞ", invert);
	string = _jreplace(string, L"ƒu", L"ÌŞ", invert);
	string = _jreplace(string, L"ƒx", L"ÍŞ", invert);
	string = _jreplace(string, L"ƒ{", L"ÎŞ", invert);
	string = _jreplace(string, L"ƒp", L"Êß", invert);
	string = _jreplace(string, L"ƒs", L"Ëß", invert);
	string = _jreplace(string, L"ƒv", L"Ìß", invert);
	string = _jreplace(string, L"ƒy", L"Íß", invert);
	string = _jreplace(string, L"ƒ|", L"Îß", invert);
	string = _jreplace(string, L"ƒ@", L"§", invert);
	string = _jreplace(string, L"ƒB", L"¨", invert);
	string = _jreplace(string, L"ƒD", L"©", invert);
	string = _jreplace(string, L"ƒF", L"ª", invert);
	string = _jreplace(string, L"ƒH", L"«", invert);
	string = _jreplace(string, L"ƒƒ", L"¬", invert);
	string = _jreplace(string, L"ƒ…", L"­", invert);
	string = _jreplace(string, L"ƒ‡", L"®", invert);
	string = _jreplace(string, L"[", L"°", invert);
	string = _jreplace(string, L"J", L"Ş", invert);
	string = _jreplace(string, L"K", L"ß", invert);
	string = _jreplace(string, L"E", L"¥", invert);
	string = _jreplace(string, L"u", L"¢", invert);
	string = _jreplace(string, L"v", L"£", invert);
	string = _jreplace(string, L"B", L"¡", invert);
	string = _jreplace(string, L"A", L"¤", invert);

	string = _jreplace(string, L"I", L"!", invert);
	string = _jreplace(string, L"úW", L"\"", invert);
	string = _jreplace(string, L"”", L"#", invert);
	string = _jreplace(string, L"", L"$", invert);
	string = _jreplace(string, L"“", L"%", invert);
	string = _jreplace(string, L"•", L"&", invert);
	string = _jreplace(string, L"úV", L"\'", invert);
	string = _jreplace(string, L"i", L"(", invert);
	string = _jreplace(string, L"j", L")", invert);
	string = _jreplace(string, L"–", L"*", invert);
	string = _jreplace(string, L"{", L"+", invert);
	string = _jreplace(string, L"C", L",", invert);
	string = _jreplace(string, L"|", L"-", invert);
	string = _jreplace(string, L"D", L".", invert);
	string = _jreplace(string, L"^", L"/", invert);
	string = _jreplace(string, L"F", L":", invert);
	string = _jreplace(string, L"G", L";", invert);
	string = _jreplace(string, L"ƒ", L"<", invert);
	string = _jreplace(string, L"", L"=", invert);
	string = _jreplace(string, L"„", L">", invert);
	string = _jreplace(string, L"H", L"\?", invert);
	string = _jreplace(string, L"—", L"@", invert);
	string = _jreplace(string, L"m", L"[", invert);
	string = _jreplace(string, L"_", L"\\", invert);
	string = _jreplace(string, L"n", L"]", invert);
	string = _jreplace(string, L"O", L"^", invert);
	string = _jreplace(string, L"Q", L"_", invert);
	string = _jreplace(string, L"M", L"`", invert);
	string = _jreplace(string, L"o", L"{", invert);
	string = _jreplace(string, L"b", L"|", invert);
	string = _jreplace(string, L"p", L"}", invert);
	string = _jreplace(string, L"`", L"~", invert);
	string = _jreplace(string, L"", L"\\", invert);

	if (space)
		string = _jreplace(string, L"@", L" ", invert);

	return string;
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