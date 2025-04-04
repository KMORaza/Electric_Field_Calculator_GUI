#include <math.h>
#include "electric_field.h"
double solid_cube_field(double volume_charge_density, double side_length, Point3D point) {
    double rho = volume_charge_density;
    double total_charge = rho * side_length * side_length * side_length;
    double r = calculate_distance((Point3D){0,0,0}, point);
    if (r < side_length/2) {
        return (rho * r) / (3 * 8.85e-12);
    } else {
        return (K * fabs(total_charge)) / (r * r);
    }
}
