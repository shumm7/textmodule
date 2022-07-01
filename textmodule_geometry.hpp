#pragma once
#include <complex>
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/LU>

double geometry_norm(std::complex<double> value);
double geometry_norm(Eigen::Quaterniond value);
double geometry_norm(Eigen::Vector2d value);
double geometry_norm(Eigen::Vector3d value);
double geometry_norm(Eigen::Vector4d value);
double geometry_norm(Eigen::Matrix2d value);
double geometry_norm(Eigen::Matrix3d value);
double geometry_norm(Eigen::Matrix4d value);

double geometry_abs(std::complex<double> value);
double geometry_abs(Eigen::Quaterniond value);
double geometry_abs(Eigen::Vector2d value);
double geometry_abs(Eigen::Vector3d value);
double geometry_abs(Eigen::Vector4d value);
double geometry_abs(Eigen::Matrix2d value);
double geometry_abs(Eigen::Matrix3d value);
double geometry_abs(Eigen::Matrix4d value);