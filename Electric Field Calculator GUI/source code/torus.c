#include <math.h>
#include "electric_field.h"
double torus_field(double surface_charge_density, double major_radius, double minor_radius, Point3D point) {
    double r = calculate_distance((Point3D){0,0,0}, point);
    double total_charge = surface_charge_density * 2 * PI * PI * major_radius * minor_radius;
    if (r < minor_radius) return 0;
    return (K * fabs(total_charge)) / (r * r);
}
