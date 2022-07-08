#pragma once
#include <complex>
#include <chrono>
#include <Eigen/Geometry>
#include <boost/multiprecision/cpp_dec_float.hpp>

typedef std::complex<double> Complex;
typedef Eigen::Quaterniond Quat;
typedef Eigen::Vector2d Vector2;
typedef Eigen::Vector3d Vector3;
typedef Eigen::Vector4d Vector4;
typedef Eigen::Matrix2d Matrix2;
typedef Eigen::Matrix3d Matrix3;
typedef Eigen::Matrix4d Matrix4;
typedef Eigen::AngleAxisd AngleAxis;

typedef struct ColorItem { std::wstring color = L""; std::wstring name = L""; std::wstring japanese = L""; std::wstring english = L""; };
typedef std::vector<ColorItem> ColorList;

typedef struct { double r; double g; double b; double a; }st_rgba;
typedef struct { unsigned char r; unsigned char g; unsigned char b; unsigned char a; }st_rgba32;
typedef struct { unsigned char b; unsigned char g; unsigned char r; unsigned char a; }st_imgpixel;
typedef struct { st_imgpixel* pixel; int width; int height; }st_img;

typedef std::chrono::utc_clock::time_point utc_clock;
typedef boost::multiprecision::number<boost::multiprecision::cpp_dec_float<1024>> dec_float;