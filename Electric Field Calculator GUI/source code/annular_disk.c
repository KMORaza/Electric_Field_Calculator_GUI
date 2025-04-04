#include <math.h>
#include "electric_field.h"
double annular_disk_field(double surface_charge_density, double inner_radius, double outer_radius, Point3D point) {
    double z = fabs(point.z);
    double E = (surface_charge_density / (2 * 8.85e-12)) *
               (z/sqrt(z*z + inner_radius*inner_radius) -
                z/sqrt(z*z + outer_radius*outer_radius));
    return fabs(E);
}
