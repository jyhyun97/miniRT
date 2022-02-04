/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:26:36 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:27:59 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int set_sphere(t_info *info, char **split)
{
	t_sphere    *sp;
	char        **centor;
	double      radius;
	char        **color;
	t_object    *object;
	
	object = NULL;
	if (ft_strslen(split) != 3 && !check_double(split[1]))
		return (ERROR);
	centor = ft_split(split[0], ',');
	color = ft_split(split[2], ',');
	radius = ft_atod(split[1]);
	if (!centor || !color || 0 >= radius || !check_vector(centor) || !check_vector(color))
	{
		allo_free(centor);
		allo_free(color);
		return (ERROR);
	}
	sp = create_sphere(create_vector(ft_atod(centor[0]), ft_atod(centor[1]), ft_atod(centor[2])),
						radius,create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]))); 
	allo_free(centor);
	allo_free(color);
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
