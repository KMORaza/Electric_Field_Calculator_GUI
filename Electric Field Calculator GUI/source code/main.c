#include <gtk/gtk.h>
#include "electric_field.h"
#include <string.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *dropdown;
    GtkWidget *entry1, *entry2, *entry3, *entry4;
    GtkWidget *result_label;
} AppWidgets;

void calculate_field(GtkButton *button, gpointer data);
void update_inputs(GtkDropDown *dropdown, gpointer data);
static void activate(GtkApplication *app, gpointer user_data);

static const char *bodies[] = {
    "Infinite Wire",
    "Finite Wire",
    "Infinite Rod",
    "Thin Finite Rod",
    "Hollow Cylinder",
    "Solid Cylinder",
    "Hollow Sphere",
    "Solid Sphere",
    "Thin Sheet",
    "Hollow Cube",
    "Solid Cube",
    "Torus",
    "Coil",
    "Thin Ring",
    "Thin Disk",
    "Annular Disk",
    "Triangular Sheet",
    NULL
};

int main(int argc, char *argv[]) {
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.example.electricfield", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

static void activate(GtkApplication *app, gpointer user_data) {
    AppWidgets *widgets = g_new(AppWidgets, 1);

    widgets->window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(widgets->window), "Electric Field Calculator");
    gtk_window_set_default_size(GTK_WINDOW(widgets->window), 400, 300);
    gtk_window_set_resizable(GTK_WINDOW(widgets->window), FALSE);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_window_set_child(GTK_WINDOW(widgets->window), vbox);
    GtkStringList *string_list = gtk_string_list_new(bodies);
    widgets->dropdown = gtk_drop_down_new(G_LIST_MODEL(string_list), NULL);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(widgets->dropdown), 0);
    gtk_box_append(GTK_BOX(vbox), widgets->dropdown);

    widgets->entry1 = gtk_entry_new();
    widgets->entry2 = gtk_entry_new();
    widgets->entry3 = gtk_entry_new();
    widgets->entry4 = gtk_entry_new();
    gtk_box_append(GTK_BOX(vbox), widgets->entry1);
    gtk_box_append(GTK_BOX(vbox), widgets->entry2);
    gtk_box_append(GTK_BOX(vbox), widgets->entry3);
    gtk_box_append(GTK_BOX(vbox), widgets->entry4);

    GtkWidget *button = gtk_button_new_with_label("Calculate");
    gtk_box_append(GTK_BOX(vbox), button);

    widgets->result_label = gtk_label_new("Result will appear here");
    gtk_box_append(GTK_BOX(vbox), widgets->result_label);

    g_signal_connect(widgets->dropdown, "notify::selected", G_CALLBACK(update_inputs), widgets);
    g_signal_connect(button, "clicked", G_CALLBACK(calculate_field), widgets);
    g_signal_connect(widgets->window, "destroy", G_CALLBACK(g_application_quit), app);

    update_inputs(GTK_DROP_DOWN(widgets->dropdown), widgets);

    gtk_widget_set_visible(widgets->window, TRUE);
}

void update_inputs(GtkDropDown *dropdown, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    guint active = gtk_drop_down_get_selected(dropdown);
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "");
    gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "");
    switch (active + 1) {
        case 1: case 3:  // Infinite Wire & Infinite Rod
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Linear charge density (C/m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radial distance (m)");
            gtk_widget_set_visible(widgets->entry3, FALSE);
            gtk_widget_set_visible(widgets->entry4, FALSE);
            break;
        case 2: case 4:  // Finite Wire & Thin Finite Rod
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Total charge (C)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Length (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Point (x)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 5: case 7:  // Hollow Cylinder & Hollow Sphere
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Distance from center/axis (m)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, FALSE);
            break;
        case 6: case 8:  // Solid Cylinder & Solid Sphere
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Volume charge density (C/m³)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Distance from center/axis (m)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, FALSE);
            break;
        case 9:  // Thin Sheet
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_widget_set_visible(widgets->entry2, FALSE);
            gtk_widget_set_visible(widgets->entry3, FALSE);
            gtk_widget_set_visible(widgets->entry4, FALSE);
            break;
        case 10: case 11:  // Hollow Cube & Solid Cube
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), active == 9 ? "Surface charge density (C/m²)" : "Volume charge density (C/m³)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Side length (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Point (x)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 12:  // Torus
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Major radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Minor radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (x, y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 13:  // Coil
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Linear charge density (C/m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Number of turns");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (x, y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 14:  // Thin Ring
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Total charge (C)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Point (x)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 15:  // Thin Disk
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Point (x)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 16:  // Annular Disk
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Inner radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Outer radius (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (x, y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
        case 17:  // Triangular Sheet
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry1), "Surface charge density (C/m²)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry2), "Base length (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry3), "Height (m)");
            gtk_entry_set_placeholder_text(GTK_ENTRY(widgets->entry4), "Point (x, y, z)");
            gtk_widget_set_visible(widgets->entry3, TRUE);
            gtk_widget_set_visible(widgets->entry4, TRUE);
            break;
    }
}

