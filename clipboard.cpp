#include "clipboard.hpp"

#include <lua.hpp>
#include <iostream>
#include <windows.h>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

#pragma comment(lib,"user32.lib")

int clipboard_get(lua_State* L) {
	try {
		HGLOBAL hMem;
		LPTSTR lpBuff;
		lua_Wstring str;
		bool flag = false;

		if (OpenClipboard(NULL)) {
			if ((hMem = GetClipboardData(CF_TEXT)) != NULL) {
				if ((lpBuff = (LPTSTR)GlobalLock(hMem)) != NULL) {
					str = StrToWstr((const char*)lpBuff);

					lua_pushstring(L, WstrToStr(str).c_str());
					flag = true;
					GlobalUnlock(hMem);
				}
			}
			CloseClipboard();
		}

		if (flag)
			return 1;
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int clipboard_set(lua_State* L) {
	try {
		HGLOBAL hMem;
		LPTSTR lpBuff;
		DWORD dwSize;
		LPTSTR lpText = (LPTSTR)tm_tostring(L, 1);
		bool flag = false;

		dwSize = ((lstrlen(lpText) + 1) * sizeof(TCHAR));

		if ((hMem = GlobalAlloc((GHND | GMEM_SHARE), dwSize)) != NULL) {
			if ((lpBuff = (LPTSTR)GlobalLock(hMem)) != NULL) {
				lstrcpy(lpBuff, lpText);
				GlobalUnlock(hMem);

				if (OpenClipboard(NULL)) {
					EmptyClipboard();
					SetClipboardData(CF_TEXT, hMem);
					CloseClipboard();
					flag = true;
				}
			}
			GlobalFree(hMem);
		}

		if (flag) {
			lua_pushboolean(L, true);
			return 1;
		}
		else {
			lua_pushboolean(L, false);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int clipboard_clear(lua_State* L) {
	try {
		bool flag = false;

		if (OpenClipboard(NULL)) {
			EmptyClipboard();
			CloseClipboard();
			flag = true;
		}

		if (flag) {
			lua_pushboolean(L, true);
			return 1;
		}
		else {
			lua_pushboolean(L, false);
			return 1;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_CLIPBOARD_REG[] = {
	{"get", clipboard_get},
	{"set", clipboard_set},
	{"clear", clipboard_clear},
	{ nullptr, nullptr }
};

void luaReg_clipboard(lua_State* L, lua_Option opt) {
	if (opt["api"]["clipboard"]) {
		tm_debuglog_apiloaded(opt, "clipboard");
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_CLIPBOARD_REG);
		lua_setfield(L, -2, "clipboard");
	}
	else {
		tm_debuglog_apinoloaded(opt, "clipboard");
	}
}