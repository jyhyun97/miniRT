/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:56:58 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 14:48:17 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ROUNDOFF 0.0000000001

# define A 0
# define B 1
# define C 2
# define DISCRIMINANT 3
# define TOP 0
# define BOTTOM 1

//-----------------util1.c---------------------
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			is_digit(int c);
int			ft_strslen(char **strs);
double		deg_to_rad(int degree);

//-----------------util2.c---------------------
int			ft_atoi(const char *str);
double		ft_atod(char *s);

//-----------------split.c---------------------
char		**allo_free(char **rst);
char		**ft_split(char const *s, char c);

//-----------------create.c---------------------
t_cam		create_cam(t_camera camera);
t_vector	create_vector(double x, double y, double z);
t_color		create_color(double x, double y, double z);

//-----------------create_object.c---------------------
t_sphere	*create_sphere(t_vector point, double radius, t_color color);
t_plane		*create_plane(t_vector point, t_vector normal, t_color color);
t_cylinder	*create_cylinder(
				t_vector pnt, t_vector nor, double var[2], t_color clr);
t_object	*create_object(int type, void *figure);

//-----------------check.c---------------------
int			check_int(char *str);
int			check_double(char *str);
int			check_vector(char **element);
int			check_color(t_color color);
int			check_normal(char **normal);

//-----------------set.c---------------------
int			set_ambient(t_canvas *canvas, char **split);
int			camera_error_check(char **view, char **norm, char **split);
int			set_camera(t_canvas *canvas, char **split);
int			set_light(t_canvas *canvas, char **split);
t_ray		set_ray(t_cam cam, double u, double v);

//-----------------set_object.c---------------------
void		push_object(t_info *info, t_object *object);
int			free_element(char **point, char **normal, char **color);

//-----------------set_plane.c---------------------
int			push_plane(t_info *info, t_plane *plane);
int			set_plane(t_info *info, char **split);

//-----------------set_sphere.c---------------------
int			push_sphere(t_info *info, t_sphere *sp);
int			set_sphere(t_info *info, char **split);

//-----------------set_cylinder.c---------------------
int			push_cylinder(t_info *info, t_cylinder *cylinder);
int			set_cylinder(t_info *info, char **split);

//-----------------hit.c------------------
t_vector	find_cylinder_normal(t_object *curr_ob);
int			find_normal(t_object *curr_ob, t_ray ray,
				double *min, double *tmp_min);
t_object	*hit_objects(t_info *info, t_ray ray);
int			hit_shadow_ray(t_info *info, t_ray ray, t_object *curr_ob);

//-----------------hit_object.c------------------
double		hit_sphere(t_sphere *sp, t_ray ray);
double		hit_plane(t_plane *pl, t_ray ray);
double		hit_cylinder_cap(t_cylinder *cy, t_ray ray, double t);
double		hit_cylinder(t_cylinder *cy, t_ray ray);

//-----------------render.c------------------
t_color		render_color(t_object *curr_ob);
t_color		choose_color(t_info *info, t_ray ray, t_object *curr_ob);
void		draw_image(t_img *img, t_info *info);
int			rendering(t_info *info);

//-----------------mlx_util.c------------------
void		my_mlx_pixel_put(t_img *img, t_color color, int x, int y);
int			press_x(t_info *info);
int			exit_mlx(int keycode, t_info *info);

//-----------------phong.c------------------
t_color		ambient_light(t_info *info);
t_color		diffuse_light(t_info *info, t_object *curr_ob);
t_color		specular_light(t_info *info, t_ray ray, t_object *curr_ob);
int			is_shadow(t_info *info, t_object *curr_ob);
t_color		phong_model(t_info *info, t_ray ray, t_object *curr_ob);

//-----------------vector1.c---------------------
t_vector	vec_plus(t_vector vec1, t_vector vec2);
t_vector	vec_minus(t_vector vec1, t_vector vec2);
t_vector	vec_mult(t_vector vec1, t_vector vec2);
t_vector	vec_mult_(t_vector vec1, double t);
t_vector	vec_div_(t_vector vec1, double t);

//-----------------vector2.c---------------------
t_vector	vec_unit(t_vector vec);
double		vec_dot(t_vector vec1, t_vector vec2);
t_vector	vec_cross(t_vector vec1, t_vector vec2);
double		vec_len2(t_vector vec);
t_vector	vec_max(t_vector vec, double max);

//-----------------main.c------------------
void		put_err(char *str, t_info *info);
int			parsing(char *file, t_info *info);

//-----------------info.c------------------
void		free_info(t_info **info);
int			init_canvas(t_info *info);
t_info		*init_info(void);
int			save_info(t_info *info, char **split);
int			line_to_info(t_info *info, char *line);

#endif
