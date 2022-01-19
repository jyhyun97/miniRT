#include "../../include/minirt.h"

double  degree_to_radian(int degree)
{
    return (degree * M_PI / 180);
}

t_camera    create_cam(t_camera camera)
{
    t_cam   cam;

    cam.aspect_ratio = (double)((double)WIN_WIDTH / (double)WIN_HEIGHT);
    cam.viewport_h = 2 * tan(degree_to_radian(camera.fov / 2));
    cam.viewport_w = cam.viewport_h * cam.aspect_ratio;
    cam.focal_length = 1;
    cam.origin = camera.origin;
    cam.normal = camera.normal;
    

    return (cam);
}
/*
    double      viewport_w;
    double      viewport_h;
    double      aspect_ratio;
    double      focal_length;
    t_vector    origin;
    t_vector    horizontal;
    t_vector    vertical;
    t_vector    left_bottom;
    t_vector    normal;
*/


/*
    t_camera	cam;
	t_point	lookfrom = data.coor1;//카메라좌표
	t_point	lookat = data.normal_vector;//카메라 방향벡터
	t_vec		vup = vec(0, 1, 0);//y축 방향벡터?

	cam.viewport_h = 2 * tan(get_radian(data.view_degree) / 2);//
	cam.viewport_w = cam.viewport_h * canvas->aspect_ratio;
	cam.focal = vec(0, 0, 1);

	t_vec w = vunit(vminus(lookfrom,  lookat));
	t_vec u = vunit(vcross(vup, w));
	t_vec v = vcross(w, u);

	cam.orig = lookfrom;
	cam.horizontal = vmult_(vec(cam.viewport_w, 0, 0), u);//*u
	cam.vertical = vmult_(vec(0, cam.viewport_h, 0), v);//*v
	cam.left_bottom = vminus(vminus(vminus(cam.orig, vdivide(cam.horizontal, 2)), vdivide(cam.vertical, 2)), w);
	cam.normal_vector = data.normal_vector;
	return (cam);
*/

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
    sp->radius = radius;
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