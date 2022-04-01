#include <cmath>
#include <stdexcept>
#include <vector>

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
		throw std::out_of_range("The value which you tried to clamp is out of range.");
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

double combination(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument("combination less than 0 undefined");
	if (n < r) throw std::invalid_argument("n must be greater than or equal to r");

	std::vector<std::vector<double>> v(n + 1, std::vector<double>(n + 1, 0));
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

double factorial(int n) {
	if (n == 0) return 1;
	if (n < 0) throw std::invalid_argument("factorial less than 0 is undefined");
	double res = 1;
	for (int i = 1; i <= n; i++)
		res *= i;
	return res;
}

double permutation(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument("permutation less than 0 undefined");
	if (n < r) throw std::invalid_argument("n must be greater than or equal to r");

	return factorial(n) / factorial(n - r);
}

double repetition_combination(int n, int r) {
	if (r < 0) throw std::invalid_argument("combination less than 0 undefined");
	if (n < 1) throw std::invalid_argument("n must be greater than or equal to 1");

	return combination(n + r - 1, r);
}

double repetition_permutation(int n, int r) {
	if (n < 0 || r < 0) throw std::invalid_argument("permutation less than 0 undefined");
	if (n < r) throw std::invalid_argument("n must be greater than or equal to r");

	return std::pow(n, r);
}

double circular_permutation(int n) {
	if (n < 1) throw std::invalid_argument("circular permutation less than 1 is undefined");
	return factorial(n) / (double)n;
}

double bernstein(double t, int n, int i) {
	return combination(n, i) * std::pow(t, i) * std::pow(1 - t, n - i);
}