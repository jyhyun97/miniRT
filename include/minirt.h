#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "get_next_line.h"
# include "struct.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

//-----------------util.c---------------------
int         ft_strcmp(const char *s1, const char *s2);

//-----------------split.c---------------------
char        **allo_free(char **rst);
char        **ft_split(char const *s, char c);

#endif