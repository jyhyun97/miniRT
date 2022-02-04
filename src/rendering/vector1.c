/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:21:29 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 13:22:21 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vector	vec_plus(t_vector vec1, t_vector vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}

t_vector	vec_minus(t_vector vec1, t_vector vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return (vec1);
}

t_vector	vec_mult(t_vector vec1, t_vector vec2)
{
	vec1.x *= vec2.x;
	vec1.y *= vec2.y;
	vec1.z *= vec2.z;
	return (vec1);
}

t_vector	vec_mult_(t_vector vec1, double t)
{
	vec1.x *= t;
	vec1.y *= t;
	vec1.z *= t;
	return (vec1);
}

t_vector	vec_div_(t_vector vec1, double t)
{
	vec1.x /= t;
	vec1.y /= t;
	vec1.z /= t;
	return (vec1);
}
