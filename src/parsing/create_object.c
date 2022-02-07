/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:53:28 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 10:53:54 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_sphere	*create_sphere(t_vector point, double radius, t_color color)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		return (NULL);
	sp->color = color;
	sp->point = point;
	sp->radius = radius / 2;
	return (sp);
}

t_plane	*create_plane(t_vector point, t_vector normal, t_color color)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (NULL);
	pl->point = point;
	pl->normal = vec_unit(normal);
	pl->color = color;
	return (pl);
}

t_cylinder	*create_cylinder(
	t_vector pnt, t_vector nor, double var[2], t_color clr)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		return (NULL);
	cy->point = pnt;
	cy->normal = vec_unit(nor);
	cy->radius = var[0] / 2;
	cy->height = var[1];
	cy->color = clr;
	cy->cap[TOP] = create_plane(vec_plus(cy->point,
				vec_mult_(cy->normal, cy->height)), cy->normal, cy->color);
	cy->cap[BOTTOM] = create_plane(cy->point,
			vec_mult_(cy->normal, -1), cy->color);
	return (cy);
}

t_object	*create_object(int type, void *figure)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->type = type;
	object->figure = figure;
	object->next = NULL;
	return (object);
}
