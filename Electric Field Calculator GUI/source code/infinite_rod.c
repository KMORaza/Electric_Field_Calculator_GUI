#include <math.h>
#include "electric_field.h"
double infinite_rod_field(double linear_charge_density, double radial_distance) {
    if (radial_distance == 0) return 0;
    return (2 * K * fabs(linear_charge_density)) / radial_distance;
}
