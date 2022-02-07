/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:26:32 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 10:31:59 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	push_cylinder(t_info *info, t_cylinder *cylinder)
{
	t_object	*object;

	object = NULL;
	if (!cylinder)
		return (ERROR);
	if (check_normal(cylinder->normal) == FALSE
		|| check_color(cylinder->color) == FALSE)
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

int	set_cylinder(t_info *info, char **split)
{
	char		**pnt;
	char		**nor;
	char		**clr;
	double		value[2];
	t_cylinder	*cylinder;

	if (ft_strslen(split) != 5 || check_double(split[2]) == FALSE
		|| check_double(split[3]) == FALSE)
		return (ERROR);
	pnt = ft_split(split[0], ',');
	nor = ft_split(split[1], ',');
	value[0] = ft_atod(split[2]);
	value[1] = ft_atod(split[3]);
	clr = ft_split(split[4], ',');
	if (!pnt || !nor || !clr || (0 >= value[0]) || (0 >= value[1])
		|| !check_vector(pnt) || !check_vector(nor) || !check_vector(clr))
		return (free_element(pnt, nor, clr));
	cylinder = create_cylinder(
			create_vector(ft_atod(pnt[0]), ft_atod(pnt[1]), ft_atod(pnt[2])),
			create_vector(ft_atod(nor[0]), ft_atod(nor[1]), ft_atod(nor[2])),
			value,
			create_color(ft_atod(clr[0]), ft_atod(clr[1]), ft_atod(clr[2])));
	free_element(pnt, nor, clr);
	return (push_cylinder(info, cylinder));
}
