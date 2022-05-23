#pragma once
#include <complex>
#include <Eigen/Geometry>

double g_complex_norm(std::complex<double> value);
double g_quaternion_norm(Eigen::Quaterniond value);
double g_vector2_norm(Eigen::Vector2d value);
double g_vector3_norm(Eigen::Vector3d value);
double g_vector4_norm(Eigen::Vector4d value);

double g_complex_abs(std::complex<double> value);
double g_quaternion_abs(Eigen::Quaterniond value);
double g_vector2_abs(Eigen::Vector2d value);
double g_vector3_abs(Eigen::Vector3d value);
double g_vector4_abs(Eigen::Vector4d value);