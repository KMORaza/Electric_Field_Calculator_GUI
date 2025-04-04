#include "electric_field.h"
#include <math.h>

double hollow_pyramid_field(double sigma, double a, double h, Point3D point) {
    // Placeholder: Replace with actual field calculation for hollow pyramid
    double k = 8.99e9;
    double area = a * sqrt(a * a / 4 + h * h) * 4;  // Lateral surface area (square base)
    return k * sigma * area / calculate_distance((Point3D){0,0,0}, point);
}
