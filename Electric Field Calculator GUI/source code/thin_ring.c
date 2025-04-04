#include <math.h>
#include "electric_field.h"
double thin_ring_field(double total_charge, double radius, Point3D point) {
    double r = calculate_distance((Point3D){0,0,0}, point);
    double rho = sqrt(point.x * point.x + point.y * point.y);
    if (r == 0) return 0;
    return (K * total_charge * point.z) / pow(rho*rho + point.z*point.z, 1.5);
}
