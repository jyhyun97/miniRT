/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:26:40 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 13:26:57 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	push_plane(t_info *info, t_plane *plane)
{
	t_object	*object;

	object = NULL;
	if (!plane)
		return (ERROR);
	else if (check_color(plane->color) == FALSE)
	{
		free(plane);
		return (ERROR);
	}
	object = create_object(PLANE, plane);
	if (!object)
	{
		free(plane);
		return (ERROR);
	}
	push_object(info, object);
	return (SUCCESS);
}

int	set_plane(t_info *info, char **split)
{
	char		**pnt;
	char		**nor;
	char		**clr;
	t_plane		*plane;

	plane = NULL;
	pnt = ft_split(split[0], ',');
	nor = ft_split(split[1], ',');
	clr = ft_split(split[2], ',');
	if (ft_strslen(split) != 3 && (!pnt || !nor || !clr
			|| check_vector(pnt) == FALSE || check_vector(nor) == FALSE
			|| check_vector(clr) == FALSE
			|| check_normal(nor) == FALSE))
		return (free_element(pnt, nor, clr));
	plane = create_plane(
			create_vector(ft_atod(pnt[0]), ft_atod(pnt[1]), ft_atod(pnt[2])),
			create_vector(ft_atod(nor[0]), ft_atod(nor[1]), ft_atod(nor[2])),
			create_color(ft_atod(clr[0]), ft_atod(clr[1]), ft_atod(clr[2])));
	free_element(pnt, nor, clr);
	return (push_plane(info, plane));
}
