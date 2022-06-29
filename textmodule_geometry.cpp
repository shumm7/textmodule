#include "textmodule_geometry.hpp"

#include <complex>
#include <Eigen/Geometry>
#include <Eigen/Dense>

double geometry_norm(std::complex<double> value) {
	return std::norm(value);
}

double geometry_norm(Eigen::Quaterniond value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Eigen::Vector2d value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Eigen::Vector3d value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Eigen::Vector4d value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Eigen::Matrix2d value) {
	return std::pow(value.norm(), 2);
}

double geometry_norm(Eigen::Matrix3d value) {
	return std::pow(value.norm(), 2);
}


double geometry_abs(std::complex<double> value) {
	return std::abs(value);
}

double geometry_abs(Eigen::Quaterniond value) {
	return value.norm();
}

double geometry_abs(Eigen::Vector2d value) {
	return value.norm();
}

double geometry_abs(Eigen::Vector3d value) {
	return value.norm();
}

double geometry_abs(Eigen::Vector4d value) {
	return value.norm();
}

double geometry_abs(Eigen::Matrix2d value) {
	return value.norm();
}

double geometry_abs(Eigen::Matrix3d value) {
	return value.norm();
}

#ifdef EIGEN_INTERNAL_U_PROTECTOR
#define U EIGEN_INTERNAL_U_PROTECTOR
#undef EIGEN_INTERNAL_U_PROTECTOR
#endif