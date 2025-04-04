#include <math.h>
#include "electric_field.h"
double coil_field(double linear_charge_density, double radius, double turns, Point3D point) {
    double r = sqrt(point.x * point.x + point.y * point.y);
    if (r < radius) {
        return (K * linear_charge_density * turns) / radius;  // Inside approximation
    }
    return (K * linear_charge_density * turns) / (r * r);  // Outside
}
