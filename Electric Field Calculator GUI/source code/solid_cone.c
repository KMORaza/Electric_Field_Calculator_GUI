#include "electric_field.h"
#include <math.h>

double solid_cone_field(double rho, double R, double h, Point3D point) {
    // Placeholder: Replace with actual field calculation for solid cone
    double k = 8.99e9;
    double volume = (1.0/3.0) * M_PI * R * R * h;  // Volume of cone
    return k * rho * volume / calculate_distance((Point3D){0,0,0}, point);
}
