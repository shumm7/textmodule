#include "textmodule_math.hpp"

#include <cmath>

#include "textmodule_type.hpp"
#include "textmodule_exception.hpp"

double range(double n, double min, double max) {
	if (n < min) {
		n = min;
	}
	else if (n > max) {
		n = max;
	}
	return n;
}

double range(double n) {
	return range(n, 0, 1);
}

double clamp(double n, double min, double max) {
	if (n<min || n>max)
		throw std::out_of_range(CLAMP_OUT_OF_RANGE);
	return n;
}

double clamp(double n) {
	return clamp(n, 0, 1);
}

double clamp_s(double n, double min, double max) {
	if (n < min)
		return min;
	else if (n > max)
		return max;
	return n;
}

double clamp_s(double n) {
	return clamp_s(n, 0, 1);
}

bool isinteger(double n) {
	return static_cast<int>(n) == n;
}

bool isprime(int n) {
	if (n < 2) return false;
	else if (n == 2) return true;
	else if (n % 2 == 0) return false;

	double sqrtNum = std::sqrt(n);
	for (int i = 3; i <= sqrtNum; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

dec_float combination(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument(COMBINATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	std::vector<std::vector<dec_float>> v(n + 1, std::vector<dec_float>(n + 1, 0));
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

dec_float factorial(int n) {
	if (n == 0) return 1;
	if (n < 0) throw std::invalid_argument(FACTORIAL_ZERO);
	dec_float res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}

dec_float permutation(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument(PERMUTATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	return factorial(n) / factorial(n - r);
}

dec_float repetition_combination(int n, int r) {
	if (r < 0) throw std::invalid_argument(COMBINATION_ZERO);
	if (n < 1) throw std::invalid_argument(N_LESSER_THAN_ONE);

	return combination(n + r - 1, r);
}

dec_float repetition_permutation(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument(PERMUTATION_ZERO);
	if (n < r) throw std::invalid_argument(N_LESSER_THAN_R);

	return (dec_float)std::pow(n, r);
}

dec_float circular_permutation(int n) {
	if (n < 1) throw std::invalid_argument(CIRCULAR_PERMUTATION_ONE);
	return factorial(n) / n;
}

double bernstein(double t, int n, int i) {
	return (double)combination(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
}