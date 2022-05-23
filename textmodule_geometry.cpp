#include "textmodule_geometry.hpp"

#include <complex>
#include <Eigen/Geometry>
#include <Eigen/Dense>

double g_complex_norm(std::complex<double> value) {
	return std::norm(value);
}

double g_quaternion_norm(Eigen::Quaterniond value) {
	return std::pow(value.norm(), 2);
}

double g_vector2_norm(Eigen::Vector2d value) {
	return std::pow(value.norm(), 2);
}

double g_vector3_norm(Eigen::Vector3d value) {
	return std::pow(value.norm(), 2);
}

double g_vector4_norm(Eigen::Vector4d value) {
	return std::pow(value.norm(), 2);
}


double g_complex_abs(std::complex<double> value) {
	return std::abs(value);
}

double g_quaternion_abs(Eigen::Quaterniond value) {
	return value.norm();
}

double g_vector2_abs(Eigen::Vector2d value) {
	return value.norm();
}

double g_vector3_abs(Eigen::Vector3d value) {
	return value.norm();
}

double g_vector4_abs(Eigen::Vector4d value) {
	return value.norm();
}

#ifdef EIGEN_INTERNAL_U_PROTECTOR
#define U EIGEN_INTERNAL_U_PROTECTOR
#undef EIGEN_INTERNAL_U_PROTECTOR
#endif