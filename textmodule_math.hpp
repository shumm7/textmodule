#pragma once
#include "textmodule_type.hpp"

double range(double n, double min, double max);
double range(double n);

double clamp(double n, double min, double max);
double clamp(double n);

double clamp_s(double n, double min, double max);
double clamp_s(double n);

bool isinteger(double n);
bool isprime(int n);

dec_float combination(int n, int r);
dec_float factorial(int n);
dec_float permutation(int n, int r);
dec_float repetition_combination(int n, int r);
dec_float repetition_permutation(int n, int r);
dec_float circular_permutation(int n);

double bernstein(double t, int n, int i);
Eigen::VectorXcd equation(Eigen::VectorXd number);

double array_sum(std::vector<double> v);
double array_mean(std::vector<double> v);
double array_max(std::vector<double> v);
double array_min(std::vector<double> v);
double array_var(std::vector<double> v);
double array_uvar(std::vector<double> v);
double array_median(std::vector<double> v);
double array_mode(std::vector<double> v);
std::vector<double> array_normalize(std::vector<double> v);