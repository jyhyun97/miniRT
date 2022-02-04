/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:32:52 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:01:46 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector	find_cylinder_normal(t_object *curr_ob)
{
	t_vector	normal;
	t_cylinder	*cy;
	t_vector	oa;
	double		len;
	double		l;

	cy = curr_ob->figure;
	oa = vec_minus(curr_ob->point, cy->point);
	len = sqrt(vec_len2(oa) - pow(vec_dot(oa, cy->normal), 2));
	if (len <= cy->radius - ROUNDOFF)
	{
		if (sqrt(vec_len2(oa)) > cy->height - ROUNDOFF)
			normal = cy->normal;
		else
			normal = vec_mult_(cy->normal, -1);
		return (normal);
	}
	l = vec_dot(oa, cy->normal);
	normal = vec_unit(vec_minus(oa, vec_mult_(cy->normal, l)));
	return (normal);
}

int	find_normal(t_object *curr_ob, t_ray ray, double *min, double *tmp_min)
{
	t_sphere	*sp;
	t_plane		*pl;

	sp = NULL;
	pl = NULL;
	if (ROUNDOFF >= *tmp_min || *tmp_min >= *min - ROUNDOFF)
		return (FALSE);
	(*min) = (*tmp_min);
	curr_ob->point = vec_plus(ray.origin, vec_mult_(ray.normal, *min));
	if (curr_ob->type == SPHERE)
	{
		sp = curr_ob->figure;
		curr_ob->point_normal = vec_unit(vec_minus(curr_ob->point, sp->point));
	}
	else if (curr_ob->type == PLANE)
	{
		pl = curr_ob->figure;
		if (vec_dot(pl->normal, curr_ob->point) < ROUNDOFF)
			curr_ob->point_normal = pl->normal;
		else
			curr_ob->point_normal = vec_mult_(pl->normal, -1);
	}
	else
		curr_ob->point_normal = find_cylinder_normal(curr_ob);
	return (TRUE);
}

t_object	*hit_objects(t_info *info, t_ray ray)
{
	t_object	*rtn;
	t_object	*curr_ob;
	double		min;
	double		tmp_min;

	rtn = NULL;
	curr_ob = info->object;
	min = INFINITY;
	while (curr_ob)
	{
		if (curr_ob->type == SPHERE)
			tmp_min = hit_sphere(curr_ob->figure, ray);
		else if (curr_ob->type == PLANE)
			tmp_min = hit_plane(curr_ob->figure, ray);
		else
			tmp_min = hit_cylinder(curr_ob->figure, ray);
		if (find_normal(curr_ob, ray, &min, &tmp_min))
			rtn = curr_ob;
		curr_ob = curr_ob->next;
	}
	return (rtn);
}

int	hit_shadow_ray(t_info *info, t_ray ray, t_object *curr_ob)
{
	t_object	*rtn;
	t_object	*hit_ob;
	double		min;
	double		tmp_min;

	rtn = NULL;
	hit_ob = info->object;
	min = sqrt(vec_len2(vec_minus(info->canvas->light.light_point,
					ray.origin)));
	while (hit_ob)
	{
		if (hit_ob->type == SPHERE)
			tmp_min = hit_sphere(hit_ob->figure, ray);
		else if (hit_ob->type == PLANE)
			tmp_min = hit_plane(hit_ob->figure, ray);
		else
			tmp_min = hit_cylinder(hit_ob->figure, ray);
		if (ROUNDOFF <= tmp_min && tmp_min < min)
		{
			min = tmp_min;
			rtn = hit_ob;
		}
		hit_ob = hit_ob->next;
	}
	return (rtn != NULL && rtn != curr_ob);
}
