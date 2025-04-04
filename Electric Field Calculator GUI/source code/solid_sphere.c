#include <math.h>
#include "electric_field.h"
double solid_sphere_field(double volume_charge_density, double radius, double distance) {
    double rho = volume_charge_density;
    double total_charge = rho * (4.0/3.0) * PI * radius * radius * radius;
    if (distance < radius) {
        return (rho * distance) / (3 * 8.85e-12);
    } else {
        return (K * fabs(total_charge)) / (distance * distance);
    }
}
