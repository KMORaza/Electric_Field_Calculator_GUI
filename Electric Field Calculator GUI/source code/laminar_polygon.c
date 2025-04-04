#include "electric_field.h"
#include <math.h>

double laminar_polygon_field(double sigma, double s, double n, Point3D point) {
    double k = 8.99e9;  // Coulomb's constant
    double area = (n * s * s) / (4.0 * tan(M_PI / n));  // Area of regular n-gon
    double Q = sigma * area;  // Total charge

    double r = calculate_distance((Point3D){0, 0, 0}, point);
    if (r < 1e-6) return 0;  // Avoid division by zero at center

    // Far field: Point-charge approximation
    double E = k * Q / (r * r);

    // Near field: If point is close to plane (z small), use sheet-like behavior
    double R = s / (2.0 * tan(M_PI / n));  // Radius of circumscribed circle
    if (fabs(point.z) < R && sqrt(point.x * point.x + point.y * point.y) < R) {
        E = sigma / (2.0 * 8.85e-12);  // Infinite sheet field
        E *= (area / (M_PI * R * R));  // Scale by finite area vs. circumscribed circle
    }

    return E;  // Magnitude, components split in main.c
}
