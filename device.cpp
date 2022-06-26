#include "device.hpp"

#include <lua.hpp>
#include <iostream>
#include <windows.h>
#include <stdexcept>
#include <cmath>
#include <bit>
#include <sstream>
#include <tchar.h>
#include <format>

#include "textmodule.hpp"
#include "textmodule_lua.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_string.hpp"

#pragma comment(lib, "winmm.lib")

struct FONT_INFO {
	std::string FullName;
	std::string Style;
	std::string Script;
	std::string FontType;
	long Width;
	long Height;
};

std::vector<FONT_INFO*> fonts;

bool device_check_keystate(BYTE keystate) {
	return (bool)(keystate & 0x80);
}

double device_joystick_clamp(DWORD axis, bool raw) {
	double n = (double)axis;
	if (raw)
		return n;
	return (n - 32767.0) / 32768.0;
}

bool device_joystick_button(DWORD button, int num) {
	DWORD f = std::pow(2, num-1);
	return button & f;
}

lua_Sstring device_joystick_pov(DWORD pov) {
	switch (pov) {
	case JOY_POVLEFT:
		return "left";
	case JOY_POVFORWARD:
		return "forward";
	case JOY_POVRIGHT:
		return "right";
	case JOY_POVBACKWARD:
		return "backward";
	case JOY_POVCENTERED:
		return "centered";
	}
	return "";
}

int device_push_joystickvalue(lua_State* L, JOYINFOEX info, bool raw) {
	lua_newtable(L);

	lua_settablevalue(L, "x", device_joystick_clamp(info.dwXpos, raw));
	lua_settablevalue(L, "y", device_joystick_clamp(info.dwYpos, raw));
	lua_settablevalue(L, "z", device_joystick_clamp(info.dwZpos, raw));
	lua_settablevalue(L, "r", device_joystick_clamp(info.dwRpos, raw));
	lua_settablevalue(L, "u", device_joystick_clamp(info.dwUpos, raw));
	lua_settablevalue(L, "v", device_joystick_clamp(info.dwVpos, raw));
	
	
	for (int i = 1; i <= 32; i++)
		lua_settablevalue(L, i, device_joystick_button(info.dwButtons, i));

	if (raw) {
		lua_settablevalue(L, 0, (lua_Number)info.dwButtons);
		lua_settablevalue(L, "pov", (lua_Number)info.dwPOV);
	}
	else {
		lua_pushinteger(L, 0);
		lua_newtable(L);
		for (int i = 1; i <= 32; i++)
			lua_settablevalue(L, i, device_joystick_button(info.dwButtons, i));
		lua_settable(L, -3);

		lua_settablevalue(L, "pov", device_joystick_pov(info.dwPOV));
	}

	return 1;
}

lua_Sstring device_get_osname(int major, int minor, int build) {
	if (major == 5 && minor == 0)
		return "Windows 2000";
	else if (major == 5 && minor == 1)
		return "Windows XP";
	else if (major == 6 && minor == 0)
		return "Windows Vista";
	else if (major == 6 && minor == 1)
		return "Windows 7";
	else if (major == 6 && minor == 2)
		return "Windows 8";
	else if (major == 6 && minor == 3)
		return "Windows 8.1";
	else if (major == 10 && minor == 0) {
		if (build >= 22000)
			return "Windows 11";
		else
			return "Windows 10";
	}
	else
		return "Unknown";
}

