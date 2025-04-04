#include <math.h>
#include "electric_field.h"
double hollow_cube_field(double surface_charge_density, double side_length, Point3D point) {
    double r = calculate_distance((Point3D){0,0,0}, point);
    double total_charge = surface_charge_density * 6 * side_length * side_length;
    if (r < side_length/2) return 0;
    return (K * fabs(total_charge)) / (r * r);
}
