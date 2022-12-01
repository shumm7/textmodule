#include "matrix2.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"

int matrix2_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__matrix2"))
			return 1;

		lua_Matrix2 m;

		if (lua_isnumber(L, 1) || lua_isnone(L, 1)) {
			lua_Number p1 = tm_tonumber_s(L, 1);
			lua_Number p2 = tm_tonumber_s(L, 2);
			lua_Number p3 = tm_tonumber_s(L, 3);
			lua_Number p4 = tm_tonumber_s(L, 4);
			m << p1, p2, p3, p4;
		}
		else if (lua_isvector2(L, 1)) {
			if (tm_toboolean_s(L, 3, false)) {
				m.col(0) = *tm_tovector2_s(L, 1);
				m.col(1) = *tm_tovector2_s(L, 2);
			}
			else {
				m.row(0) = *tm_tovector2_s(L, 1);
				m.row(1) = *tm_tovector2_s(L, 2);
			}
		}
		else if (lua_iscomplex(L, 1)) {
			lua_Complex c = *tm_tocomplex(L, 1);
			m << c.real(), -c.imag(), c.imag(), c.real();
		}
		else
			return luaL_typeexception(L, 1, std::vector<std::string>{"number", "vector2"});

		lua_pushmatrix2(L, m);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_rot(lua_State* L) {
	try {
		lua_Matrix2 val;
		if(lua_isnumber(L, 1)){
			lua_Number r = tm_tonumber(L, 1);
			val = Eigen::Rotation2D(r).matrix();
		}
		else if (lua_iscomplex(L, 1)) {
			lua_Complex c = *tm_tocomplex(L, 1);
			val << c.real(), -c.imag(), c.imag(), c.real();
		}
		lua_pushmatrix2(L, val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_identity(lua_State* L) {
	try {
		lua_pushmatrix2(L, lua_Matrix2::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_zero(lua_State* L) {
	try {
		lua_pushmatrix2(L, lua_Matrix2::Zero());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_one(lua_State* L) {
	try {
		lua_pushmatrix2(L, lua_Matrix2::Ones());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_row(lua_State* L) {
	try {
		lua_Matrix2* val = tm_tomatrix2(L, 1);
		int p = tm_tonumber(L, 2);

		if (p < 1 && p>2)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector2(L, val->row(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_col(lua_State* L) {
	try {
		lua_Matrix2* val = tm_tomatrix2(L, 1);
		int p = tm_tonumber(L, 2);
		
		if (p < 1 && p>2)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector2(L, val->col(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_rowswap(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>2)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>2)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix2 ret = val;
		ret.row(p1 - 1).swap(ret.row(p2 - 1));
		lua_pushmatrix2(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_colswap(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>2)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>2)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix2 ret = val;
		ret.col(p1 - 1).swap(ret.col(p2 - 1));
		lua_pushmatrix2(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix2____tostring(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);

		lua_Wstring ret = L"["
			 L"(" + tostring_n(val(0, 0)) + L"," + tostring_n(val(0, 1)) +  L"),"
		     L"(" + tostring_n(val(1, 0)) + L"," + tostring_n(val(1, 1)) +  L")"
			 L"]";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____add(lua_State* L) {
	try {
		lua_Matrix2 val1 = *tm_tomatrix2(L, 1);
		lua_Matrix2 val2 = *tm_tomatrix2(L, 2);
		lua_Matrix2 ret = val1 + val2;

		lua_pushmatrix2(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____sub(lua_State* L) {
	try {
		lua_Matrix2 val1 = *tm_tomatrix2(L, 1);
		lua_Matrix2 val2 = *tm_tomatrix2(L, 2);
		lua_Matrix2 ret = val1 - val2;

		lua_pushmatrix2(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____mul(lua_State* L) {
	try {
		luaL_argcheck(L, lua_ismatrix2(L, 1) || lua_isnumber(L, 1) || lua_isvector2(L, 1), 1, "number/matrix2 expected");

		if (lua_ismatrix2(L, 1)) {
			luaL_argcheck(L, lua_ismatrix2(L, 2) || lua_isnumber(L, 2) || lua_isvector2(L, 2), 1, "matrix2/number/vector2 expected");

			if (lua_ismatrix2(L, 2)) { // Matrix2 * Matrix2
				Matrix2 val = (*tm_tomatrix2(L, 1))* (*tm_tomatrix2(L, 2));
				lua_pushmatrix2(L, val);
			}
			else if (lua_isnumber(L, 2)) { // Matrix2 * Number
				Matrix2 val = (*tm_tomatrix2(L, 1)) * (tm_tonumber(L, 2));
				lua_pushmatrix2(L, val);
			}
			else if (lua_isvector2(L, 2)) { // Matrix2 * Vector2
				Vector2 val = (*tm_tomatrix2(L, 1)) * (*tm_tovector2(L, 2));
				lua_pushvector2(L, val);
			}
			return 1;
		}
		else if (lua_isnumber(L, 1)) { // Number * Matrix2
			Matrix2 val = (tm_tonumber(L, 1)) * (*tm_tomatrix2(L, 2));
			lua_pushmatrix2(L, val);
			return 1;
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____div(lua_State* L) {
	try {
		Matrix2 val = (*tm_tomatrix2(L, 1)) / (tm_tonumber(L, 2));
		lua_pushmatrix2(L, val);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____unm(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);

		lua_pushmatrix2(L, -val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____type(lua_State* L) {
	try {
		lua_pushstring(L, "matrix2");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2____call(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		int row = tm_tointeger(L, 2);
		int col = tm_tointeger(L, 3);

		if (row < 1 && row>2)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (col < 1 && col>2)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		if (lua_isnoneornil(L, 4)) {
			lua_pushnumber(L, val(row-1, col-1));
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

int matrix2____gc(lua_State* L) {
	try {
		auto c = reinterpret_cast<lua_Matrix2*>(lua_touserdata(L, 1));
		std::destroy_at(c);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2__abs(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushnumber(L, geometry_abs(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2__norm(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushnumber(L, geometry_norm(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2__normalize(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushmatrix2(L, val.normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2__table(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);

		lua_newtable(L);

		lua_pushinteger(L, 1);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(0, 0));
		lua_settablevalue(L, 2, val(0, 1));
		lua_settable(L, -3);

		lua_pushinteger(L, 2);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(1, 0));
		lua_settablevalue(L, 2, val(1, 1));
		lua_settable(L, -3);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix2_transpose(lua_State* L) {
	try {
		Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushmatrix2(L, val.transpose());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_inverse(lua_State* L) {
	try {
		Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushmatrix2(L, val.inverse());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_determinant(lua_State* L) {
	try {
		Matrix2 val = *tm_tomatrix2(L, 1);
		lua_pushnumber(L, val.determinant());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_rank(lua_State* L) {
	try {
		Matrix2 val = *tm_tomatrix2(L, 1);
		Eigen::FullPivLU<lua_Matrix2> lu_decomp(val);
		lua_pushnumber(L, lu_decomp.rank());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_solve(lua_State* L) {
	try {
		lua_Matrix2 val = *tm_tomatrix2(L, 1);
		Eigen::SelfAdjointEigenSolver<lua_Matrix2> es(val);

		lua_pushmatrix2(L, es.eigenvectors());
		lua_pushvector2(L, es.eigenvalues());
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix2_linearsolve(lua_State* L) {
	try {
		lua_Matrix2 A = *tm_tomatrix2(L, 1);
		lua_Vector2 b = *tm_tovector2(L, 2);
		
		lua_Vector2 x = A.colPivHouseholderQr().solve(b);
		lua_pushvector2(L, x);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


static luaL_Reg TEXTMODULE_MATRIX2_REG[] = {
	{"new", matrix2_new},
	{"rot", matrix2_rot},
	{"identity", matrix2_identity},
	{"one", matrix2_one},
	{"zero", matrix2_zero},

	{"row", matrix2_row},
	{"col", matrix2_col},
	{"rowswap", matrix2_rowswap},
	{"colswap", matrix2_colswap},

	{"transpose", matrix2_transpose},
	{"inverse", matrix2_inverse},
	{"determinant", matrix2_determinant},
	{"rank", matrix2_rank},
	{"solve", matrix2_solve},
	{"linearsolve", matrix2_linearsolve},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_MATRIX2_META_REG[] = {
	{"row", matrix2_row},
	{"col", matrix2_col},
	{"rowswap", matrix2_rowswap},
	{"colswap", matrix2_colswap},

	{"__tostring", matrix2____tostring},

	{"__add", matrix2____add},
	{"__sub", matrix2____sub},
	{"__mul", matrix2____mul},
	{"__div", matrix2____div},
	{"__unm", matrix2____unm},
	{"__type", matrix2____type},
	{"__call", matrix2____call},
	{"__gc", matrix2____gc},

	{"__abs", matrix2__abs},
	{"__norm", matrix2__norm},
	{"__normalize", matrix2__normalize},
	{"__table", matrix2__table},

	{"abs", matrix2__abs},
	{"norm", matrix2__norm},
	{"normalize", matrix2__normalize},
	{"transpose", matrix2_transpose},
	{"inverse", matrix2_inverse},
	{"determinant", matrix2_determinant},
	{"rank", matrix2_rank},
	{"solve", matrix2_solve},
	{"linearsolve", matrix2_linearsolve},
	{nullptr, nullptr}
};

void luaReg_matrix2(lua_State* L, const char* name, bool reg) {
	if (reg) {
		luaL_newmetatable(L, TEXTMODULE_MATRIX2, TEXTMODULE_MATRIX2_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_MATRIX2_REG);
		lua_setfield(L, -2, name);
	}
}