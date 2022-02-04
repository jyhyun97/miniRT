/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:26:32 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:27:07 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int set_cylinder(t_info *info, char **split)
{
	char        **point;
	char        **normal;
	char        **color;
	double      value[2];
	t_cylinder  *cylinder;
	t_object    *object;
	
	object = NULL;
	if (ft_strslen(split) != 5 || check_double(split[2]) == FALSE ||
		check_double(split[3]) == FALSE)
		return (ERROR);
	point = ft_split(split[0], ',');
	normal = ft_split(split[1], ',');
	value[0] = ft_atod(split[2]);
	value[1] = ft_atod(split[3]);
	color = ft_split(split[4], ',');
	if (!point || !normal || !color || (0 >= value[0]) || (0 >= value[1]) || 
		!check_vector(point) || !check_vector(normal) || !check_vector(color))
	{
		allo_free(point);
		allo_free(normal);
		allo_free(color);
		return (ERROR);
	}
	cylinder = create_cylinder(create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2])),
		create_vector(ft_atod(normal[0]), ft_atod(normal[1]), ft_atod(normal[2])),
		value, create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2])));
	allo_free(point);
	allo_free(normal);
	allo_free(color);
	if (!cylinder)
		return (ERROR);
	if (check_normal(cylinder->normal) == FALSE || check_color(cylinder->color) == FALSE)
	{
		free(cylinder);
		return (ERROR);
	}
	object = create_object(CYLINDER, cylinder);
	if (!object)
	{
		free(cylinder);
		return (ERROR);
	}
	push_object(info, object);
	return (SUCCESS);
}
