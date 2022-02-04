#include "../../include/minirt.h"

t_cam    create_cam(t_camera camera)
{
    t_cam       cam;
    t_vector    u;
    t_vector    v;
    t_vector    w;
    t_vector    vup;

    cam.focal_length = 1;
    cam.aspect_ratio = (double)((double)WIN_WIDTH / (double)WIN_HEIGHT);
    cam.viewport_h = cam.focal_length * 2 * tan(degree_to_radian(camera.fov / 2));
    cam.viewport_w = cam.viewport_h * cam.aspect_ratio;
    cam.origin = camera.origin;
    cam.normal = vec_unit(camera.normal);
    vup = create_vector(0, 1, 0);
    if (cam.normal.x == 0 && cam.normal.y != 0 && cam.normal.z == 0)
        vup = create_vector(0, 0, 1);
    w = vec_mult_(cam.normal, -1);
    u = vec_unit(vec_cross(w, vup));
    v = vec_unit(vec_cross(u, w));

    cam.horizontal = vec_mult_(u, cam.viewport_w);
    cam.vertical = vec_mult_(v, cam.viewport_h);
    cam.left_bottom = vec_minus(cam.origin, vec_plus(vec_div_(cam.horizontal, 2), 
                                            vec_plus(vec_div_(cam.vertical, 2), 
                                            w)));
    
    return (cam);
}

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

t_sphere    *create_sphere(t_vector point, double radius, t_color color)
{
    t_sphere    *sp;

    sp = malloc(sizeof(t_sphere));
    if (!sp)
        return (NULL);
    sp->color = color;
    sp->point = point;
    sp->radius = radius / 2;
    return (sp);
}

t_plane     *create_plane(t_vector point, t_vector normal, t_color color)
{
    t_plane     *pl;

    pl = malloc(sizeof(t_plane));
    if (!pl)
        return (NULL);
    pl->point = point;
    pl->normal = vec_unit(normal);
    pl->color = color;
    return (pl);
}

t_cylinder  *create_cylinder(t_vector point, t_vector normal, double value[2], t_color color)
{
    t_cylinder  *cy;
    
    cy = malloc(sizeof(t_cylinder));
    if (!cy)
        return (NULL);
    cy->point = point;
    cy->normal = vec_unit(normal);
    cy->radius = value[0] / 2;
    cy->height = value[1];
    cy->color = color;
    cy->cap[TOP] = create_plane(vec_plus(cy->point, vec_mult_(cy->normal, cy->height)), cy->normal, cy->color);
    cy->cap[BOTTOM] = create_plane(cy->point, vec_mult_(cy->normal, -1), cy->color);
    return (cy);
}

t_object    *create_object(int type, void *figure)
{
    t_object *object;
    
    object = malloc(sizeof(t_object));
    if (!object)
        return (NULL);
    object->type = type;
    object->figure = figure;
    object->next = NULL;
    return (object);
}