void calculate_field(GtkButton *button, gpointer data) {
    AppWidgets *widgets = (AppWidgets *)data;
    guint active = gtk_drop_down_get_selected(GTK_DROP_DOWN(widgets->dropdown)) + 1;
    const char *text1 = gtk_editable_get_text(GTK_EDITABLE(widgets->entry1));
    const char *text2 = gtk_editable_get_text(GTK_EDITABLE(widgets->entry2));
    const char *text3 = gtk_editable_get_text(GTK_EDITABLE(widgets->entry3));
    const char *text4 = gtk_editable_get_text(GTK_EDITABLE(widgets->entry4));
    double val1, val2, val3, Ex, Ey, Ez, r = 0.0;  // Single declaration of r
    Point3D point = {0, 0, 0};
    char result[256];
    switch (active) {
        case 1: case 3:  // Infinite Wire & Infinite Rod
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            Ex = (active == 1 ? infinite_wire_field(val1, val2) : infinite_rod_field(val1, val2));
            Ey = Ez = 0;
            break;
        case 2: case 4:  // Finite Wire & Thin Finite Rod
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &point.x);
            sscanf(text4, "%lf %lf", &point.y, &point.z);
            val3 = (active == 2 ? finite_wire_field(val1, val2, point) : thin_finite_rod_field(val1, val2, point));
            r = calculate_distance((Point3D){0,0,0}, point);
            Ex = val3 * point.x/r; Ey = val3 * point.y/r; Ez = 0;
            break;
        case 5:  // Hollow Cylinder
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            Ex = hollow_cylinder_field(val1, val2, val3);
            Ey = Ez = 0;
            break;
        case 6:  // Solid Cylinder
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            Ex = solid_cylinder_field(val1, val2, val3);
            Ey = Ez = 0;
            break;
        case 7:  // Hollow Sphere
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            Ex = hollow_sphere_field(val1, val2, val3);
            Ey = Ez = 0;
            break;
        case 8:  // Solid Sphere
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            Ex = solid_sphere_field(val1, val2, val3);
            Ey = Ez = 0;
            break;
        case 9:  // Thin Sheet
            sscanf(text1, "%lf", &val1);
            Ez = thin_sheet_field(val1);
            Ex = Ey = 0;
            break;
        case 10: case 11:  // Hollow Cube & Solid Cube
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &point.x);
            sscanf(text4, "%lf %lf", &point.y, &point.z);
            val3 = (active == 10 ? hollow_cube_field(val1, val2, point) : solid_cube_field(val1, val2, point));
            r = calculate_distance((Point3D){0,0,0}, point);
            Ex = val3 * point.x/r; Ey = val3 * point.y/r; Ez = val3 * point.z/r;
            break;
        case 12:  // Torus
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            sscanf(text4, "%lf %lf %lf", &point.x, &point.y, &point.z);
            val3 = torus_field(val1, val2, val3, point);
            r = calculate_distance((Point3D){0,0,0}, point);
            Ex = val3 * point.x/r; Ey = val3 * point.y/r; Ez = val3 * point.z/r;
            break;
        case 13:  // Coil
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            sscanf(text4, "%lf %lf %lf", &point.x, &point.y, &point.z);
            Ez = coil_field(val1, val2, val3, point);
            Ex = Ey = 0;
            break;
        case 14:  // Thin Ring
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &point.x);
            sscanf(text4, "%lf %lf", &point.y, &point.z);
            Ez = thin_ring_field(val1, val2, point);
            Ex = Ey = 0;
            break;
        case 15:  // Thin Disk
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &point.x);
            sscanf(text4, "%lf %lf", &point.y, &point.z);
            Ez = thin_disk_field(val1, val2, point);
            Ex = Ey = 0;
            break;
        case 16:  // Annular Disk
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            sscanf(text4, "%lf %lf %lf", &point.x, &point.y, &point.z);
            Ez = annular_disk_field(val1, val2, val3, point);
            Ex = Ey = 0;
            break;
        case 17:  // Triangular Sheet
            sscanf(text1, "%lf", &val1);
            sscanf(text2, "%lf", &val2);
            sscanf(text3, "%lf", &val3);
            sscanf(text4, "%lf %lf %lf", &point.x, &point.y, &point.z);
            val3 = triangular_sheet_field(val1, val2, val3, point);
            r = calculate_distance((Point3D){0,0,0}, point);
            Ex = val3 * point.x/r; Ey = val3 * point.y/r; Ez = val3 * point.z/r;
            break;
        default:
            sprintf(result, "Invalid selection");
            gtk_label_set_text(GTK_LABEL(widgets->result_label), result);
            return;
    }
    sprintf(result, "Ex = %.2e N/C\nEy = %.2e N/C\nEz = %.2e N/C", Ex, Ey, Ez);
    gtk_label_set_text(GTK_LABEL(widgets->result_label), result);
}
