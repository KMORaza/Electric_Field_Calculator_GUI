#include "electric_field.h"
#include <math.h>

double trapezoid_field(double sigma, double b1, double b2, double h, Point3D point) {
    double k = 8.99e9;  // Coulomb's constant
    double area = (b1 + b2) * h / 2.0;  // Area of trapezoid
    double Q = sigma * area;  // Total charge

    // Trapezoid in xy-plane, centered at origin, base1 at x = -h/2, base2 at x = h/2
    double r = calculate_distance((Point3D){0, 0, 0}, point);
    if (r < 1e-6) return 0;  // Avoid division by zero at center

    // Field due to a planar sheet: Integrate over trapezoid
    // Approximate as a uniform sheet with effective distance
    double E = k * Q / (r * r);  // Point-charge approximation for distance >> size

    // For points close to the plane (z dominant), use sheet-like behavior
    if (fabs(point.z) < h && fabs(point.x) < h / 2.0 && fabs(point.y) < (b1 + b2) / 4.0) {
        // Near-field: Similar to infinite sheet, adjusted for finite size
        E = sigma / (2.0 * 8.85e-12);  // Infinite sheet field (ε₀ = 8.85e-12)
        E *= (area / (h * (b1 + b2) / 2.0));  // Scale by finite area
    }

    return E;  // Magnitude, components split in main.c
}
