#pragma once
#include <iostream>
#include <windows.h>

#define MODULE_NAME "textmodule"
#define MODULE_VERSION 31
#define ALIAS_MODULE_NAME "tm"

std::wstring getVersionNum(int num);
void SetDllPath();
HWND GetAviUtlWindowHandle();