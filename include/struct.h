#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vector
{
    double x;
    double y;
    double z;
}   t_vector;

typedef struct s_vector	t_color;

typedef struct  s_light
{
    t_vector    light_point;
    t_color     color;
    double      brightness;
}   t_light;

typedef struct s_camera
{
    t_vector    view_vector;
    t_vector    normal;
    int         fov;
}   t_camera;

typedef struct  s_canvas
{
    int         width;
    int         height;
    double      aspect_ratio;
    double      ambient;
    t_color     ambient_color;
    t_light     light;
    t_camera    camera;
}   t_canvas;

typedef struct  s_object
{
    int         type;
    void        *figure;
    struct s_object    *next;
}   t_object;

typedef struct s_sphere
{
    t_vector    point;
    double      radius;
    t_color     color;
}   t_sphere;

typedef struct s_plane
{
    t_vector    point;
    t_vector    normal;
    t_color     color;
}   t_plane;

typedef struct s_cylinder
{
    t_vector    point;
    t_vector    normal;
    double      radius;
    double      height;
    t_color     color;
}   t_cylinder;

typedef struct  s_info
{
    t_canvas    *canvas;
    t_object    *object;
}   t_info;

#endif