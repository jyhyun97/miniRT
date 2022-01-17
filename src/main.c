#include "../include/minirt.h"

void    free_info(t_info **info)
{
    t_object    *curr;
    t_object    *prev;
    
    if ((*info)->canvas)
        free((*info)->canvas);
    if ((*info)->object)
    {
        curr = (*info)->object;
        while (curr != NULL)
        {
            prev = curr;
            curr = prev->next;
            free(prev);
        }
    }
    free(*info);
}

void    put_err(char *str, t_info *info)
{
    printf("%s\n", str);
    free_info(&info);
    exit(ERROR);
}

t_info  *init_info(void)
{
    t_info *info;

    info = malloc(sizeof(t_info));
    info->canvas = NULL;
    info->object = NULL;
    return (info);
}

int save_info(t_info *info, char **split)
{
    int error;

    error = TRUE;
    // int i = 0;
    // (void)info;
    // while (split[i] != 0)
    // {
    //     printf("split[%d] %s\n", i, split[i]);
    //     i++;
    // }
    if (ft_strcmp(split[0], "A"))
        error = set_ambient(info->canvas, &(split[1]));
    else if (ft_strcmp(split[0], "C"))
        error = set_camera(info->canvas, &(split[1]));
    else if (ft_strcmp(split[0], "L"))
        error = set_light(info->canvas, &(split[1]));
    else if (ft_strcmp(split[0], "pl"))
        error = set_plane(info, &(split[1]));
    else if (ft_strcmp(split[0], "sp"))
        error = set_sphere(info, &(split[1]));
    else if (ft_strcmp(split[0], "cy"))
        error = set_cylinder(info, &(split[1]));
    else
        error = FALSE;
    return (error);
}

int parsing(char *file, t_info *info)
{
    int     fd;
    char    *line;
    char    **split;
    
    fd = open(file, O_RDONLY);
    if (fd == -1)
        put_err("File open error", info);
    info->canvas = malloc(sizeof(t_canvas));
    if (!info->canvas)
        return (FALSE);
    while (get_next_line(fd, &line) > 0)
    {
        split = ft_split(line, ' ');
        if (split[0] != 0 && !save_info(info, split))
        {
            allo_free(split);
            return (FALSE);
        }
        allo_free(split);
    }
    close(fd);
    return (TRUE);
}

int main(int argc, char **argv)
{
    t_info  *info;

    info = 0;
    if (argc != 2 || ft_strcmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt") != 0)
        put_err("Input Error\n", info);
    info = init_info();
    if (!parsing(argv[1], info))
        put_err("Parsing Error", info);
    //rendering
    free_info(&info);

    
    return (SUCCESS);
}