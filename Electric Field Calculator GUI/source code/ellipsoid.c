#include "electric_field.h"
#include <math.h>

double ellipsoid_field(double rho, double a, double b, double c, Point3D point) {
    double k = 8.99e9;  // Coulomb's constant
    double volume = (4.0 / 3.0) * M_PI * a * b * c;  // Volume of ellipsoid
    double Q = rho * volume;  // Total charge

    // Distance from center to point
    double r = calculate_distance((Point3D){0, 0, 0}, point);
    if (r < sqrt(a * a + b * b + c * c)) {  // Rough check if inside (simplified)
        // Inside: Field requires numerical integration or special functions
        // For simplicity, approximate as zero (valid only for highly symmetric cases)
        return 0;
    }

    // Outside: Approximate field magnitude using point-charge-like behavior
    // Adjusted for ellipsoidal shape (effective radius based on geometric mean)
    double r_eff = pow(a * b * c, 1.0 / 3.0);  // Effective radius
    double E = k * Q / (r * r);  // Base magnitude

    // Correction factor for ellipsoidal asymmetry (simplified)
    double factor = (a + b + c) / (3.0 * r_eff);
    E *= factor;

    return E;  // Magnitude, components split in main.c
}
