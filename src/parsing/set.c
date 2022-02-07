/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:06:57 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 14:17:29 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	set_ambient(t_canvas *canvas, char **split)
{
	char	**element;
	t_color	color;

	if (ft_strslen(split) != 2 || !check_double(split[0]))
		return (ERROR);
	element = ft_split(split[1], ',');
	if (!check_vector(element))
	{
		allo_free(element);
		return (ERROR);
	}
	canvas->ambient = ft_atod(split[0]);
	color = create_color(ft_atod(element[0]),
			ft_atod(element[1]), ft_atod(element[2]));
	allo_free(element);
	if (0.0 > canvas->ambient || canvas->ambient > 1.0 || !check_color(color))
		return (ERROR);
	canvas->ambient_color = color;
	return (SUCCESS);
}

int	camera_error_check(char **view, char **norm, char **split)
{
	int	i;

	i = 0;
	while (view[i] != 0 || norm[i] != 0)
	{
		if (check_double(view[i]) == FALSE
			|| check_double(norm[i]) == FALSE
			|| ft_atod(norm[i]) < -1 || ft_atod(norm[i]) > 1)
			return (ERROR);
		i++;
	}
	if (i != 3 || ft_atoi(split[2]) < 0
		|| ft_atoi(split[2]) > 180 || ft_strslen(split) != 3)
		return (ERROR);
	return (SUCCESS);
}

int	set_camera(t_canvas *canvas, char **split)
{
	char	**view_vector;
	char	**norm_vector;
	int		rtn;

	view_vector = ft_split(split[0], ',');
	norm_vector = ft_split(split[1], ',');
	rtn = camera_error_check(view_vector, norm_vector, split);
	if (rtn != ERROR)
	{
		canvas->camera.origin = create_vector(ft_atod(view_vector[0]),
				ft_atod(view_vector[1]), ft_atod(view_vector[2]));
		canvas->camera.normal = create_vector(ft_atod(norm_vector[0]),
				ft_atod(norm_vector[1]), ft_atod(norm_vector[2]));
		canvas->camera.fov = ft_atoi(split[2]);
	}
	allo_free(view_vector);
	allo_free(norm_vector);
	return (rtn);
}

int	set_light(t_canvas *canvas, char **split)
{
	char	**point;
	char	**color;

	if (ft_strslen(split) != 3 || !check_double(split[1]))
		return (ERROR);
	point = ft_split(split[0], ',');
	color = ft_split(split[2], ',');
	if (!point || !color || !check_vector(point) || !check_vector(color))
	{
		allo_free(point);
		allo_free(color);
		return (ERROR);
	}
	canvas->light.light_point = create_vector(ft_atod(point[0]),
			ft_atod(point[1]), ft_atod(point[2]));
	canvas->light.brightness = ft_atod(split[1]);
	canvas->light.color = create_color(ft_atod(color[0]), ft_atod(color[1]),
			ft_atod(color[2]));
	allo_free(point);
	allo_free(color);
	if ((0 > canvas->light.brightness || canvas->light.brightness > 1.0)
		&& !check_color(canvas->light.color))
		return (ERROR);
	return (SUCCESS);
}

t_ray	set_ray(t_cam cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam.origin;
	ray.normal = vec_unit(vec_minus(vec_plus(cam.left_bottom,
					vec_plus(vec_mult_(cam.horizontal, u),
						(vec_mult_(cam.vertical, v)))), ray.origin));
	return (ray);
}
