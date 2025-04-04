#ifndef ELECTRIC_FIELD_H
#define ELECTRIC_FIELD_H
#define K 8.99e9
#define PI 3.14159265359
typedef struct {
    double x;
    double y;
    double z;
} Point3D;
double calculate_distance(Point3D p1, Point3D p2);
double infinite_wire_field(double linear_charge_density, double radial_distance);
double finite_wire_field(double total_charge, double length, Point3D point);
double infinite_rod_field(double linear_charge_density, double radial_distance);
double thin_finite_rod_field(double total_charge, double length, Point3D point);
double hollow_cylinder_field(double surface_charge_density, double radius, double distance);
double solid_cylinder_field(double volume_charge_density, double radius, double distance);
double hollow_sphere_field(double surface_charge_density, double radius, double distance);
double solid_sphere_field(double volume_charge_density, double radius, double distance);
double thin_sheet_field(double surface_charge_density);
double hollow_cube_field(double surface_charge_density, double side_length, Point3D point);
double solid_cube_field(double volume_charge_density, double side_length, Point3D point);
double torus_field(double surface_charge_density, double major_radius, double minor_radius, Point3D point);
double coil_field(double linear_charge_density, double radius, double turns, Point3D point);
double thin_ring_field(double total_charge, double radius, Point3D point);
double thin_disk_field(double surface_charge_density, double radius, Point3D point);
double annular_disk_field(double surface_charge_density, double inner_radius, double outer_radius, Point3D point);
double triangular_sheet_field(double surface_charge_density, double base, double height, Point3D point);
void print_vector(double Ex, double Ey, double Ez);
#endif
