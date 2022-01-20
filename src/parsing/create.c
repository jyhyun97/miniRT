#include "../../include/minirt.h"

double  degree_to_radian(int degree)
{
    return (degree * M_PI / 180);
}

t_cam    create_cam(t_camera camera)
{
    t_cam       cam;
    t_vector    u;
    t_vector    v;
    t_vector    w;

    cam.focal_length = 5;
    cam.aspect_ratio = (double)((double)WIN_WIDTH / (double)WIN_HEIGHT);
    cam.viewport_h = cam.focal_length * 2 * tan(degree_to_radian(camera.fov / 2));
    cam.viewport_w = cam.viewport_h * cam.aspect_ratio;
    cam.origin = camera.origin;
    cam.normal = camera.normal;
    w = cam.normal;
    u = vec_unit(vec_cross(create_vector(0, 1, 0), w));
    v = vec_cross(w, u);
    // print_vector("u", u);
    // print_vector("v", v);

    cam.horizontal = vec_mult(create_vector(cam.viewport_w, 0, 0), u);
    cam.vertical = vec_mult(create_vector(0, cam.viewport_h, 0), v);
    cam.left_bottom = vec_minus(cam.origin, vec_plus(vec_div_(cam.horizontal, 2), 
                                            vec_plus(vec_div_(cam.vertical, 2), 
                                            vec_mult_(w, -1))));
    
    // printf("cam.AR %f\n", cam.aspect_ratio);
    // printf("cam.view_port_h %f\n", cam.viewport_h);
    // printf("cam.view_port_w %f\n", cam.viewport_w);
    // print_vector("cam.origin", cam.origin);
    // print_vector("cam.normal", cam.normal);
    // print_vector("cam.horizontal", cam.horizontal);
    // print_vector("cam.vertical", cam.vertical);
    // print_vector("cam.left_bottom", cam.left_bottom);
    //while (1) ;
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
    print_vector("sphere centor ", sp->point);
    printf("%f\n", sp->radius);
    return (sp);
}

t_plane     *create_plane(t_vector point, t_vector normal, t_color color)
{
    t_plane     *pl;

    pl = malloc(sizeof(t_plane));
    if (!pl)
        return (NULL);
    pl->point = point;
    pl->normal = normal;
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
    cy->normal = normal;
    cy->radius = value[0];
    cy->height = value[1];
    cy->color = color;
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