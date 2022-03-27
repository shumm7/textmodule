#include "textmodule_geometry.h"

double geometry_norm(std::complex<double> value) {
	return std::norm(value);
}

double geometry_norm(Quat value) {
	return std::pow(value.w(), 2) + std::pow(value.x(), 2) + std::pow(value.y(), 2) + std::pow(value.z(), 2);
}

double geometry_norm(Vector2 value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Vector3 value) {
	return std::pow(value.norm(), 2);
}


double geometry_abs(std::complex<double> value) {
	return std::abs(value);
}

double geometry_abs(Quat value) {
	return std::sqrt(geometry_norm(value));
}

double geometry_abs(Vector2 value) {
	return value.norm();
}

double geometry_abs(Vector3 value) {
	return value.norm();
}