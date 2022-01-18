#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
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
t_sphere    create_sphere(t_vector point, double radius, t_color color);
t_plane     create_plane(t_vector point, t_vector normal, t_color color);
t_cylinder  create_cylinder(t_vector point, t_vector normal, double value[2], t_color color);

//-----------------check.c---------------------
int check_int(char *str);
int check_double(char *str);
int check_vector(char **element);
int check_color(t_color color);
int check_normal(t_vector normal);

//-----------------check.c---------------------
void    push_object(t_info *info, t_object *object);
int     set_ambient(t_canvas *canvas, char **split);
int     set_camera(t_canvas *canvas, char **split);
int     set_light(t_canvas *canvas, char **split);
int     set_plane(t_info *info, char **split);
int     set_sphere(t_info *info, char **split);
int     set_cylinder(t_info *info, char **split);


#endif