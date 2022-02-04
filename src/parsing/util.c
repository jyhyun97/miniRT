#include "../../include/minirt.h"

double  degree_to_radian(int degree)
{
    return (degree * M_PI / 180);
}

int ft_strcmp(const char *s1, const char *s2)
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
	unsigned long i;

	i = 0;
	if (src == 0)
		return ((size_t)NULL);
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

int				ft_atoi(const char *str)
{
	int i;
	int rst;
	int pmsign;

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
    int j;

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

double          ft_atod(char *s)
{
    double  rst;
    int     i;
    int     pm_sign;

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

int ft_strslen(char **strs)
{
    int i;

    i = -1;
    while (strs[++i])
        ;
    return (i);
}
