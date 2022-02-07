/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:22:36 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 13:42:24 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color	render_color(t_object *curr_ob)
{
	t_color		rtn;
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	rtn = create_vector(255, 255, 255);
	sp = NULL;
	pl = NULL;
	cy = NULL;
	if (curr_ob->type == SPHERE)
	{
		sp = curr_ob->figure;
		rtn = sp->color;
	}
	else if (curr_ob->type == PLANE)
	{
		pl = curr_ob->figure;
		rtn = pl->color;
	}
	else if (curr_ob->type == CYLINDER)
	{
		cy = curr_ob->figure;
		rtn = cy->color;
	}
	return (rtn);
}

t_color	choose_color(t_info *info, t_ray ray, t_object *curr_ob)
{
	t_color	color;

	if (curr_ob)
	{
		color = vec_div_(render_color(curr_ob), 255);
		color = vec_max(vec_mult(color,
					vec_div_(phong_model(info, ray, curr_ob), 255)), 1);
		color = vec_mult_(color, 255);
	}
	else
		color = create_vector(0, 0, 0);
	return (color);
}

void	draw_image(t_img *img, t_info *info)
{
	int			w;
	int			h;
	t_cam		cam;
	t_ray		ray;
	t_object	*curr_ob;

	cam = create_cam(info->canvas->camera);
	h = -1;
	while (++h < WIN_HEIGHT)
	{
		w = -1;
		while (++w < WIN_WIDTH)
		{
			ray = set_ray(cam, (double)w / (WIN_WIDTH - 1),
					(double)h / (WIN_HEIGHT - 1));
			curr_ob = hit_objects(info, ray);
			my_mlx_pixel_put(img, choose_color(info, ray, curr_ob), w, h);
		}
	}
}

int	rendering(t_info *info)
{
	t_mlx	mlx;
	t_img	img;

	mlx.mlx_ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Mini RT");
	img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.data = mlx_get_data_addr(img.img_ptr, &img.bpp,
			&img.size_l, &img.endian);
	draw_image(&img, info);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, img.img_ptr, 0, 0);
	mlx_hook(mlx.win, KEY_PRESS, 0, &exit_mlx, info);
	mlx_hook(mlx.win, EXIT_BUTTON, 0, &press_x, info);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
