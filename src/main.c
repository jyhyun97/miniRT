/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeonhyun <jeonhyun@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 13:15:31 by jeonhyun          #+#    #+#             */
/*   Updated: 2022/02/04 13:19:04 by jeonhyun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	put_err(char *str, t_info *info)
{
	printf("%s\n", str);
	if (info)
		free_info(&info);
	exit(ERROR);
}

int	parsing(char *file, t_info *info)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		put_err("File open error", info);
	info->canvas = malloc(sizeof(t_canvas));
	if (!info->canvas)
		return (FALSE);
	while (get_next_line(fd, &line) > 0)
		if (line_to_info(info, line) == FALSE)
			return (FALSE);
	if (line_to_info(info, line) == FALSE)
		return (FALSE);
	close(fd);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_info	*info;

	info = NULL;
	if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt") != 0)
		put_err("Input Error", info);
	info = init_info();
	if (!info)
		put_err("Init Error", info);
	else if (!parsing(argv[1], info))
		put_err("Parsing Error", info);
	else if (!rendering(info))
		put_err("rendering Error", info);
	free_info(&info);
	return (SUCCESS);
}
