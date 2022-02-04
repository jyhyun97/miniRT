/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:02:27 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:05:41 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

double	degree_to_radian(int degree)
{
	return (degree * M_PI / 180);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned long	i;

	i = 0;
	if (src == 0)
		return ((size_t) NULL);
	if (size > 0)
	{
		while (src[i] && (i + 1 < size))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

int	is_digit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_strslen(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		;
	return (i);
}
