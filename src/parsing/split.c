#include "../../include.minirt.h"

static int  cnt_word(char const *s, char c)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '\0')
			i--;
		i++;
	}
	return (cnt);
}

static int  cnt_letter(char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				j++;
			}
			return (j);
		}
		if (s[i] == '\0')
			i--;
		i++;
	}
	return (0);
}

char    **allo_free(char **rst)
{
	int i;

	i = 0;
	while (rst[i] != 0)
	{
		free(rst[i]);
		i++;
	}
	free(rst);
	return (0);
}

static char **fill_rst(char **rst, char const *s, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			ft_strlcpy(rst[j], s + i, cnt_letter(s + i, c) + 1);
			j++;
			i += cnt_letter(s + i, c);
		}
		if (s[i] == '\0')
			i--;
		i++;
	}
	rst[j] = 0;
	return (rst);
}

char        **ft_split(char const *s, char c)
{
    char    **rst;
    int     i;
    int     j;

    rst = (char **)malloc(sizeof(char *) * (cnt_word(s, c) + 1));
    if (rst == 0 || s == 0)
        return (0);
    i = 0;
    j = 0;
    while (s[i] != '\0')
    {
        if (s[i] != c && s[i] != '\0')
        {
            rst[j] = (char *)malloc(sizeof(char) * (cnt_letter(s + i, c) + 1));
            if (rst[j] == 0)
                return (allo_free(rst));
            j++;
            while (s[i] != c && s[i] != '\0')
                i++;
        }
        if (s[i] == '\0')
            i--;
        i++;
    }
    return (fill_rst(rst, s, c));
}