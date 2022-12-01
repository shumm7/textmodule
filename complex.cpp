#include "complex.hpp"

#include <lua.hpp>
#include <iostream>
#include <complex>
#include <cmath>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"

int complex_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__complex"))
			return 1;

		int tp = lua_type(L, 1);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TUSERDATA || tp==LUA_TNONE, 1, "number/complex expected");

		lua_Number r = 0;
		lua_Number i = 0;

		if (tp == LUA_TNUMBER || tp==LUA_TNONE) {
			r = tm_tonumber_s(L, 1, 0);
			i = tm_tonumber_s(L, 2, 0);
		}
		else if (tp == LUA_TUSERDATA && lua_iscomplex(L, 1)) {
			auto c = tm_tocomplex(L, 1);
			r = c->real();
			i = c->imag();
		}
		
		lua_pushcomplex(L, r, i);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex_polar_new(lua_State* L) {
	try {
		lua_Number r = tm_tonumber_s(L, 1, 0);
		lua_Number s = tm_tonumber_s(L, 2, 0);

		lua_pushcomplex(L, std::polar(r, s));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__real(lua_State* L) {
	try {
		lua_Complex* val = lua_tocomplex(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->real(lua_tonumber(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
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
		lua_Complex* val = lua_tocomplex(L, 1);
		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNONE || tp == LUA_TNUMBER, 2, "number/none expected");

		if (tp == LUA_TNUMBER) {
			val->imag(lua_tonumber(L, 2));
			return 0;
		}
		else if (tp == LUA_TNONE) {
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
		lua_Complex* val = lua_tocomplex(L, 1);
		lua_Wstring ret = L"(" + tostring_n(val->real()) + L"," + tostring_n(val->imag()) + L")";
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
		auto c = lua_tocomplex(L, 1);
		std::destroy_at(c);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____add(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, *val1 + *val2);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____sub(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, *val1 - *val2);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____mul(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, (*val1) * (*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____div(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, (*val1) / (*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____pow(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, std::pow(*val1, *val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____unm(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, -*val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____lt(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushboolean(L, geometry_norm(*val1) < geometry_norm(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____le(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushboolean(L, geometry_norm(*val1) <= geometry_norm(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____index(lua_State* L) {
	try {
		lua_Complex* val1 = lua_tocomplex(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TSTRING, 2, "string/number expected");

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
			case 1:
				lua_pushnumber(L, val1->real());
				return 1;
			case 2:
				lua_pushnumber(L, val1->imag());
				return 1;
			default:
				return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "r" || l == "real") {
				lua_pushnumber(L, val1->real());
				return 1;
			}
			else if (l == "i" || l == "imag") {
				lua_pushnumber(L, val1->imag());
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____newindex(lua_State* L) {
	try {
		lua_Complex* val1 = lua_tocomplex(L, 1);

		int tp = lua_type(L, 2);
		luaL_argcheck(L, tp == LUA_TNUMBER || tp == LUA_TSTRING, 2, "string/number expected");
		lua_Number value = tm_tonumber(L, 3);

		if (tp == LUA_TNUMBER) {
			switch (tm_tointeger(L, 2)) {
				case 1:
					val1->real(value);
					break;
				case 2:
					val1->imag(value);
					break;
				default:
					return 0;
			}
		}
		else if (tp == LUA_TSTRING) {
			lua_Sstring l = tm_tostring(L, 2);
			if (l == "r" || l == "real") {
				val1->real(value);
			}
			else if (l == "i" || l == "imag") {
				val1->imag(value);
			}
			else {
				return 0;
			}
		}

		lua_pushcomplex(L, *val1);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____type(lua_State* L) {
	try {
		lua_pushstring(L, "complex");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____tonumber(lua_State* L) {
	try {
		lua_Complex* val = lua_tocomplex(L, 1);
		lua_Wstring ret = tostring_n(val->real()) + L"+" + tostring_n(val->imag()) + L"i";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex____call(lua_State* L) {
	try {
		lua_Complex* val = lua_tocomplex(L, 1);
		int idx = tm_tointeger(L, 2);

		if (lua_isnoneornil(L, 3)) {
			switch (idx) {
			case 1:
				lua_pushnumber(L, val->real());
				return 1;
			case 2:
				lua_pushnumber(L, val->imag());
				return 1;
			default:
				return 0;
			}
		}
		else {
			switch (idx) {
			case 1:
				val->real(tm_tonumber(L, 3));
				return 0;
			case 2:
				val->imag(tm_tonumber(L, 3));
				return 0;
			default:
				return 0;
			}
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__abs(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushnumber(L, geometry_abs(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__arg(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

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
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushnumber(L, geometry_norm(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__conj(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::conj(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__proj(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::proj(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__polar(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushnumber(L, geometry_abs(*val1));
		lua_pushnumber(L, std::atan(val1->imag() / val1->real()));
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__acos(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::acos(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__asin(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::asin(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__atan(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::atan(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__acosh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::acosh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__asinh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::asinh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__atanh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::atanh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__cos(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::cos(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sin(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::sin(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__tan(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::tan(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__cosh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::cosh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sinh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::sinh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__tanh(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::tanh(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__exp(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::exp(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__log(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);
		lua_Complex* val2 = tm_tocomplex(L, 2);

		lua_pushcomplex(L, std::log(*val1) / std::log(*val2));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__sqrt(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_pushcomplex(L, std::sqrt(*val1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int complex__table(lua_State* L) {
	try {
		lua_Complex* val1 = tm_tocomplex(L, 1);

		lua_newtable(L);
		lua_settablevalue(L, 1, val1->real());
		lua_settablevalue(L, 2, val1->real());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_COMPLEX_REG[] = {
	{"new", complex_new},
	{"polar_new", complex_polar_new},
	{"pnew", complex_polar_new},

	{"real", complex__real},
	{"imag", complex__imag},
	{"r", complex__real},
	{"i", complex__imag},

	{"arg", complex__arg},
	{"proj", complex__proj},
	{"polar", complex__polar},

	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_COMPLEX_META_REG[] = {
	{"real", complex__real},
	{"imag", complex__imag},
	{"r", complex__real},
	{"i", complex__imag},

	{"__tostring", complex____tostring},
	{"__add", complex____add},
	{"__sub", complex____sub},
	{"__mul", complex____mul},
	{"__div", complex____div},
	{"__pow", complex____pow},
	{"__unm", complex____unm},
	{"__lt", complex____lt},
	{"__le", complex____le},
	{"__gc", complex____gc},
	//{"__index", complex____index},
	{"__newindex", complex____newindex},
	{"__type", complex____type},
	{"__tonumber", complex____tonumber},
	{"__call", complex____call},

	{"__cos", complex__cos},
	{"__sin", complex__sin},
	{"__tan", complex__tan},
	{"__cosh", complex__cosh},
	{"__sinh", complex__sinh},
	{"__tanh", complex__tanh},
	{"__acos", complex__acos},
	{"__asin", complex__asin},
	{"__atan", complex__atan},
	{"__acosh", complex__acosh},
	{"__asinh", complex__asinh},
	{"__atanh", complex__atanh},
	{"__exp", complex__exp},
	{"__log", complex__log},
	{"__sqrt", complex__sqrt},
	{"__abs", complex__abs},
	{"__norm", complex__norm},
	{"__conj", complex__conj},
	{"__table", complex__table},

	{"abs", complex__abs},
	{"norm", complex__norm},
	{"conj", complex__conj},
	{"arg", complex__arg},
	{"proj", complex__proj},
	{"polar", complex__polar},
	{nullptr, nullptr}
};

void luaReg_complex(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_COMPLEX, TEXTMODULE_COMPLEX_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_COMPLEX_REG);
		lua_setfield(L, -2, name);
	}
}