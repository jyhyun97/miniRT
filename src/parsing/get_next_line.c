/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 12:03:43 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/01/17 10:52:38 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int	split_line(char **line, char **bkup, char *bkup_p)
{
	char	*new_bkup;

	*bkup_p = '\0';
	*line = ft_strdup(*bkup);
	if (!(*line))
		return (-1);
	if (*(bkup_p + 1) == '\0')
	{
		free(*bkup);
		*bkup = 0;
		return (1);
	}
	bkup_p++;
	new_bkup = ft_strdup(bkup_p);
	if (!(new_bkup))
		return (-1);
	free(*bkup);
	*bkup = 0;
	*bkup = new_bkup;
	return (1);
}

int	rd_end(int read_len, char **line, char **bkup)
{
	char	*bkup_p;

	if (read_len < 0)
		return (-1);
	if (*bkup != 0)
	{
		bkup_p = ft_strchr(*bkup, '\n');
		if (bkup_p != 0)
			return (split_line(line, bkup, bkup_p));
	}
	else if (*bkup != 0)
	{
		*line = ft_strdup(*bkup);
		if (!(*line))
			return (-1);
		free(*bkup);
		*bkup = 0;
		return (0);
	}
	*line = ft_strdup("");
	if (!(*line))
		return (-1);
	return (0);
}

void	get_next_line_2(char *tmp, char **bkup, char *buf, int fd)
{
	tmp = ft_strjoin(bkup[fd], buf);
	free(bkup[fd]);
	bkup[fd] = tmp;
}

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	static char	*bkup[OPEN_MAX];
	int			read_len;
	char		*bkup_p;
	char		*tmp;

	if (fd < 0 || line == 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (-1);
	read_len = read(fd, buf, BUFFER_SIZE);
	tmp = 0;
	while (read_len > 0)
	{
		buf[read_len] = '\0';
		if (bkup[fd] == 0)
			bkup[fd] = ft_strdup(buf);
		else
			get_next_line_2(tmp, bkup, buf, fd);
		bkup_p = ft_strchr(bkup[fd], '\n');
		if (bkup_p != 0)
			return (split_line(line, &bkup[fd], bkup_p));
		read_len = read(fd, buf, BUFFER_SIZE);
	}
	return (rd_end(read_len, line, &bkup[fd]));
}
