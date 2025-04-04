#include <math.h>
#include "electric_field.h"
double hollow_sphere_field(double surface_charge_density, double radius, double distance) {
    double total_charge = surface_charge_density * 4 * PI * radius * radius;
    if (distance < radius) return 0;
    return (K * fabs(total_charge)) / (distance * distance);
}
