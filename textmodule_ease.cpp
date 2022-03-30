#include <cmath>
#include <numbers>
#include "textmodule_ease.h"

#define pi std::numbers::pi
#define pow(n,m) std::pow(n,m)
#define sin(n) std::sin(n)
#define cos(n) std::cos(n)
#define tan(n) std::tan(n)
#define asin(n) std::asin(n)
#define acos(n) std::acos(n)
#define atan(n) std::atan(n)
#define sqrt(n) std::sqrt(n)
#define abs(n) std::abs(n)

double e_linear(double t, double b, double c, double d) {
    return c * t / d + b;
}


double e_inQuad(double t, double b, double c, double d) {
    t = t / d;
    return c * t * t + b;
}

double e_outQuad(double t, double b, double c, double d) {
    t = t / d;
    return -c * t * (t - 2) + b;
}

double e_inOutQuad(double t, double b, double c, double d) {
    t = t / d * 2;
    if (t < 1)
        return c / 2 * (t * t) + b;
    else
        return -c / 2 * ((t - 1) * (t - 3) - 1) + b;
}

double e_outInQuad(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outQuad(t * 2, b, c / 2, d);
    else
        return e_inQuad((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inCubic(double t, double b, double c, double d) {
    t = t / d;
    return c * pow(t, 3) + b;
}

double e_outCubic(double t, double b, double c, double d) {
    t = t / d - 1;
    return c * (pow(t, 3) + 1) + b;
}

double e_inOutCubic(double t, double b, double c, double d) {
    t = t / d * 2;
    if (t < 1)
        return c / 2 * t * t * t + b;
    else {
        t = t - 2;
        return c / 2 * (t * t * t + 2) + b;
    }
}

double e_outInCubic(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outCubic(t * 2, b, c / 2, d);
    else
        return e_inCubic((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inQuart(double t, double b, double c, double d) {
    t = t / d;
    return c * pow(t, 4) + b;
}

double e_outQuart(double t, double b, double c, double d) {
    t = t / d - 1;
    return -c * (pow(t, 4) - 1) + b;
}

double e_inOutQuart(double t, double b, double c, double d) {
    t = t / d * 2;
    if (t < 1)
        return c / 2 * pow(t, 4) + b;
    else {
        t = t - 2;
        return -c / 2 * (pow(t, 4) - 2) + b;
    }
}

double e_outInQuart(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outQuart(t * 2, b, c / 2, d);
    else
        return e_inQuart((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inQuint(double t, double b, double c, double d) {
    t = t / d;
    return c * pow(t, 5) + b;
}

double e_outQuint(double t, double b, double c, double d) {
    t = t / d - 1;
    return c * (pow(t, 5) + 1) + b;
}

double e_inOutQuint(double t, double b, double c, double d) {
    t = t / d * 2;
    if (t < 1)
        return c / 2 * pow(t, 5) + b;
    else {
        t = t - 2;
        return c / 2 * (pow(t, 5) + 2) + b;
    }
}

double e_outInQuint(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outQuint(t * 2, b, c / 2, d);
    else
        return e_inQuint((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inSine(double t, double b, double c, double d) {
    return -c * cos(t / d * (pi / 2)) + c + b;
}

double e_outSine(double t, double b, double c, double d) {
    return c * sin(t / d * (pi / 2)) + b;
}

double e_inOutSine(double t, double b, double c, double d) {
    return -c / 2 * (cos(pi * t / d) - 1) + b;
}

double e_outInSine(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outSine(t * 2, b, c / 2, d);
    else
        return e_inSine((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inExpo(double t, double b, double c, double d) {
    if (t == 0)
        return b;
    else
        return c * pow(2, 10 * (t / d - 1)) + b - c * 0.001;
}

double e_outExpo(double t, double b, double c, double d) {
    if (t == d)
        return b + c;
    else
        return c * 1.001 * (-pow(2, -10 * t / d) + 1) + b;
}

double e_inOutExpo(double t, double b, double c, double d) {
    if (t == 0)
        return b;
    if (t == d)
        return b + c;

    t = t / d * 2;
    if (t < 1)
        return c / 2 * pow(2, 10 * (t - 1)) + b - c * 0.0005;
    else {
        t = t - 1;
        return c / 2 * 1.0005 * (-pow(2, -10 * t) + 2) + b;
    }
}

double e_outInExpo(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outExpo(t * 2, b, c / 2, d);
    else
        return e_inExpo((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inCirc(double t, double b, double c, double d) {
    t = t / d;
    return(-c * (sqrt(1 - pow(t, 2)) - 1) + b);
}

double e_outCirc(double t, double b, double c, double d) {
    t = t / d - 1;
    return(c * sqrt(1 - pow(t, 2)) + b);
}

double e_inOutCirc(double t, double b, double c, double d) {
    t = t / d * 2;
    if (t < 1)
        return -c / 2 * (sqrt(1 - t * t) - 1) + b;
    else {
        t = t - 2;
        return c / 2 * (sqrt(1 - t * t) + 1) + b;
    }
}

double e_outInCirc(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outCirc(t * 2, b, c / 2, d);
    else
        return e_inCirc((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inElastic(double t, double b, double c, double d, double a, double p) {
    if (t == 0)
        return b;

    t = t / d;

    if (t == 1)
        return b + c;

    double s;
    if (a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else {
        s = p / (2 * pi) * asin(c / a);
    }

    t = t - 1;
    return -(a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b;
}

double e_inElastic(double t, double b, double c, double d) {
    if (t == 0)
        return b;

    t = t / d;

    if (t == 1)
        return b + c;
    double p = d * 0.3;

    double s = p / 4;
    double a = c;

    t = t - 1;
    return -(a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b;
}

double e_outElastic(double t, double b, double c, double d, double a, double p) {
    if (t == 0)
        return b;

    t = t / d;

    if (t == 1)
        return b + c;

    double s;

    if (a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * pi) * asin(c / a);

    return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) + c + b;
}

double e_outElastic(double t, double b, double c, double d) {
    if (t == 0)
        return b;

    t = t / d;

    if (t == 1)
        return b + c;

    double p = d * 0.3;
    double s = p / 4;
    double a = c;

    return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) + c + b;
}

double e_inOutElastic(double t, double b, double c, double d, double a, double p) {
    if (t == 0)
        return b;

    t = t / d * 2;

    if (t == 2)
        return b + c;

    double s;
    if (a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * pi) * asin(c / a);

    if (t < 1) {
        t = t - 1;
        return -0.5 * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b;
    }
    else {
        t = t - 1;
        return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) * 0.5 + c + b;
    }
}

double e_inOutElastic(double t, double b, double c, double d) {
    if (t == 0)
        return b;

    t = t / d * 2;

    if (t == 2)
        return b + c;

    double p = d * (0.3 * 1.5);
    double a = 0;
    double s;
    if (a < abs(c)) {
        a = c;
        s = p / 4;
    }
    else
        s = p / (2 * pi) * asin(c / a);

    if (t < 1) {
        t = t - 1;
        return -0.5 * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * pi) / p)) + b;
    }
    else {
        t = t - 1;
        return a * pow(2, -10 * t) * sin((t * d - s) * (2 * pi) / p) * 0.5 + c + b;
    }
}

double e_outInElastic(double t, double b, double c, double d, double a, double p) {
    if (t < d / 2)
        return e_outElastic(t * 2, b, c / 2, d, a, p);
    else
        return e_inElastic((t * 2) - d, b + c / 2, c / 2, d, a, p);
}

double e_outInElastic(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outElastic(t * 2, b, c / 2, d);
    else
        return e_inElastic((t * 2) - d, b + c / 2, c / 2, d);
}


double e_inBack(double t, double b, double c, double d, double s) {
    t = t / d;
    return c * t * t * ((s + 1) * t - s) + b;
}

double e_inBack(double t, double b, double c, double d) {
    return e_inBack(t, b, c, d, 1.70158);
}

double e_outBack(double t, double b, double c, double d, double s) {
    t = t / d - 1;
    return c * (t * t * ((s + 1) * t + s) + 1) + b;
}

double e_outBack(double t, double b, double c, double d) {
    return e_outBack(t, b, c, d, 1.70158);
}

double e_inOutBack(double t, double b, double c, double d, double s) {
    s = s * 1.525;
    t = t / d * 2;
    if (t < 1)
        return c / 2 * (t * t * ((s + 1) * t - s)) + b;
    else {
        t = t - 2;
        return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
    }
}

double e_inOutBack(double t, double b, double c, double d) {
    return e_inOutBack(t, b, c, d, 1.70158);
}

double e_outInBack(double t, double b, double c, double d, double s) {
    if (t < d / 2)
        return e_outBack(t * 2, b, c / 2, d, s);
    else
        return e_inBack((t * 2) - d, b + c / 2, c / 2, d, s);
}

double e_outInBack(double t, double b, double c, double d) {
    return e_outInBack(t, b, c, d, 1.70158);
}


double e_outBounce(double t, double b, double c, double d) {
    t = t / d;
    if (t < 1 / 2.75) {
        return c * (7.5625 * t * t) + b;
    }
    else if (t < 2 / 2.75) {
        t = t - (1.5 / 2.75);
        return c * (7.5625 * t * t + 0.75) + b;
    }
    else if (t < 2.5 / 2.75) {
        t = t - (2.25 / 2.75);
        return c * (7.5625 * t * t + 0.9375) + b;
    }
    else {
        t = t - (2.625 / 2.75);
        return c * (7.5625 * t * t + 0.984375) + b;
    }
}

double e_inBounce(double t, double b, double c, double d) {
    return c - e_outBounce(d - t, 0, c, d) + b;
}

double e_inOutBounce(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_inBounce(t * 2, 0, c, d) * 0.5 + b;
    else
        return e_outBounce(t * 2 - d, 0, c, d) * 0.5 + c * .5 + b;
}

double e_outInBounce(double t, double b, double c, double d) {
    if (t < d / 2)
        return e_outBounce(t * 2, b, c / 2, d);
    else
        return e_inBounce((t * 2) - d, b + c / 2, c / 2, d);
}