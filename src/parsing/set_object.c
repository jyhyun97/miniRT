/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:20:14 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/07 10:37:35 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	push_object(t_info *info, t_object *object)
{
	t_object	*curr;

	if (!(info->object))
	{
		info->object = object;
		return ;
	}
	curr = info->object;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = object;
}

int	free_element(char **point, char **normal, char **color)
{
	if (point)
		allo_free(point);
	if (normal)
		allo_free(normal);
	if (color)
		allo_free(color);
	return (ERROR);
}
