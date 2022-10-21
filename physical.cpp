#include <iostream>


double PhysicalMUV_S(double a, double v0, double t) {
    double s0 = 0;
    double s;

    s = s0 + (v0 * t) + ((a * (t * t)) / 2);

    return s;
}
