/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:41:47 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 14:57:50 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	free_info(t_info **info)
{
	t_object	*curr;
	t_object	*prev;
	t_cylinder	*tmp;

	if ((*info)->canvas)
		free((*info)->canvas);
	if ((*info)->object)
	{
		curr = (*info)->object;
		while (curr != NULL)
		{
			if (curr->type == CYLINDER)
			{
				tmp = curr->figure;
				free(tmp->cap[TOP]);
				free(tmp->cap[BOTTOM]);
			}
			prev = curr;
			curr = prev->next;
			free(prev->figure);
			free(prev);
		}
	}
	free(*info);
}

int	init_canvas(t_info *info)
{
	info->canvas = malloc(sizeof(t_canvas));
	if (!(info->canvas))
		return (ERROR);
	info->canvas->ambient = 0.2;
	info->canvas->ambient_color = create_color(255, 255, 255);
	info->canvas->light.light_point = create_vector(0, 10, 0);
	info->canvas->light.color = create_color(255, 255, 255);
	info->canvas->light.brightness = 0.7;
	info->canvas->camera.origin = create_vector(0, 5, 0);
	info->canvas->camera.normal = create_vector(0, 0, 1);
	info->canvas->camera.fov = 70;
	return (SUCCESS);
}

t_info	*init_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	if (init_canvas(info))
		return (NULL);
	info->object = NULL;
	return (info);
}

int	save_info(t_info *info, char **split)
{
	int			error;
	static int	flag[3];

	error = SUCCESS;
	if (!ft_strcmp(split[0], "A") && ++flag[0])
		error = set_ambient(info->canvas, &(split[1]));
	else if (!ft_strcmp(split[0], "C") && ++flag[1])
		error = set_camera(info->canvas, &(split[1]));
	else if (!ft_strcmp(split[0], "L") && ++flag[2])
		error = set_light(info->canvas, &(split[1]));
	else if (!ft_strcmp(split[0], "pl"))
		error = set_plane(info, &(split[1]));
	else if (!ft_strcmp(split[0], "sp"))
		error = set_sphere(info, &(split[1]));
	else if (!ft_strcmp(split[0], "cy"))
		error = set_cylinder(info, &(split[1]));
	else
		error = ERROR;
	if (flag[0] >= 2 || flag[1] >= 2 || flag[2] >= 2)
		error = ERROR;
	return (error);
}

int	line_to_info(t_info *info, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	free(line);
	if (!split)
		return (FALSE);
	else if (split[0] != 0 && save_info(info, split))
	{
		allo_free(split);
		return (FALSE);
	}
	allo_free(split);
	return (TRUE);
}
