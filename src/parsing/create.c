#include "../../include/minirt.h"

t_vector    create_vector(double x, double y, double z)
{
    t_vector vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    return (vector);
}

t_color     create_color(double x, double y, double z)
{
    t_color color;

    color.x = x;
    color.y = y;
    color.z = z;
    return (color);
}

t_sphere    create_sphere(t_vector point, double radius, t_color color)
{
    t_sphere    sp;

    sp.color = color;
    sp.point = point;
    sp.radius = radius;
    return (sp);
}

t_plane     create_plane(t_vector point, t_vector normal, t_color color)
{
    t_plane     pl;

    pl.point = point;
    pl.normal = normal;
    pl.color = color;
    return (pl);
}

t_cylinder  create_cylinder(t_vector point, t_vector normal, double value[2], t_color color)
{
    t_cylinder cy;
    
    cy.point = point;
    cy.normal = normal;
    cy.radius = value[0];
    cy.height = value[1];
    cy.color = color;
    return (cy);
}
