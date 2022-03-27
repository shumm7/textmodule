#include "textmodule_geometry.h"

double g_complex_norm(std::complex<double> value) {
	return std::norm(value);
}

double g_quaternion_norm(Quat value) {
	return std::pow(value.norm(), 2);
}

double g_vector2_norm(Vector2 value) {
	return std::pow(value.norm(), 2);
}

double g_vector3_norm(Vector3 value) {
	return std::pow(value.norm(), 2);
}


double g_complex_abs(std::complex<double> value) {
	return std::abs(value);
}

double g_quaternion_abs(Quat value) {
	return value.norm();
}

double g_vector2_abs(Vector2 value) {
	return value.norm();
}

double g_vector3_abs(Vector3 value) {
	return value.norm();
}

#ifdef EIGEN_INTERNAL_U_PROTECTOR
#define U EIGEN_INTERNAL_U_PROTECTOR
#undef EIGEN_INTERNAL_U_PROTECTOR
#endif