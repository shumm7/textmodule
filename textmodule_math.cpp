#include "textmodule_math.hpp"

#include <iostream>
#include <cmath>
#include <vector>
#include <complex>
#include <Eigen/Dense>
#include <numeric>
#include <algorithm>

#include "textmodule_type.hpp"
#include "textmodule_exception.hpp"

using namespace Eigen;

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

Eigen::VectorXcd equation(Eigen::VectorXd number) {
	int dim = number.size();

	MatrixXd A = MatrixXd::Zero(dim, dim);
	for (int i = 0; i < dim - 1; i++)
		A(i, i + 1) = 1;

	for (int i = 0; i < dim; i++)
		A(dim - 1, i) = -number[(dim-1)-i];

	EigenSolver<MatrixXd> es(A);
	es.compute(A, false);
	
	VectorXcd ret = es.eigenvalues();
	return ret;
}


double array_size(std::vector<double> v) {
	return static_cast<double>(v.size());
}

double array_sum(std::vector<double> v) {
	return std::accumulate(v.begin(), v.end(), 0);
}

double array_mean(std::vector<double> v) {
	return array_sum(v) / array_size(v);
}

double array_max(std::vector<double> v) {
	double max = *max_element(v.begin(), v.end());
	return max;
}

double array_min(std::vector<double> v) {
	double min = *min_element(v.begin(), v.end());
	return min;
}

double array_var(std::vector<double> v) {
	double s = 0;
	double m = array_mean(v);
	for (int i = 0; i < v.size(); i++) {
		s += std::pow(v.at(i) - m, 2);
	}
	return s / array_size(v);
}

double array_uvar(std::vector<double> v) {
	double s = 0;
	double m = array_mean(v);
	for (int i = 0; i < v.size(); i++) {
		s += std::pow(v.at(i) - m, 2);
	}
	return s / (array_size(v)-1);
}

double array_median(std::vector<double> v) {
	std::sort(v.begin(), v.end());
	size_t index = array_size(v) / 2;
	double median = (v.size() % 2 == 0
		? static_cast<double>(v.at(index) + v.at(index - 1)) / 2
		: v.at(index));
	return median;
}

double array_mode(std::vector<double> v) {
	std::sort(v.begin(), v.end());
	typename decltype(v)::value_type mode{};
	size_t n{}, count{ 1 };
	for (auto iter = std::adjacent_find(v.begin(), v.end()),
		last = v.end(),
		next = v.end();
		iter != last;
		) {
		next = std::upper_bound(iter, last, *iter);
		count = std::distance(iter, next);
		if (n < count) n = count, mode = *iter;
		iter = std::adjacent_find(next, last);
	}

	return mode;
}

std::vector<double> array_normalize(std::vector<double> v) {
	double average = array_mean(v);
	double sd = std::sqrt(array_var(v));

	std::vector<double> norm_data(std::size(v));
	std::transform(v.begin(), v.end(), norm_data.begin(), [&average, &sd](const auto& e) {
		return (e - average) / sd;
	});

	return norm_data;
}