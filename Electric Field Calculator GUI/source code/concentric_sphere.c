#include "electric_field.h"
#include <math.h>

double concentric_sphere_field(double sigma, double R1, double R2, double r) {
    // Placeholder: Replace with actual field calculation for concentric spheres
    double k = 8.99e9;  // Coulomb's constant
    if (r < R1) return 0;  // Inside inner sphere
    if (r >= R1 && r < R2) return k * sigma * 4 * M_PI * R1 * R1 / (r * r);  // Between spheres
    return k * sigma * 4 * M_PI * (R1 * R1 + R2 * R2) / (r * r);  // Outside both
}
