#include "qrcode.hpp"

#include <lua.hpp>
#include <iostream>
#include <vector>
#include "QR-Code-generator/qrcodegen.hpp"

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"

using qrcodegen::QrCode;
using qrcodegen::QrSegment;

#define QRCODE_WHITE false
#define QRCODE_BLACK true

QrCode get_qrcode(lua_State* L, int idx) {
	std::vector<QrSegment> segment = QrSegment::makeSegments(tm_tostring(L, idx));
	QrCode::Ecc ecc = static_cast<QrCode::Ecc>(tm_tonumber_s(L, idx + 1, 2)-1);
	int min_version = tm_tointeger_s(L, idx + 2, QrCode::MIN_VERSION);
	int max_version = tm_tointeger_s(L, idx + 3, QrCode::MAX_VERSION);
	int mask = tm_tointeger_s(L, idx + 4, -1);
	bool boost_ecc = tm_toboolean_s(L, idx + 5, true);

	return QrCode::encodeSegments(segment, ecc, min_version, max_version, mask, boost_ecc);
}

int qrcode_encode(lua_State* L) {
	QrCode qr = get_qrcode(L, 1);

	lua_newtable(L);
	for (int x = 0; x < qr.getSize(); x++) {
		lua_pushinteger(L, x + 1);
		lua_newtable(L);
		for (int y = 0; y < qr.getSize(); y++) {
			lua_settablevalue(L, y + 1, qr.getModule(x, y));
		}
		lua_settable(L, -3);
	}
	return 1;
}

int qrcode_encode_string(lua_State* L) {
	lua_Wstring black = tm_towstring(L, 1);
	lua_Wstring white = tm_towstring(L, 2);
	lua_Wstring ret;

	QrCode qr = get_qrcode(L, 3);

	for (int x = 0; x < qr.getSize(); x++) {
		for (int y = 0; y < qr.getSize(); y++) {
			if (qr.getModule(x, y))
				ret += black;
			else
				ret += white;
		}
		ret += L"\n";
	}
	lua_pushwstring(L, ret);
	return 1;
}

void luaReg_qrcode(lua_State* L, const char* name, bool reg) {
	if (reg) {
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_QRCODE_REG);
		lua_setfield(L, -2, name);
	}
}