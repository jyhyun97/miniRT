/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:42:48 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 10:53:51 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_cam	create_cam(t_camera camera)
{
	t_cam		cam;
	t_vector	u;
	t_vector	v;
	t_vector	w;
	t_vector	vup;

	cam.focal_length = 1;
	cam.aspect_ratio = (double)((double)WIN_WIDTH / (double)WIN_HEIGHT);
	cam.viewport_h = cam.focal_length * 2 * tan(deg_to_rad(camera.fov / 2));
	cam.viewport_w = cam.viewport_h * cam.aspect_ratio;
	cam.origin = camera.origin;
	cam.normal = vec_unit(camera.normal);
	vup = create_vector(0, 1, 0);
	if (cam.normal.x == 0 && cam.normal.y != 0 && cam.normal.z == 0)
		vup = create_vector(0, 0, 1);
	w = vec_mult_(cam.normal, -1);
	u = vec_unit(vec_cross(w, vup));
	v = vec_unit(vec_cross(u, w));
	cam.horizontal = vec_mult_(u, cam.viewport_w);
	cam.vertical = vec_mult_(v, cam.viewport_h);
	cam.left_bottom = vec_minus(cam.origin,
			vec_plus(vec_div_(cam.horizontal, 2),
				vec_plus(vec_div_(cam.vertical, 2), w)));
	return (cam);
}

t_vector	create_vector(double x, double y, double z)
{
	t_vector	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_color	create_color(double x, double y, double z)
{
	t_color	color;

	color.x = x;
	color.y = y;
	color.z = z;
	return (color);
}
