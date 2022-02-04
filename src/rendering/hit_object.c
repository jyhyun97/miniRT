/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:54:24 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 13:55:05 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	hit_sphere(t_sphere *sp, t_ray ray)
{
	t_vector	os;
	double		var[4];
	double		t1;
	double		t2;

	os = vec_minus(ray.origin, sp->point);
	var[A] = vec_dot(ray.normal, ray.normal);
	var[B] = vec_dot(ray.normal, os);
	var[C] = vec_len2(os) - (sp->radius * sp->radius);
	var[DISCRIMINANT] = (var[B] * var[B]) - (var[A] * var[C]);
	if (var[DISCRIMINANT] < 0)
		return (-1);
	t1 = (-var[B] - sqrt(var[DISCRIMINANT])) / var[A];
	t2 = (-var[B] + sqrt(var[DISCRIMINANT])) / var[A];
	if (t1 < t2 && t1 > ROUNDOFF)
		return (t1);
	else if (t1 > t2 && t2 > ROUNDOFF)
		return (t2);
	else
		return (-1);
}

double	hit_plane(t_plane *pl, t_ray ray)
{
	t_vector	a;
	double		b;
	double		t;

	a = vec_minus(pl->point, ray.origin);
	b = vec_dot(pl->normal, ray.normal);
	t = vec_dot(pl->normal, a) / b;
	if (t < 0)
		return (-1);
	return (t);
}

double	hit_cylinder_cap(t_cylinder *cy, t_ray ray, double t)
{
	t_vector	rt;
	double		h;
	double		tp;
	double		len;
	int			i;

	i = -1;
	while (++i < 2)
	{
		tp = hit_plane(cy->cap[i], ray);
		if (tp != -1 && vec_dot(cy->cap[i]->normal, ray.normal) <= 0)
		{
			len = vec_len2(vec_minus(cy->cap[i]->point,
						vec_plus(ray.origin, vec_mult_(ray.normal, tp))));
			if (len <= pow(cy->radius, 2))
				return (tp);
		}
	}
	rt = vec_plus(ray.origin, vec_mult_(ray.normal, t));
	h = vec_dot(vec_minus(rt, cy->point), cy->normal);
	if (0 < h && h < cy->height)
		return (t);
	return (-1);
}

double	hit_cylinder(t_cylinder *cy, t_ray ray)
{
	t_vector	pc;
	double		var[4];
	double		t1;
	double		t2;

	pc = vec_minus(ray.origin, cy->point);
	var[A] = vec_len2(vec_cross(ray.normal, cy->normal));
	var[B] = vec_dot(vec_cross(ray.normal, cy->normal),
			vec_cross(pc, cy->normal));
	var[C] = vec_len2(vec_cross(pc, cy->normal)) - pow(cy->radius, 2);
	var[DISCRIMINANT] = (var[B] * var[B]) - (var[A] * var[C]);
	if (var[DISCRIMINANT] < 0)
		return (-1);
	t1 = (-var[B] - sqrt(var[DISCRIMINANT])) / var[A];
	t2 = (-var[B] + sqrt(var[DISCRIMINANT])) / var[A];
	if (t1 <= 0)
	{
		if (t2 <= 0)
			return (-1);
		return (hit_cylinder_cap(cy, ray, t2));
	}
	if (t2 < t1 && t2 > 0)
		return (hit_cylinder_cap(cy, ray, t2));
	return (hit_cylinder_cap(cy, ray, t1));
}
