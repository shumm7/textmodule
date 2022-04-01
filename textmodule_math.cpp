#include <cmath>
#include <stdexcept>
#include <vector>

#include "textmodule_lua.h"
#include "textmodule_exception.h"
#include "textmodule_math.h"

lua_Number range(lua_Number n, lua_Number min, lua_Number max) {
	if (n < min) {
		n = min;
	}
	else if (n > max) {
		n = max;
	}
	return n;
}

lua_Number range(lua_Number n) {
	return range(n, 0, 1);
}

lua_Number clamp(lua_Number n, lua_Number min, lua_Number max) {
	if (n<min || n>max)
		throw std::out_of_range(CLAMP_OUT_OF_RANGE);
	return n;
}

lua_Number clamp(lua_Number n) {
	return clamp(n, 0, 1);
}

lua_Number clamp_s(lua_Number n, lua_Number min, lua_Number max) {
	if (n < min)
		return min;
	else if (n > max)
		return max;
	return n;
}

lua_Number clamp_s(lua_Number n) {
	return clamp_s(n, 0, 1);
}

lua_Boolean isinteger(lua_Number n) {
	return static_cast<lua_Integer>(n) == n;
}

lua_Boolean isprime(lua_Integer n) {
	if (n < 2) return false;
	else if (n == 2) return true;
	else if (n % 2 == 0) return false;

	double sqrtNum = std::sqrt(n);
	for (int i = 3; i <= sqrtNum; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

lua_Number combination(lua_Integer n, lua_Integer r) {
	if (n < 0 || r < 0) throw std::invalid_argument(COMBINATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	std::vector<std::vector<lua_Number>> v(n + 1, std::vector<lua_Number>(n + 1, 0));
	for (int i = 0; i < v.size(); i++) {
		v[i][0] = 1;
		v[i][i] = 1;
	}
	for (int j = 1; j < v.size(); j++) {
		for (int k = 1; k < j; k++) {
			v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
		}
	}
	return v[n][r];
}

lua_Number factorial(lua_Integer n) {
	if (n == 0) return 1;
	if (n < 0) throw std::invalid_argument(FACTORIAL_ZERO);
	double res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}

lua_Number permutation(lua_Integer n, lua_Integer r) {
	if (n < 0 || r < 0) throw std::invalid_argument(PERMUTATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	return factorial(n) / factorial(n - r);
}

lua_Number repetition_combination(lua_Integer n, lua_Integer r) {
	if (r < 0) throw std::invalid_argument(COMBINATION_ZERO);
	if (n < 1) throw std::invalid_argument(N_LESSER_THAN_ONE);

	return combination(n + r - 1, r);
}

lua_Number repetition_permutation(lua_Integer n, lua_Integer r) {
	if (n < 0 || r < 0) throw std::invalid_argument(PERMUTATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	return std::pow(n, r);
}

lua_Number circular_permutation(lua_Integer n) {
	if (n < 1) throw std::invalid_argument(CIRCULAR_PERMUTATION_ONE);
	return factorial(n) / (double)n;
}

lua_Number bernstein(lua_Number t, lua_Integer n, lua_Integer i) {
	return combination(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
}