#include "matrix4.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"


int matrix4_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__matrix4"))
			return 1;

		lua_Matrix4 m;

		if (lua_isnumber(L, 1) || lua_isnone(L, 1)) {
			lua_Number p1 = tm_tonumber_s(L, 1);
			lua_Number p2 = tm_tonumber_s(L, 2);
			lua_Number p3 = tm_tonumber_s(L, 3);
			lua_Number p4 = tm_tonumber_s(L, 4);
			lua_Number p5 = tm_tonumber_s(L, 5);
			lua_Number p6 = tm_tonumber_s(L, 6);
			lua_Number p7 = tm_tonumber_s(L, 7);
			lua_Number p8 = tm_tonumber_s(L, 8);
			lua_Number p9 = tm_tonumber_s(L, 9);
			lua_Number p10 = tm_tonumber_s(L, 10);
			lua_Number p11 = tm_tonumber_s(L, 11);
			lua_Number p12 = tm_tonumber_s(L, 12);
			lua_Number p13 = tm_tonumber_s(L, 13);
			lua_Number p14 = tm_tonumber_s(L, 14);
			lua_Number p15 = tm_tonumber_s(L, 15);
			lua_Number p16 = tm_tonumber_s(L, 16);
			m << p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16;
		}
		else if (lua_isvector4(L, 1)) {
			if (tm_toboolean_s(L, 4, false)) {
				m.col(0) = *tm_tovector4_s(L, 1);
				m.col(1) = *tm_tovector4_s(L, 2);
				m.col(2) = *tm_tovector4_s(L, 3);
				m.col(3) = *tm_tovector4_s(L, 4);
			}
			else {
				m.row(0) = *tm_tovector4_s(L, 1);
				m.row(1) = *tm_tovector4_s(L, 2);
				m.row(2) = *tm_tovector4_s(L, 3);
				m.row(3) = *tm_tovector4_s(L, 4);
			}
		}
		else
			return luaL_typeexception(L, 1, std::vector<std::string>{"number", "vector4"});

		lua_pushmatrix4(L, m);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_identity(lua_State* L) {
	try {
		lua_pushmatrix4(L, lua_Matrix4::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_zero(lua_State* L) {
	try {
		lua_pushmatrix4(L, lua_Matrix4::Zero());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_one(lua_State* L) {
	try {
		lua_pushmatrix4(L, lua_Matrix4::Ones());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_row(lua_State* L) {
	try {
		lua_Matrix4* val = tm_tomatrix4(L, 1);
		int p = tm_tonumber(L, 2);

		if (p < 1 && p>4)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector4(L, val->row(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_col(lua_State* L) {
	try {
		lua_Matrix4* val = tm_tomatrix4(L, 1);
		int p = tm_tonumber(L, 2);

		if (p < 1 && p>4)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector4(L, val->col(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_rowswap(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>4)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>4)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix4 ret = val;
		ret.row(p1 - 1).swap(ret.row(p2 - 1));
		lua_pushmatrix4(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_colswap(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>4)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>4)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix4 ret = val;
		ret.col(p1 - 1).swap(ret.col(p2 - 1));
		lua_pushmatrix4(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix4____tostring(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);

		lua_Wstring ret = L"["
			L"(" + tostring_n(val(0, 0)) + L"," + tostring_n(val(0, 1)) + L"," + tostring_n(val(0, 2)) + L"," + tostring_n(val(0, 3)) + L"),"
			L"(" + tostring_n(val(1, 0)) + L"," + tostring_n(val(1, 1)) + L"," + tostring_n(val(1, 2)) + L"," + tostring_n(val(1, 3)) + L"),"
			L"(" + tostring_n(val(2, 0)) + L"," + tostring_n(val(2, 1)) + L"," + tostring_n(val(2, 2)) + L"," + tostring_n(val(2, 3)) + L"),"
			L"(" + tostring_n(val(3, 0)) + L"," + tostring_n(val(3, 1)) + L"," + tostring_n(val(3, 2)) + L"," + tostring_n(val(3, 3)) + L")"
			L"]";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____add(lua_State* L) {
	try {
		lua_Matrix4 val1 = *tm_tomatrix4(L, 1);
		lua_Matrix4 val2 = *tm_tomatrix4(L, 2);
		lua_Matrix4 ret = val1 + val2;

		lua_pushmatrix4(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____sub(lua_State* L) {
	try {
		lua_Matrix4 val1 = *tm_tomatrix4(L, 1);
		lua_Matrix4 val2 = *tm_tomatrix4(L, 2);
		lua_Matrix4 ret = val1 - val2;

		lua_pushmatrix4(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____mul(lua_State* L) {
	try {
		luaL_argcheck(L, lua_ismatrix4(L, 1) || lua_isnumber(L, 1) || lua_isvector4(L, 1), 1, "number/matrix4 expected");

		if (lua_ismatrix4(L, 1)) {
			luaL_argcheck(L, lua_ismatrix4(L, 2) || lua_isnumber(L, 2) || lua_isvector4(L, 2), 1, "matrix4/number/vector4 expected");

			if (lua_ismatrix4(L, 2)) { // Matrix4 * Matrix4
				lua_Matrix4 val = (*tm_tomatrix4(L, 1)) * (*tm_tomatrix4(L, 2));
				lua_pushmatrix4(L, val);
			}
			else if (lua_isnumber(L, 2)) { // Matrix4 * Number
				lua_Matrix4 val = (*tm_tomatrix4(L, 1)) * (tm_tonumber(L, 2));
				lua_pushmatrix4(L, val);
			}
			else if (lua_isvector4(L, 2)) { // Matrix4 * Vector4
				lua_Vector4 val = (*tm_tomatrix4(L, 1)) * (*tm_tovector4(L, 2));
				lua_pushvector4(L, val);
			}
			return 1;
		}
		else if (lua_isnumber(L, 1)) { // Number * Matrix3
			lua_Matrix4 val = (tm_tonumber(L, 1)) * (*tm_tomatrix4(L, 2));
			lua_pushmatrix4(L, val);
			return 1;
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____div(lua_State* L) {
	try {
		lua_Matrix4 val = (*tm_tomatrix4(L, 1)) / (tm_tonumber(L, 2));
		lua_pushmatrix4(L, val);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____unm(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);

		lua_pushmatrix4(L, -val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____type(lua_State* L) {
	try {
		lua_pushstring(L, "matrix4");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____call(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		int row = tm_tointeger(L, 2);
		int col = tm_tointeger(L, 3);

		if (row < 1 && row>4)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (col < 1 && col>4)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		if (lua_isnoneornil(L, 4)) {
			lua_pushnumber(L, val(row - 1, col - 1));
			return 1;
		}
		else {
			val(row - 1, col - 1) = tm_tonumber(L, 4);
			return 0;
		}
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4____gc(lua_State* L) {
	try {
		auto c = reinterpret_cast<lua_Matrix4*>(lua_touserdata(L, 1));
		std::destroy_at(c);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4__abs(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushnumber(L, geometry_abs(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4__norm(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushnumber(L, geometry_norm(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4__normalize(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushmatrix4(L, val.normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4__table(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);

		lua_newtable(L);

		lua_pushinteger(L, 1);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(0, 0));
		lua_settablevalue(L, 2, val(0, 1));
		lua_settablevalue(L, 3, val(0, 2));
		lua_settablevalue(L, 4, val(0, 3));
		lua_settable(L, -3);

		lua_pushinteger(L, 2);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(1, 0));
		lua_settablevalue(L, 2, val(1, 1));
		lua_settablevalue(L, 3, val(1, 2));
		lua_settablevalue(L, 4, val(1, 3));
		lua_settable(L, -3);

		lua_pushinteger(L, 3);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(2, 0));
		lua_settablevalue(L, 2, val(2, 1));
		lua_settablevalue(L, 3, val(2, 2));
		lua_settablevalue(L, 4, val(2, 3));
		lua_settable(L, -3);

		lua_pushinteger(L, 4);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(3, 0));
		lua_settablevalue(L, 2, val(3, 1));
		lua_settablevalue(L, 3, val(3, 2));
		lua_settablevalue(L, 4, val(3, 3));
		lua_settable(L, -3);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix4_transpose(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushmatrix4(L, val.transpose());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_inverse(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushmatrix4(L, val.inverse());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_determinant(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		lua_pushnumber(L, val.determinant());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_rank(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		Eigen::FullPivLU<lua_Matrix4> lu_decomp(val);
		lua_pushnumber(L, lu_decomp.rank());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_solve(lua_State* L) {
	try {
		lua_Matrix4 val = *tm_tomatrix4(L, 1);
		Eigen::SelfAdjointEigenSolver<lua_Matrix4> es(val);

		lua_pushmatrix4(L, es.eigenvectors());
		lua_pushvector4(L, es.eigenvalues());
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix4_linearsolve(lua_State* L) {
	try {
		lua_Matrix4 A = *tm_tomatrix4(L, 1);
		lua_Vector4 b = *tm_tovector4(L, 2);

		lua_Vector4 x = A.colPivHouseholderQr().solve(b);
		lua_pushvector4(L, x);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}



static luaL_Reg TEXTMODULE_MATRIX4_REG[] = {
	{"new", matrix4_new},
	{"identity", matrix4_identity},
	{"one", matrix4_one},
	{"zero", matrix4_zero},

	{"row", matrix4_row},
	{"col", matrix4_col},
	{"rowswap", matrix4_rowswap},
	{"colswap", matrix4_colswap},

	{"transpose", matrix4_transpose},
	{"inverse", matrix4_inverse},
	{"determinant", matrix4_determinant},
	{"rank", matrix4_rank},
	{"solve", matrix4_solve},
	{"linearsolve", matrix4_linearsolve},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_MATRIX4_META_REG[] = {
	{"row", matrix4_row},
	{"col", matrix4_col},
	{"rowswap", matrix4_rowswap},
	{"colswap", matrix4_colswap},

	{"__tostring", matrix4____tostring},

	{"__add", matrix4____add},
	{"__sub", matrix4____sub},
	{"__mul", matrix4____mul},
	{"__div", matrix4____div},
	{"__unm", matrix4____unm},
	{"__type", matrix4____type},
	{"__call", matrix4____call},
	{"__gc", matrix4____gc},

	{"__abs", matrix4__abs},
	{"__norm", matrix4__norm},
	{"__normalize", matrix4__normalize},
	{"__table", matrix4__table},

	{"abs", matrix4__abs},
	{"norm", matrix4__norm},
	{"normalize", matrix4__normalize},
	{"transpose", matrix4_transpose},
	{"inverse", matrix4_inverse},
	{"determinant", matrix4_determinant},
	{"rank", matrix4_rank},
	{"solve", matrix4_solve},
	{"linearsolve", matrix4_linearsolve},
	{nullptr, nullptr}
};


void luaReg_matrix4(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_MATRIX4, TEXTMODULE_MATRIX4_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_MATRIX4_REG);
		lua_setfield(L, -2, name);
	}
}