#include <math.h>
#include "electric_field.h"
double solid_cylinder_field(double volume_charge_density, double radius, double distance) {
    double rho = volume_charge_density;
    if (distance < radius) {
        return (rho * distance) / (2 * 8.85e-12);
    } else {
        double total_charge = rho * PI * radius * radius;
        return (K * fabs(total_charge)) / (distance * distance);
    }
}
