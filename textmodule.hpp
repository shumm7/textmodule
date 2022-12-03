#pragma once
#include <iostream>
#include <windows.h>

#define MODULE_NAME "textmodule"
#define MODULE_VERSION 142
#define ALIAS_MODULE_NAME "tm"

#define MODULE_DLLDIR "./textmodule/bin"

std::wstring getVersionNum(int num);
void SetDllPath();