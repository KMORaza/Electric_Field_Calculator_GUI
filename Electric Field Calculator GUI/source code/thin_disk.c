#include <math.h>
#include "electric_field.h"
double thin_disk_field(double surface_charge_density, double radius, Point3D point) {
    double rho = sqrt(point.x * point.x + point.y * point.y);
    double z = fabs(point.z);
    if (rho > radius) rho = radius;
    double E = (surface_charge_density / (2 * 8.85e-12)) *
               (1 - z/sqrt(z*z + radius*radius));
    return fabs(E);
}
