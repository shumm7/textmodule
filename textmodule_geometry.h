#pragma once
#include "complex.h"
#include "quaternion.h"
#include "vector2.h"
#include "vector3.h"

double geometry_norm(std::complex<double> value);
double geometry_norm(Quat value);
double geometry_norm(Vector2 value);
double geometry_norm(Vector3 value);

double geometry_abs(std::complex<double> value);
double geometry_abs(Quat value);
double geometry_abs(Vector2 value);
double geometry_abs(Vector3 value);