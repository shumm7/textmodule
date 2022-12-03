#include "textmodule.hpp"

#include <iostream>
#include <windows.h>
#include <filesystem>

std::wstring getVersionNum(int num) {
	switch (num) {
	case 1: return L"0.0.1";
	case 2: return L"0.0.2";
	case 3: return L"0.0.3";
	case 10: return L"0.1.0";
	case 11: return L"0.1.1";
	case 12: return L"0.1.2";
	case 13: return L"0.1.3";
	case 14: return L"0.1.4";
	case 15: return L"0.1.5";
	case 16: return L"0.1.6";
	case 100: return L"1.0.0";
	case 110: return L"1.1.0";
	case 111: return L"1.1.1";
	case 112: return L"1.1.2";
	case 120: return L"1.2.0";
	case 121: return L"1.2.1";
	case 122: return L"1.2.2";
	case 123: return L"1.2.3";
	case 124: return L"1.2.4";
	case 125: return L"1.2.5";
	case 126: return L"1.2.6";
	case 127: return L"1.2.7";
	case 130: return L"1.3.0";
	case 131: return L"1.3.1";
	case 132: return L"1.3.2";
	case 133: return L"1.3.3";
	case 134: return L"1.3.4";
	case 135: return L"1.3.5";
	case 136: return L"1.3.6";
	case 137: return L"1.3.7";
	case 140: return L"1.4.0";
	case 141: return L"1.4.1";
	case 142: return L"1.4.2";

	default: return L"";
	}
}

void SetDllPath() {
	SetDllDirectory(std::filesystem::canonical(MODULE_DLLDIR).string().c_str());
}