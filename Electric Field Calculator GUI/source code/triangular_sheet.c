#include <math.h>
#include "electric_field.h"
double triangular_sheet_field(double surface_charge_density, double base, double height, Point3D point) {
    double area = 0.5 * base * height;
    double total_charge = surface_charge_density * area;
    double r = calculate_distance((Point3D){0,0,0}, point);
    if (r < height/2) {
        return (surface_charge_density * r) / (2 * 8.85e-12);
    }
    return (K * total_charge) / (r * r);
}
