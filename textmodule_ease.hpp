#pragma once
double e_linear(double t, double b, double c, double d);

double e_inQuad(double t, double b, double c, double d);
double e_outQuad(double t, double b, double c, double d);
double e_inOutQuad(double t, double b, double c, double d);
double e_outInQuad(double t, double b, double c, double d);

double e_inCubic(double t, double b, double c, double d);
double e_outCubic(double t, double b, double c, double d);
double e_inOutCubic(double t, double b, double c, double d);
double e_outInCubic(double t, double b, double c, double d);

double e_inQuart(double t, double b, double c, double d);
double e_outQuart(double t, double b, double c, double d);
double e_inOutQuart(double t, double b, double c, double d);
double e_outInQuart(double t, double b, double c, double d);

double e_inQuint(double t, double b, double c, double d);
double e_outQuint(double t, double b, double c, double d);
double e_inOutQuint(double t, double b, double c, double d);
double e_outInQuint(double t, double b, double c, double d);

double e_inSine(double t, double b, double c, double d);
double e_outSine(double t, double b, double c, double d);
double e_inOutSine(double t, double b, double c, double d);
double e_outInSine(double t, double b, double c, double d);

double e_inExpo(double t, double b, double c, double d);
double e_outExpo(double t, double b, double c, double d);
double e_inOutExpo(double t, double b, double c, double d);
double e_outInExpo(double t, double b, double c, double d);

double e_inCirc(double t, double b, double c, double d);
double e_outCirc(double t, double b, double c, double d);
double e_inOutCirc(double t, double b, double c, double d);
double e_outInCirc(double t, double b, double c, double d);

double e_inElastic(double t, double b, double c, double d, double a, double p);
double e_inElastic(double t, double b, double c, double d);
double e_outElastic(double t, double b, double c, double d, double a, double p);
double e_outElastic(double t, double b, double c, double d);
double e_inOutElastic(double t, double b, double c, double d, double a, double p);
double e_inOutElastic(double t, double b, double c, double d);
double e_outInElastic(double t, double b, double c, double d, double a, double p);
double e_outInElastic(double t, double b, double c, double d);

double e_inBack(double t, double b, double c, double d, double s);
double e_inBack(double t, double b, double c, double d);
double e_outBack(double t, double b, double c, double d, double s);
double e_outBack(double t, double b, double c, double d);
double e_inOutBack(double t, double b, double c, double d, double s);
double e_inOutBack(double t, double b, double c, double d);
double e_outInBack(double t, double b, double c, double d, double s);
double e_outInBack(double t, double b, double c, double d);

double e_outBounce(double t, double b, double c, double d);
double e_inBounce(double t, double b, double c, double d);
double e_inOutBounce(double t, double b, double c, double d);
double e_outInBounce(double t, double b, double c, double d);