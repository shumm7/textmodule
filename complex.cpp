#include <lua.hpp>
#include <iostream>
#include <complex>
#include <cmath>

#include "complex.h"
#include "textmodule_lua.h"
#include "textmodule_string.h"

#define complex_check(L, n) (reinterpret_cast<std::complex<double>*>(luaL_checkudata(L, n, TEXTMODULE_COMPLEX)))

int complex_new(lua_State* L) {
	try {
		double r = 0;
		double i = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			r = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			r = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			i = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			i = 0;
		}
		else {
			return 0;
		}

		std::complex<double>* ret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		ret->real(r);
		ret->imag(i);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex_new_polar(lua_State* L) {
	try {
		double d = 0;
		double r = 0;

		if (lua_type(L, 1) == LUA_TNUMBER) {
			d = lua_tonumber(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNIL || lua_type(L, 1) == LUA_TNONE) {
			d = 0;
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			r = lua_tonumber(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNIL || lua_type(L, 2) == LUA_TNONE) {
			r = 0;
		}
		else {
			return 0;
		}

		std::complex<double>* ret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*ret = std::polar(d, r);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__real(lua_State* L) {
	try {
		std::complex<double>* val;
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = complex_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->real(lua_tonumber(L, 2));
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
			lua_pushnumber(L, val->real());
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__imag(lua_State* L) {
	try {
		std::complex<double>* val;
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = complex_check(L, 1);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TNUMBER) {
			val->imag(lua_tonumber(L, 2));
			return 0;
		}
		else if (lua_type(L, 2) == LUA_TNONE || lua_type(L, 2) == LUA_TNIL) {
			lua_pushnumber(L, val->imag());
			return 1;
		}

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____tostring(lua_State* L) {
	try {
		std::complex<double>* val;
		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val = complex_check(L, 1);
		}
		else {
			return 0;
		}

		std::wstring ret = L"(" + tostring_n(val->real()) + L"," + tostring_n(val->imag()) + L")";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____gc(lua_State* L) {
	try {
		std::complex<double>* c = complex_check(L, 1);
		if(c!=nullptr)
			free(c);

		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____add(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = *val1 + *val2;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____sub(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = *val1 - *val2;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____mul(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = (*val1) * (*val2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____div(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = (*val1) / (*val2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____pow(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::pow(*val1, *val2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____unm(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = - *val1;

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____lt(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		lua_pushboolean(L, std::abs(*val1) < std::abs(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____le(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;
		std::complex<double>* val2 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		if (lua_type(L, 2) == LUA_TUSERDATA) {
			val2 = complex_check(L, 2);
		}
		else if (lua_type(L, 2) == LUA_TNUMBER) {
			val2->real(lua_tonumber(L, 2));
			val2->imag(0);
		}
		else {
			return 0;
		}

		lua_pushboolean(L, std::abs(*val1) <= std::abs(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__abs(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		lua_pushnumber(L, std::abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__arg(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		lua_pushnumber(L, std::arg(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__norm(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		lua_pushnumber(L, std::norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__conj(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::conj(*val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__proj(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::proj(*val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__polar(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		double d = std::abs(*val1);
		double r = std::atan(val1->imag() / val1->real());

		lua_pushnumber(L, d);
		lua_pushnumber(L, r);
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__acos(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::acos(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__asin(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::asin(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__atan(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::atan(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__acosh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::acosh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__asinh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::asinh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__atanh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::atanh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__cos(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::cos(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sin(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::sin(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__tan(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::tan(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__cosh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::cosh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sinh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::sinh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__tanh(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::tanh(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__exp(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::exp(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__log(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::log(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__log10(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::log10(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sqrt(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		std::complex<double>* vret = reinterpret_cast<std::complex<double>*>(lua_newuserdata(L, sizeof(std::complex<double>)));
		vret->real(0);
		vret->imag(0);
		luaL_getmetatable(L, TEXTMODULE_COMPLEX);
		lua_setmetatable(L, -2);
		*vret = std::sqrt(*val1);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__table(lua_State* L) {
	try {
		std::complex<double>* val1 = new std::complex<double>;

		if (lua_type(L, 1) == LUA_TUSERDATA) {
			val1 = complex_check(L, 1);
		}
		else if (lua_type(L, 1) == LUA_TNUMBER) {
			val1->real(lua_tonumber(L, 1));
			val1->imag(0);
		}
		else {
			return 0;
		}

		lua_newtable(L);
		lua_pushinteger(L, 1);
		lua_pushnumber(L, val1->real());
		lua_settable(L, -3);

		lua_pushinteger(L, 2);
		lua_pushnumber(L, val1->imag());
		lua_settable(L, -3);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

void luaReg_complex(lua_State* L, const char* name, bool reg) {
	if (reg) {
		//complex
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COMPLEX_REG);
		lua_setfield(L, -2, name);

		//complex (metatable)
		luaL_newmetatable(L, TEXTMODULE_COMPLEX); //add metatable
		luaL_register(L, NULL, TEXTMODULE_COMPLEX_META_REG);
		lua_pushstring(L, "__index"); //add __index
		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COMPLEX_META_REG);
		lua_settable(L, -3);
		lua_pop(L, 1); //remove metatable
	}
}

void luaGlobal_complex(lua_State* L, const char* name, bool reg) {
	lua_newtable(L);
	luaL_register(L, NULL, TEXTMODULE_COMPLEX_REG);
	lua_setglobal(L, name);
}