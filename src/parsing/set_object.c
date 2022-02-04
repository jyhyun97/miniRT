/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:20:14 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:26:59 by jeonhyun         ###   ########.fr       */
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
