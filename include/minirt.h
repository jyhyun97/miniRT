#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "struct.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

# define PLANE 1
# define CYLINDER 2
# define SPHERE 3

# define WIN_WIDTH 1024
# define WIN_HEIGHT 640

# define KEY_PRESS 2
# define ESC_KEY   53
# define EXIT_BUTTON 17

# define SHININESS 64
# define ROUNDOFF 0.0001

//-----------------util.c---------------------
int         ft_strcmp(const char *s1, const char *s2);
size_t      ft_strlcpy(char *dst, const char *src, size_t size);
int         is_digit(int c);
int			ft_atoi(const char *str);
double      ft_atod(char *s);
int         ft_strslen(char **strs);

//-----------------split.c---------------------
char        **allo_free(char **rst);
char        **ft_split(char const *s, char c);

//-----------------create.c---------------------
t_vector    create_vector(double x, double y, double z);
t_color     create_color(double x, double y, double z);
t_sphere    *create_sphere(t_vector point, double radius, t_color color);
t_plane     *create_plane(t_vector point, t_vector normal, t_color color);
t_cylinder  *create_cylinder(t_vector point, t_vector normal, double value[2], t_color color);
t_object    *create_object(int type, void *figure);
t_cam       create_cam(t_camera camera);

//-----------------check.c---------------------
int check_int(char *str);
int check_double(char *str);
int check_vector(char **element);
int check_color(t_color color);
int check_normal(t_vector normal);

//-----------------set.c---------------------
void    push_object(t_info *info, t_object *object);
int     set_ambient(t_canvas *canvas, char **split);
int     set_camera(t_canvas *canvas, char **split);
int     set_light(t_canvas *canvas, char **split);
int     set_plane(t_info *info, char **split);
int     set_sphere(t_info *info, char **split);
int     set_cylinder(t_info *info, char **split);

//-----------------vector.c---------------------
t_vector    vec_plus(t_vector vec1, t_vector vec2);
t_vector    vec_plus_(t_vector vec1, double t);
t_vector    vec_minus(t_vector vec1, t_vector vec2);
t_vector    vec_minus_(t_vector vec1, double t);
t_vector    vec_mult(t_vector vec1, t_vector vec2);
t_vector    vec_mult_(t_vector vec1, double t);
t_vector    vec_div(t_vector vec1, t_vector vec2);
t_vector    vec_div_(t_vector vec1, double t);
t_vector    vec_unit(t_vector vec);
double      vec_dot(t_vector vec1, t_vector vec2);
t_vector    vec_cross(t_vector vec1, t_vector vec2);
double      vec_len2(t_vector vec);
t_vector    vec_max(t_vector vec, double max);

//-----------------rendering.c------------------
int         rendering(t_info *info);
void        my_mlx_pixel_put(t_img *img, t_color color, int x, int y);
t_ray       set_ray(t_cam cam, double u, double v);
void        set_image(t_img *img, t_info *info);

//-----------------main.c------------------
void    free_info(t_info **info);
void    print_vector(char *str, t_vector vec);

//-----------------hit.c------------------
t_object    *hit_objects(t_info *info, t_ray ray);
double      hit_sphere(t_sphere *sp, t_ray ray);
double      hit_plane(t_plane *pl, t_ray ray);
double      hit_cylinder(t_cylinder *cy, t_ray ray);
int         set_hit_point(t_object *curr_ob, t_ray ray, double *min, double *tmp_min);
t_vector    find_cylinder_normal(t_object *curr_ob);
#endif