#include "electric_field.h"
#include <math.h>

double hollow_cone_field(double sigma, double R, double h, Point3D point) {
    // Placeholder: Replace with actual field calculation for hollow cone
    double k = 8.99e9;
    double area = M_PI * R * sqrt(R * R + h * h);  // Lateral surface area
    return k * sigma * area / calculate_distance((Point3D){0,0,0}, point);
}
