/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:31:56 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 13:32:44 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	my_mlx_pixel_put(t_img *img, t_color color, int x, int y)
{
	char	*dst;
	int		rgb_color;

	rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
	dst = img->data + (x * img->bpp / 8) + ((WIN_HEIGHT - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

int	press_x(t_info *info)
{
	free_info(&info);
	printf("exit success\n");
	exit(0);
	return (0);
}

int	exit_mlx(int keycode, t_info *info)
{
	if (keycode == ESC_KEY)
		press_x(info);
	return (0);
}
