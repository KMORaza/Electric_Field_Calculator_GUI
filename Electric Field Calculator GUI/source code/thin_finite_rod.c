#include <math.h>
#include "electric_field.h"
double thin_finite_rod_field(double total_charge, double length, Point3D point) {
    double lambda = total_charge / length;
    double r = sqrt(point.x * point.x + point.y * point.y);
    if (r == 0) return 0;
    double z1 = point.z - length/2;
    double z2 = point.z + length/2;
    double E = (K * lambda / r) * (1/sqrt(z1*z1 + r*r) - 1/sqrt(z2*z2 + r*r));
    return fabs(E);
}
