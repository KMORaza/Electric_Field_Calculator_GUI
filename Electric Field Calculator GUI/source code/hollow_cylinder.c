#include <math.h>
#include "electric_field.h"
double hollow_cylinder_field(double surface_charge_density, double radius, double distance) {
    if (distance < radius) return 0;
    return (K * 2 * PI * radius * fabs(surface_charge_density)) / distance;
}
