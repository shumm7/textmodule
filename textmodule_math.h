#pragma once
double range(double n, double min, double max);
double range(double n);

double clamp(double n, double min, double max);
double clamp(double n);

double clamp_s(double n, double min, double max);
double clamp_s(double n);

bool isinteger(double n);

double combination(int n, int r);
double factorial(int n);
double permutation(int n, int r);
double repetition_combination(int n, int r);
double repetition_permutation(int n, int r);
double circular_permutation(int n);

double bernstein(double t, int n, int i);