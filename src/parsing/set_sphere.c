/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:26:36 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 10:38:23 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	push_sphere(t_info *info, t_sphere *sp)
{
	t_object	*object;

	if (!sp)
		return (ERROR);
	object = create_object(SPHERE, sp);
	if (!object)
	{
		free(sp);
		return (ERROR);
	}
	push_object(info, object);
	return (SUCCESS);
}

int	set_sphere(t_info *info, char **split)
{
	t_sphere	*sp;
	char		**ctr;
	double		radius;
	char		**clr;

	if (ft_strslen(split) != 3 && !check_double(split[1]))
		return (ERROR);
	ctr = ft_split(split[0], ',');
	clr = ft_split(split[2], ',');
	radius = ft_atod(split[1]);
	if (!ctr || !clr || 0 >= radius
		|| !check_vector(ctr) || !check_vector(clr))
		return (free_element(ctr, NULL, clr));
	sp = create_sphere(
			create_vector(ft_atod(ctr[0]), ft_atod(ctr[1]), ft_atod(ctr[2])),
			radius,
			create_color(ft_atod(clr[0]), ft_atod(clr[1]), ft_atod(clr[2])));
	free_element(ctr, NULL, clr);
	return (push_sphere(info, sp));
}
