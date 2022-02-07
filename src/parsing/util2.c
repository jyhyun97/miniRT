/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:04:53 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 14:04:54 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	rst;
	int	pmsign;

	i = 0;
	rst = 0;
	pmsign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pmsign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rst = (rst * 10) + (str[i] - '0');
		i++;
	}
	return (rst * pmsign);
}

static double	ft_atod_abs(char *s, double rst, int i)
{
	int	j;

	while (s[i] != '\0' && s[i] != '.')
	{
		rst = rst * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] == '.')
	{
		i++;
		j = 1;
		while (s[i] != '\0')
		{
			rst = rst + ((double)(s[i] - '0') / pow(10, j));
			i++;
			j++;
		}
	}
	return (rst);
}

double	ft_atod(char *s)
{
	double	rst;
	int		i;
	int		pm_sign;

	rst = 0;
	i = 0;
	pm_sign = 1;
	if (s[i] == '-')
	{
		pm_sign = -1;
		i++;
	}
	rst = ft_atod_abs(s, rst, i);
	return (rst * pm_sign);
}
