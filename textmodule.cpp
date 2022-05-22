#include <iostream>
#include <windows.h>
#include <filesystem>

#define DLLDIR "./textmodule/bin"

std::wstring getVersionNum(int num) {
	switch (num) {
	case 1: return L"0.0.1";
	case 2: return L"0.0.2";
	case 3: return L"0.0.3";
	case 4: return L"0.1.0";
	case 5: return L"0.1.1";
	case 6: return L"0.1.2";
	case 7: return L"0.1.3";
	case 8: return L"0.1.4";
	case 9: return L"0.1.5";
	case 10: return L"0.1.6";
	case 11: return L"1.0.0";
	case 12: return L"1.1.0";
	case 13: return L"1.1.1";
	case 14: return L"1.1.2";
	case 15: return L"1.2.0";
	case 16: return L"1.2.1";
	case 17: return L"1.2.2";
	case 18: return L"1.2.3";
	case 19: return L"1.2.4";
	case 20: return L"1.2.5";
	case 21: return L"1.2.6";
	case 22: return L"1.2.7";
	case 23: return L"1.3.0";
	case 24: return L"1.3.1";
	case 25: return L"1.3.2";
	case 26: return L"1.3.3";
	case 27: return L"1.3.4";
	case 28: return L"1.3.5";
	case 29: return L"1.3.6";

	default: return L"";
	}
}

void SetDllPath() {
	SetDllDirectory(std::filesystem::canonical(DLLDIR).string().c_str());
}