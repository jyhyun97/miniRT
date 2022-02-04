#include "../../include/minirt.h"

void    free_info(t_info **info)
{
    t_object    *curr;
    t_object    *prev;
    t_cylinder  *tmp;
    
    if ((*info)->canvas)
        free((*info)->canvas);
    if ((*info)->object)
    {
        curr = (*info)->object;
        while (curr != NULL)
        {
            if (curr->type == CYLINDER)
            {
                tmp = curr->figure;
                free(tmp->cap[TOP]);
                free(tmp->cap[BOTTOM]);
            }
            prev = curr;
            curr = prev->next;
            free(prev->figure);
            free(prev);
        }
    }
    free(*info);
}

t_info  *init_info(void)
{
    t_info *info;

    info = malloc(sizeof(t_info));
    if (!info)
        return (NULL);
    info->canvas = NULL;
    info->object = NULL;
    return (info);
}

int save_info(t_info *info, char **split)
{
    int error;

    error = SUCCESS;
    if (!ft_strcmp(split[0], "A"))
        error = set_ambient(info->canvas, &(split[1]));
    else if (!ft_strcmp(split[0], "C"))
        error = set_camera(info->canvas, &(split[1]));
    else if (!ft_strcmp(split[0], "L"))
        error = set_light(info->canvas, &(split[1]));
    else if (!ft_strcmp(split[0], "pl"))
        error = set_plane(info, &(split[1]));
    else if (!ft_strcmp(split[0], "sp"))
        error = set_sphere(info, &(split[1]));
    else if (!ft_strcmp(split[0], "cy"))
        error = set_cylinder(info, &(split[1]));
    else
        error = ERROR;
    return (error);
}

int line_to_info(t_info *info, char *line)
{
    char **split;

    split = ft_split(line, ' ');
    free(line);
    if (!split)
        return (FALSE);
    else if (split[0] != 0 && save_info(info, split))
    {
        allo_free(split);
        return (FALSE);
    }
    allo_free(split);
    return (TRUE);
}
