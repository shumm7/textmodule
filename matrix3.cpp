#include "matrix3.hpp"

#include <lua.hpp>
#include <cmath>
#include <iostream>

#include "textmodule_lua.hpp"
#include "textmodule_string.hpp"
#include "textmodule_exception.hpp"
#include "textmodule_geometry.hpp"
#include "textmodule_option.hpp"


int matrix3_new(lua_State* L) {
	try {
		if (tm_callmetan(L, 1, "__matrix3"))
			return 1;

		lua_Matrix3 m;

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
			m << p1, p2, p3, p4, p5, p6, p7, p8, p9;
		}
		else if (lua_isvector3(L, 1)) {
			if (tm_toboolean_s(L, 4, false)) {
				m.col(0) = *tm_tovector3_s(L, 1);
				m.col(1) = *tm_tovector3_s(L, 2);
				m.col(2) = *tm_tovector3_s(L, 3);
			}
			else {
				m.row(0) = *tm_tovector3_s(L, 1);
				m.row(1) = *tm_tovector3_s(L, 2);
				m.row(2) = *tm_tovector3_s(L, 3);
			}
		}
		else if (lua_isquaternion(L, 1)) {
			m = *tm_toquaternion(L, 1);
		}
		else
			return luaL_typeexception(L, 1, std::vector<std::string>{"number", "vector3"});

		lua_pushmatrix3(L, m);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_rot(lua_State* L) {
	try {
		lua_Matrix3 val;
		if (lua_isnumber(L, 1)) {
			lua_Number x = tm_tonumber(L, 1);
			lua_Number y = tm_tonumber(L, 2);
			lua_Number z = tm_tonumber(L, 3);

			val = Eigen::AngleAxis(x, Eigen::Vector3d::UnitX())
				* Eigen::AngleAxis(y, Eigen::Vector3d::UnitY())
				* Eigen::AngleAxis(z, Eigen::Vector3d::UnitZ());
		}
		else if (lua_isquaternion(L, 1)) {
			val = tm_toquaternion(L, 1)->toRotationMatrix();
		}

		lua_pushmatrix3(L, val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_angleaxis(lua_State* L) {
	try {
		lua_Matrix3 val;
		
		lua_Number r = tm_tonumber(L, 1);
		lua_Vector3 v = *tm_tovector3(L, 2);

		val = Eigen::AngleAxis(r, v);
		lua_pushmatrix3(L, val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_twovectors(lua_State* L) {
	try {
		lua_Vector3* v1 = tm_tovector3(L, 1);
		lua_Vector3* v2 = tm_tovector3(L, 2);

		lua_Matrix3 mat = Quat::FromTwoVectors(*v1, *v2).toRotationMatrix();
		lua_pushmatrix3(L, mat);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_identity(lua_State* L) {
	try {
		lua_pushmatrix3(L, lua_Matrix3::Identity());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_zero(lua_State* L) {
	try {
		lua_pushmatrix3(L, lua_Matrix3::Zero());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_one(lua_State* L) {
	try {
		lua_pushmatrix3(L, lua_Matrix3::Ones());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_row(lua_State* L) {
	try {
		lua_Matrix3* val = tm_tomatrix3(L, 1);
		int p = tm_tonumber(L, 2);

		if (p < 1 && p>3)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector3(L, val->row(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_col(lua_State* L) {
	try {
		lua_Matrix3* val = tm_tomatrix3(L, 1);
		int p = tm_tonumber(L, 2);

		if (p < 1 && p>3)
			return luaL_argerror(L, 2, OUT_OF_RANGE);

		lua_pushvector3(L, val->col(p - 1));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_rowswap(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>3)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>3)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix3 ret = val;
		ret.row(p1 - 1).swap(ret.row(p2 - 1));
		lua_pushmatrix3(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_colswap(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		int p1 = tm_tointeger(L, 2);
		int p2 = tm_tointeger(L, 3);

		if (p1 < 1 || p1>3)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (p2 < 1 || p2>3)
			return luaL_argerror(L, 3, OUT_OF_RANGE);

		lua_Matrix3 ret = val;
		ret.col(p1 - 1).swap(ret.col(p2 - 1));
		lua_pushmatrix3(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix3____tostring(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);

		lua_Wstring ret = L"["
			L"(" + tostring_n(val(0, 0)) + L"," + tostring_n(val(0, 1)) + L"," + tostring_n(val(0, 2)) + L"),"
			L"(" + tostring_n(val(1, 0)) + L"," + tostring_n(val(1, 1)) + L"," + tostring_n(val(1, 2)) + L"),"
			L"(" + tostring_n(val(2, 0)) + L"," + tostring_n(val(2, 1)) + L"," + tostring_n(val(2, 2)) + L")"
			L"]";
		lua_pushwstring(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____add(lua_State* L) {
	try {
		lua_Matrix3 val1 = *tm_tomatrix3(L, 1);
		lua_Matrix3 val2 = *tm_tomatrix3(L, 2);
		lua_Matrix3 ret = val1 + val2;

		lua_pushmatrix3(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____sub(lua_State* L) {
	try {
		lua_Matrix3 val1 = *tm_tomatrix3(L, 1);
		lua_Matrix3 val2 = *tm_tomatrix3(L, 2);
		lua_Matrix3 ret = val1 - val2;

		lua_pushmatrix3(L, ret);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____mul(lua_State* L) {
	try {
		luaL_argcheck(L, lua_ismatrix3(L, 1) || lua_isnumber(L, 1) || lua_isvector3(L, 1), 1, "number/matrix3 expected");

		if (lua_ismatrix3(L, 1)) {
			luaL_argcheck(L, lua_ismatrix3(L, 2) || lua_isnumber(L, 2) || lua_isvector3(L, 2), 1, "matrix3/number/vector3 expected");

			if (lua_ismatrix3(L, 2)) { // Matrix3 * Matrix3
				lua_Matrix3 val = (*tm_tomatrix3(L, 1)) * (*tm_tomatrix3(L, 2));
				lua_pushmatrix3(L, val);
			}
			else if (lua_isnumber(L, 2)) { // Matrix3 * Number
				lua_Matrix3 val = (*tm_tomatrix3(L, 1)) * (tm_tonumber(L, 2));
				lua_pushmatrix3(L, val);
			}
			else if (lua_isvector3(L, 2)) { // Matrix3 * Vector3
				lua_Vector3 val = (*tm_tomatrix3(L, 1)) * (*tm_tovector3(L, 2));
				lua_pushvector3(L, val);
			}
			return 1;
		}
		else if (lua_isnumber(L, 1)) { // Number * Matrix3
			lua_Matrix3 val = (tm_tonumber(L, 1)) * (*tm_tomatrix3(L, 2));
			lua_pushmatrix3(L, val);
			return 1;
		}

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____div(lua_State* L) {
	try {
		lua_Matrix3 val = (*tm_tomatrix3(L, 1)) / (tm_tonumber(L, 2));
		lua_pushmatrix3(L, val);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____unm(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);

		lua_pushmatrix3(L, -val);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____type(lua_State* L) {
	try {
		lua_pushstring(L, "matrix3");
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3____call(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		int row = tm_tointeger(L, 2);
		int col = tm_tointeger(L, 3);

		if (row < 1 && row>3)
			return luaL_argerror(L, 2, OUT_OF_RANGE);
		if (col < 1 && col>3)
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

int matrix3____gc(lua_State* L) {
	try {
		auto c = reinterpret_cast<lua_Matrix3*>(lua_touserdata(L, 1));
		std::destroy_at(c);
		return 0;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3__abs(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushnumber(L, geometry_abs(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3__norm(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushnumber(L, geometry_norm(val));
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3__normalize(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushmatrix3(L, val.normalized());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3__table(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);

		lua_newtable(L);

		lua_pushinteger(L, 1);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(0, 0));
		lua_settablevalue(L, 2, val(0, 1));
		lua_settablevalue(L, 3, val(0, 2));
		lua_settable(L, -3);

		lua_pushinteger(L, 2);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(1, 0));
		lua_settablevalue(L, 2, val(1, 1));
		lua_settablevalue(L, 3, val(1, 2));
		lua_settable(L, -3);

		lua_pushinteger(L, 3);
		lua_newtable(L);
		lua_settablevalue(L, 1, val(2, 0));
		lua_settablevalue(L, 2, val(2, 1));
		lua_settablevalue(L, 3, val(2, 2));
		lua_settable(L, -3);

		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}


int matrix3_transpose(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushmatrix3(L, val.transpose());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_inverse(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushmatrix3(L, val.inverse());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_determinant(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		lua_pushnumber(L, val.determinant());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_rank(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		Eigen::FullPivLU<lua_Matrix3> lu_decomp(val);
		lua_pushnumber(L, lu_decomp.rank());
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_solve(lua_State* L) {
	try {
		lua_Matrix3 val = *tm_tomatrix3(L, 1);
		Eigen::SelfAdjointEigenSolver<lua_Matrix3> es(val);

		lua_pushmatrix3(L, es.eigenvectors());
		lua_pushvector3(L, es.eigenvalues());
		return 2;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}

int matrix3_linearsolve(lua_State* L) {
	try {
		lua_Matrix3 A = *tm_tomatrix3(L, 1);
		lua_Vector3 b = *tm_tovector3(L, 2);

		lua_Vector3 x = A.colPivHouseholderQr().solve(b);
		lua_pushvector3(L, x);
		return 1;
	}
	catch (std::exception& e) {
		luaL_error(L, e.what());
		return 1;
	}
}



static luaL_Reg TEXTMODULE_MATRIX3_REG[] = {
	{"new", matrix3_new},
	{"rot", matrix3_rot},
	{"angleaxis", matrix3_angleaxis},
	{"twovectors", matrix3_twovectors},
	{"identity", matrix3_identity},
	{"one", matrix3_one},
	{"zero", matrix3_zero},

	{"row", matrix3_row},
	{"col", matrix3_col},
	{"rowswap", matrix3_rowswap},
	{"colswap", matrix3_colswap},

	{"transpose", matrix3_transpose},
	{"inverse", matrix3_inverse},
	{"determinant", matrix3_determinant},
	{"rank", matrix3_rank},
	{"solve", matrix3_solve},
	{"linearsolve", matrix3_linearsolve},
	{ nullptr, nullptr }
};

static luaL_Reg TEXTMODULE_MATRIX3_META_REG[] = {
	{"row", matrix3_row},
	{"col", matrix3_col},
	{"rowswap", matrix3_rowswap},
	{"colswap", matrix3_colswap},

	{"__tostring", matrix3____tostring},

	{"__add", matrix3____add},
	{"__sub", matrix3____sub},
	{"__mul", matrix3____mul},
	{"__div", matrix3____div},
	{"__unm", matrix3____unm},
	{"__type", matrix3____type},
	{"__call", matrix3____call},
	{"__gc", matrix3____gc},

	{"__abs", matrix3__abs},
	{"__norm", matrix3__norm},
	{"__normalize", matrix3__normalize},
	{"__table", matrix3__table},

	{"abs", matrix3__abs},
	{"norm", matrix3__norm},
	{"normalize", matrix3__normalize},
	{"transpose", matrix3_transpose},
	{"inverse", matrix3_inverse},
	{"determinant", matrix3_determinant},
	{"rank", matrix3_rank},
	{"solve", matrix3_solve},
	{"linearsolve", matrix3_linearsolve},
	{nullptr, nullptr}
};


void luaReg_matrix3(lua_State* L, lua_Option opt) {
	if (opt["api"]["geometry"]["matrix3"]) {
		tm_debuglog_apiloaded(opt, "matrix3");
		luaL_newmetatable(L, TEXTMODULE_MATRIX3, TEXTMODULE_MATRIX3_META_REG);

		lua_newtable(L);
		luaL_register(L, NULL, TEXTMODULE_MATRIX3_REG);
		lua_setfield(L, -2, "matrix3");
	}
	else {
		tm_debuglog_apinoloaded(opt, "matrix3");
	}
}