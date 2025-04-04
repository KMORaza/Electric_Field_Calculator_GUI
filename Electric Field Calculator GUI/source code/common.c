#include <stdio.h>
#include <math.h>
#include "electric_field.h"
double calculate_distance(Point3D p1, Point3D p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double dz = p2.z - p1.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}
void print_vector(double Ex, double Ey, double Ez) {
    printf("Electric Field Vector (N/C):\n");
    printf("Ex = %.2e\n", Ex);
    printf("Ey = %.2e\n", Ey);
    printf("Ez = %.2e\n", Ez);
}
