#include <cmath>
#include <stdexcept>

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