int CALLBACK EnumFontFamProc(const LOGFONT* lpelf, const TEXTMETRIC FAR* lpntm, DWORD FontType, LPARAM lParam) {
	ENUMLOGFONTEX* lpelfe = (ENUMLOGFONTEX*)lpelf;
	
	FONT_INFO* fip = new FONT_INFO;
	char buf[256] = "";
	sprintf_s(buf, sizeof(buf), _TEXT("%s"), lpelfe->elfFullName);
	fip->FullName = std::string(buf);

	sprintf_s(buf, sizeof(buf), _TEXT("%s"), lpelfe->elfStyle);
	fip->Style = std::string(buf);

	sprintf_s(buf, sizeof(buf), _TEXT("%s"), lpelfe->elfScript);
	fip->Script = std::string(buf);

	switch (FontType) {
	case DEVICE_FONTTYPE:
		fip->FontType = "device";
		break;
	case RASTER_FONTTYPE:
		fip->FontType = "raster";
		break;
	case TRUETYPE_FONTTYPE:
		fip->FontType = "truetype";
		break;
	default:
		fip->FontType = "";
		break;
	}

	fip->Width = lpelf->lfWidth;
	fip->Height = lpelf->lfHeight;

	fonts.push_back(fip);
	return 1;
}


int device_key(lua_State* L) {
	try {
		bool mode = false;
		lua_Integer key = 0;
		if (lua_type(L, 1) != LUA_TNONE) {
			mode = true;
			key = luaL_checkinteger(L, 1);
		}

		BYTE lpKeyState[256];
		BOOL ret = GetKeyboardState(lpKeyState);
		if (ret) {
			if (!mode) {
				lua_newtable(L);
				for (int i = 0; i < 256; i++) {
					lua_settablevalue(L, i, device_check_keystate(lpKeyState[i]));
				}
				return 1;
			}
			else if (mode && key >= 0 && key <= 255) {
				lua_pushboolean(L, device_check_keystate(lpKeyState[key]));
				return 1;
			}
		}
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int device_mouse(lua_State* L) {
	try {
		POINT pt;
		GetCursorPos(&pt);

		BYTE lpKeyState[256];
		BOOL ret = GetKeyboardState(lpKeyState);
		lua_Number x = pt.x;
		lua_Number y = pt.y;

		int tp = lua_type(L, 1);

		if (tp == LUA_TSTRING) {
			lua_Sstring i = lua_tosstring(L, 1);

			if (i == "x")
				lua_pushnumber(L, x);
			else if (i == "y")
				lua_pushnumber(L, y);
			else
				return 0;
			return 1;
		}
		else if (tp == LUA_TNUMBER) {
			lua_Integer n = lua_tointeger(L, 1);
			if (n == 0)
				lua_pushvector2(L, x, y);
			else if (n == 1)
				lua_pushboolean(L, (bool)(lpKeyState[0x01] & 0x80));
			else if (n == 2)
				lua_pushboolean(L, (bool)(lpKeyState[0x02] & 0x80));
			else if (n == 3)
				lua_pushboolean(L, (bool)(lpKeyState[0x04] & 0x80));
			else if (n == 4)
				lua_pushboolean(L, (bool)(lpKeyState[0x05] & 0x80));
			else if (n == 5)
				lua_pushboolean(L, (bool)(lpKeyState[0x06] & 0x80));
			else
				return 0;
			return 1;
		}
		else if (tp == LUA_TNONE) {
			lua_newtable(L);

			lua_settablevalue(L, "x", x);
			lua_settablevalue(L, "y", y);
			lua_settablevalue(L, 1, (bool)(lpKeyState[0x01] & 0x80));
			lua_settablevalue(L, 2, (bool)(lpKeyState[0x02] & 0x80));
			lua_settablevalue(L, 3, (bool)(lpKeyState[0x04] & 0x80));
			lua_settablevalue(L, 4, (bool)(lpKeyState[0x05] & 0x80));
			lua_settablevalue(L, 5, (bool)(lpKeyState[0x06] & 0x80));

			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int device_joystick(lua_State* L) {
	try {
		if (lua_isnone(L, 1)) {
			lua_pushnumber(L, joyGetNumDevs());
			return 1;
		}

		int idx = tm_tonumber_s(L, 1, 0);
		JOYINFOEX JoyInfo = JOYINFOEX{};
		JoyInfo.dwSize = sizeof(JOYINFOEX);
		JoyInfo.dwFlags = JOY_RETURNALL;

		if (JOYERR_NOERROR != joyGetPosEx(idx, &JoyInfo) || idx<0 || idx>=joyGetNumDevs()) {
			throw std::invalid_argument(JOYSTICK_NOTFOUND);
		}

		int tp = lua_type(L, 2);
		bool raw = tm_toboolean_s(L, 3, false);

		if (tp == LUA_TSTRING) {
			lua_Sstring i = lua_tosstring(L, 2);
			if (i == "x")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwXpos, raw));
			else if (i == "y")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwYpos, raw));
			else if (i == "z")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwZpos, raw));
			else if (i == "r")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwRpos, raw));
			else if (i == "u")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwUpos, raw));
			else if (i == "v")
				lua_pushnumber(L, device_joystick_clamp(JoyInfo.dwVpos, raw));
			else if (i == "pov") {
				if (raw)
					lua_pushnumber(L, JoyInfo.dwPOV);
				else
					lua_pushsstring(L, device_joystick_pov(JoyInfo.dwPOV));
				return 1;
			}
			else
				return 0;
			return 1;
		}
		else if (tp == LUA_TNUMBER) {
			lua_Integer n = lua_tointeger(L, 2);

			if (n >= 1 && n <= 32) {
				lua_pushboolean(L, device_joystick_button(JoyInfo.dwButtons, n));
			}
			else if (n == 0) {
				if (raw) {
					lua_pushnumber(L, JoyInfo.dwButtons);
				}
				else {
					lua_newtable(L);
					for (int i = 1; i <= 32; i++)
						lua_settablevalue(L, i, device_joystick_button(JoyInfo.dwButtons, i));
				}
			}
			else
				return 0;
			return 1;
		}
		else if (tp == LUA_TNONE) {
			return device_push_joystickvalue(L, JoyInfo, false);
		}
		else if (tp == LUA_TBOOLEAN) {
			return device_push_joystickvalue(L, JoyInfo, lua_toboolean(L, 2));
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int device_version(lua_State* L) {
	try {
		const auto hModule = LoadLibrary(TEXT("ntdll.dll"));
		if (!hModule) throw std::runtime_error(GET_OSVERSION_FAILED);

		if (const auto address = GetProcAddress(hModule, "RtlGetVersion"))
		{
			using RtlGetVersionType = NTSTATUS(WINAPI*)(OSVERSIONINFOEXW*);
			const auto RtlGetVersion = reinterpret_cast<RtlGetVersionType>(address);

			OSVERSIONINFOEXW ver = { sizeof(ver) };
			if (!FAILED(RtlGetVersion(&ver)))
			{
				if (tm_toboolean_s(L, 1, false)) { //table (raw)
					lua_newtable(L);
					lua_settablevalue(L, "major", (lua_Integer)ver.dwMajorVersion);
					lua_settablevalue(L, "minor", (lua_Integer)ver.dwMinorVersion);
					lua_settablevalue(L, "build", (lua_Integer)ver.dwBuildNumber);
					lua_settablevalue(L, "service_major", (lua_Integer)ver.wServicePackMajor);
					lua_settablevalue(L, "service_minor", (lua_Integer)ver.wServicePackMinor);
					lua_settablevalue(L, "csd", std::wstring(ver.szCSDVersion));

					lua_settablevalue(L, "product", (lua_Integer)ver.wProductType);
					lua_settablevalue(L, "platform", (lua_Integer)ver.dwPlatformId);
				}
				else { //string
					//os name
					lua_pushsstring(L, device_get_osname(ver.dwMajorVersion, ver.dwMinorVersion, ver.dwBuildNumber));

					//version
					std::wstringstream s;
					s << ver.dwMajorVersion << "." << ver.dwMinorVersion << "." << ver.dwBuildNumber << " " << std::wstring(ver.szCSDVersion);
					lua_pushwstring(L, s.str());

					return 2;
				}
			}
			else
				throw std::runtime_error(GET_OSVERSION_FAILED);
		}

		FreeLibrary(hModule);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int device_font(lua_State* L) {
	try {
		fonts.clear();

		LOGFONT lf;
		HDC hdc = GetDC(0);
		lf.lfFaceName[0] = _T('\0'); // 全てのフォント名
		lf.lfPitchAndFamily = DEFAULT_PITCH;
		lf.lfCharSet = tm_tonumber_s(L, 1, SHIFTJIS_CHARSET);
		EnumFontFamiliesEx(hdc, &lf, (FONTENUMPROC)EnumFontFamProc, (LONG_PTR)&lf, 0);
		ReleaseDC(0, hdc);

		lua_newtable(L);
		for (int n = 0; n < fonts.size(); n++) {
			lua_pushinteger(L, n+1);
			lua_newtable(L);
			lua_settablevalue(L, "name", fonts[n]->FullName);
			lua_settablevalue(L, "script", fonts[n]->Script);
			lua_settablevalue(L, "style", fonts[n]->Style);
			lua_settablevalue(L, "type", fonts[n]->FontType);
			lua_settablevalue(L, "height", (lua_Number)(fonts[n]->Height));
			lua_settablevalue(L, "width", (lua_Number)(fonts[n]->Width));
			lua_settable(L, -3);
		}
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


void luaReg_const_keycode(lua_State* L, const char* name) {
	lua_newtable(L);

	lua_settablevalue(L, "lbutton", 0x01);
	lua_settablevalue(L, "rbutton", 0x02);
	lua_settablevalue(L, "cancel", 0x03);
	lua_settablevalue(L, "mbutton", 0x04);
	lua_settablevalue(L, "xbutton1", 0x05);
	lua_settablevalue(L, "xbutton2", 0x06);
	lua_settablevalue(L, "back", 0x08);
	lua_settablevalue(L, "tab", 0x09);
	lua_settablevalue(L, "clear", 0x0C);
	lua_settablevalue(L, "return", 0x0D);
	lua_settablevalue(L, "shift", 0x10);
	lua_settablevalue(L, "control", 0x11);
	lua_settablevalue(L, "menu", 0x12);
	lua_settablevalue(L, "pause", 0x13);
	lua_settablevalue(L, "capital", 0x14);
	lua_settablevalue(L, "kana", 0x15);
	lua_settablevalue(L, "hanguel", 0x15);
	lua_settablevalue(L, "hangul", 0x15);
	lua_settablevalue(L, "ime_on", 0x16);
	lua_settablevalue(L, "junja", 0x17);
	lua_settablevalue(L, "final", 0x18);
	lua_settablevalue(L, "hanja", 0x19);
	lua_settablevalue(L, "kanji", 0x19);
	lua_settablevalue(L, "ime_off", 0x1A);
	lua_settablevalue(L, "escape", 0x1B);
	lua_settablevalue(L, "convert", 0x1C);
	lua_settablevalue(L, "nonconvert", 0x1D);
	lua_settablevalue(L, "accept", 0x1E);
	lua_settablevalue(L, "modechange", 0x1F);
	lua_settablevalue(L, "space", 0x20);
	lua_settablevalue(L, "prior", 0x21);
	lua_settablevalue(L, "next", 0x22);
	lua_settablevalue(L, "end", 0x23);
	lua_settablevalue(L, "home", 0x24);
	lua_settablevalue(L, "left", 0x25);
	lua_settablevalue(L, "up", 0x26);
	lua_settablevalue(L, "right", 0x27);
	lua_settablevalue(L, "down", 0x28);
	lua_settablevalue(L, "select", 0x29);
	lua_settablevalue(L, "print", 0x2A);
	lua_settablevalue(L, "execute", 0x2B);
	lua_settablevalue(L, "snapshot", 0x2C);
	lua_settablevalue(L, "insert", 0x2D);
	lua_settablevalue(L, "delete", 0x2E);
	lua_settablevalue(L, "help", 0x2F);
	lua_settablevalue(L, "0", 0x30);
	lua_settablevalue(L, "1", 0x31);
	lua_settablevalue(L, "2", 0x32);
	lua_settablevalue(L, "3", 0x33);
	lua_settablevalue(L, "4", 0x34);
	lua_settablevalue(L, "5", 0x35);
	lua_settablevalue(L, "6", 0x36);
	lua_settablevalue(L, "7", 0x37);
	lua_settablevalue(L, "8", 0x38);
	lua_settablevalue(L, "9", 0x39);
	lua_settablevalue(L, "a", 0x41);
	lua_settablevalue(L, "b", 0x42);
	lua_settablevalue(L, "c", 0x43);
	lua_settablevalue(L, "d", 0x44);
	lua_settablevalue(L, "e", 0x45);
	lua_settablevalue(L, "f", 0x46);
	lua_settablevalue(L, "g", 0x47);
	lua_settablevalue(L, "h", 0x48);
	lua_settablevalue(L, "i", 0x49);
	lua_settablevalue(L, "j", 0x4A);
	lua_settablevalue(L, "k", 0x4B);
	lua_settablevalue(L, "l", 0x4C);
	lua_settablevalue(L, "m", 0x4D);
	lua_settablevalue(L, "n", 0x4E);
	lua_settablevalue(L, "o", 0x4F);
	lua_settablevalue(L, "p", 0x50);
	lua_settablevalue(L, "q", 0x51);
	lua_settablevalue(L, "r", 0x52);
	lua_settablevalue(L, "s", 0x53);
	lua_settablevalue(L, "t", 0x54);
	lua_settablevalue(L, "u", 0x55);
	lua_settablevalue(L, "v", 0x56);
	lua_settablevalue(L, "w", 0x57);
	lua_settablevalue(L, "x", 0x58);
	lua_settablevalue(L, "y", 0x59);
	lua_settablevalue(L, "z", 0x5A);
	lua_settablevalue(L, "lwin", 0x5B);
	lua_settablevalue(L, "rwin", 0x5C);
	lua_settablevalue(L, "apps", 0x5D);
	lua_settablevalue(L, "sleep", 0x5F);
	lua_settablevalue(L, "numpad0", 0x60);
	lua_settablevalue(L, "numpad1", 0x61);
	lua_settablevalue(L, "numpad2", 0x62);
	lua_settablevalue(L, "numpad3", 0x63);
	lua_settablevalue(L, "numpad4", 0x64);
	lua_settablevalue(L, "numpad5", 0x65);
	lua_settablevalue(L, "numpad6", 0x66);
	lua_settablevalue(L, "numpad7", 0x67);
	lua_settablevalue(L, "numpad8", 0x68);
	lua_settablevalue(L, "numpad9", 0x69);
	lua_settablevalue(L, "multiply", 0x6A);
	lua_settablevalue(L, "add", 0x6B);
	lua_settablevalue(L, "separator", 0x6C);
	lua_settablevalue(L, "subtract", 0x6D);
	lua_settablevalue(L, "decimal", 0x6E);
	lua_settablevalue(L, "divide", 0x6F);
	lua_settablevalue(L, "f1", 0x70);
	lua_settablevalue(L, "f2", 0x71);
	lua_settablevalue(L, "f3", 0x72);
	lua_settablevalue(L, "f4", 0x73);
	lua_settablevalue(L, "f5", 0x74);
	lua_settablevalue(L, "f6", 0x75);
	lua_settablevalue(L, "f7", 0x76);
	lua_settablevalue(L, "f8", 0x77);
	lua_settablevalue(L, "f9", 0x78);
	lua_settablevalue(L, "f10", 0x79);
	lua_settablevalue(L, "f11", 0x7A);
	lua_settablevalue(L, "f12", 0x7B);
	lua_settablevalue(L, "f13", 0x7C);
	lua_settablevalue(L, "f14", 0x7D);
	lua_settablevalue(L, "f15", 0x7E);
	lua_settablevalue(L, "f16", 0x7F);
	lua_settablevalue(L, "f17", 0x80);
	lua_settablevalue(L, "f18", 0x81);
	lua_settablevalue(L, "f19", 0x82);
	lua_settablevalue(L, "f20", 0x83);
	lua_settablevalue(L, "f21", 0x84);
	lua_settablevalue(L, "f22", 0x85);
	lua_settablevalue(L, "f23", 0x86);
	lua_settablevalue(L, "f24", 0x87);
	lua_settablevalue(L, "numlock", 0x90);
	lua_settablevalue(L, "scroll", 0x91);
	lua_settablevalue(L, "lshift", 0xA0);
	lua_settablevalue(L, "rshift", 0xA1);
	lua_settablevalue(L, "lcontrol", 0xA2);
	lua_settablevalue(L, "rcontrol", 0xA3);
	lua_settablevalue(L, "lmenu", 0xA4);
	lua_settablevalue(L, "rmenu", 0xA5);
	lua_settablevalue(L, "browser_back", 0xA6);
	lua_settablevalue(L, "browser_forward", 0xA7);
	lua_settablevalue(L, "browser_refresh", 0xA8);
	lua_settablevalue(L, "browser_stop", 0xA9);
	lua_settablevalue(L, "browser_search", 0xAA);
	lua_settablevalue(L, "browser_favorites", 0xAB);
	lua_settablevalue(L, "browser_home", 0xAC);
	lua_settablevalue(L, "volume_mute", 0xAD);
	lua_settablevalue(L, "volume_down", 0xAE);
	lua_settablevalue(L, "volume_up", 0xAF);
	lua_settablevalue(L, "media_next_track", 0xB0);
	lua_settablevalue(L, "media_prev_track", 0xB1);
	lua_settablevalue(L, "media_stop", 0xB2);
	lua_settablevalue(L, "media_play_pause", 0xB3);
	lua_settablevalue(L, "launch_mail", 0xB4);
	lua_settablevalue(L, "launch_media_select", 0xB5);
	lua_settablevalue(L, "launch_app1", 0xB6);
	lua_settablevalue(L, "launch_app2", 0xB7);
	lua_settablevalue(L, "oem_1", 0xBA);
	lua_settablevalue(L, "oem_plus", 0xBB);
	lua_settablevalue(L, "oem_comma", 0xBC);
	lua_settablevalue(L, "oem_minus", 0xBD);
	lua_settablevalue(L, "oem_period", 0xBE);
	lua_settablevalue(L, "oem_2", 0xBF);
	lua_settablevalue(L, "oem_3", 0xC0);
	lua_settablevalue(L, "oem_4", 0xDB);
	lua_settablevalue(L, "oem_5", 0xDC);
	lua_settablevalue(L, "oem_6", 0xDD);
	lua_settablevalue(L, "oem_7", 0xDE);
	lua_settablevalue(L, "oem_8", 0xDF);
	lua_settablevalue(L, "oem_102", 0xE2);
	lua_settablevalue(L, "processkey", 0xE5);
	lua_settablevalue(L, "packet", 0xE7);
	lua_settablevalue(L, "attn", 0xF6);
	lua_settablevalue(L, "crsel", 0xF7);
	lua_settablevalue(L, "exsel", 0xF8);
	lua_settablevalue(L, "ereof", 0xF9);
	lua_settablevalue(L, "play", 0xFA);
	lua_settablevalue(L, "zoom", 0xFB);
	lua_settablevalue(L, "noname", 0xFC);
	lua_settablevalue(L, "pa1", 0xFD);
	lua_settablevalue(L, "oem_clear", 0xFE);

	lua_setfield(L, -2, name);
}

static luaL_Reg TEXTMODULE_DEVICE_REG[] = {
	{"key", device_key},
	{"joystick", device_joystick},
	{"mouse", device_mouse},
	{"version", device_version},
	{"font", device_font},
	{ nullptr, nullptr }
};

void luaReg_device(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_DEVICE_REG);

		luaReg_const_keycode(L, "keycode");

		lua_setfield(L, -2, name);
	}
}