#include "electric_field.h"
#include <math.h>

double solid_pyramid_field(double rho, double a, double h, Point3D point) {
    // Placeholder: Replace with actual field calculation for solid pyramid
    double k = 8.99e9;
    double volume = (1.0/3.0) * a * a * h;  // Volume of pyramid (square base)
    return k * rho * volume / calculate_distance((Point3D){0,0,0}, point);
}
