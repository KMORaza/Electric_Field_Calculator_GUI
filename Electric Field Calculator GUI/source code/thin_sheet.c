#include <math.h>
#include "electric_field.h"
double thin_sheet_field(double surface_charge_density) {
    return fabs(surface_charge_density) / (2 * 8.85e-12);
}
