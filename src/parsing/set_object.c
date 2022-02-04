#include "../../include/minirt.h"

void    push_object(t_info *info, t_object *object)
{
    t_object    *curr;
    
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

int set_plane(t_info *info, char **split)
{
    char **point;
    char **normal;
    char **color;
    t_plane *plane;
    t_object *object;

    plane = NULL;
    object = NULL;
    if (ft_strslen(split) != 3)
        return (ERROR);
    point = ft_split(split[0], ',');
    normal = ft_split(split[1], ',');
    color = ft_split(split[2], ',');
    if (!point || !normal || !color || check_vector(point) == FALSE ||
         check_vector(normal) == FALSE || check_vector(color) == FALSE)
    {
        allo_free(point);
        allo_free(normal);
        allo_free(color);
        return (ERROR);
    }
    plane = create_plane(create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2])),
        create_vector(ft_atod(normal[0]), ft_atod(normal[1]), ft_atod(normal[2])),
        create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2])));
    allo_free(point);
    allo_free(normal);
    allo_free(color);
    if (!plane)
        return (ERROR);
    else if (check_normal(plane->normal) == FALSE || check_color(plane->color) == FALSE)
    {
        free(plane);
        return (ERROR);
    }
    object = create_object(PLANE, plane);
    if (!object)
    {
        free(plane);
        return (ERROR);
    }
    push_object(info, object);
    return (SUCCESS);
}

int set_sphere(t_info *info, char **split)
{
    t_sphere    *sp;
    char        **centor;
    double      radius;
    char        **color;
    t_object    *object;
    
    object = NULL;
    if (ft_strslen(split) != 3 && !check_double(split[1]))
        return (ERROR);
    centor = ft_split(split[0], ',');
    color = ft_split(split[2], ',');
    radius = ft_atod(split[1]);
    if (!centor || !color || 0 >= radius || !check_vector(centor) || !check_vector(color))
    {
        allo_free(centor);
        allo_free(color);
        return (ERROR);
    }
    sp = create_sphere(create_vector(ft_atod(centor[0]), ft_atod(centor[1]), ft_atod(centor[2])),
                        radius,create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]))); 
    allo_free(centor);
    allo_free(color);
    if (!sp)
        return (ERROR);
    object = create_object(SPHERE, sp);
    if (!object)
    {
        free(sp);
        return (ERROR);
    }
    push_object(info, object);
    return (SUCCESS);
}

int set_cylinder(t_info *info, char **split)
{
    char        **point;
    char        **normal;
    char        **color;
    double      value[2];
    t_cylinder  *cylinder;
    t_object    *object;
    
    object = NULL;
    if (ft_strslen(split) != 5 || check_double(split[2]) == FALSE ||
        check_double(split[3]) == FALSE)
        return (ERROR);
    point = ft_split(split[0], ',');
    normal = ft_split(split[1], ',');
    value[0] = ft_atod(split[2]);
    value[1] = ft_atod(split[3]);
    color = ft_split(split[4], ',');
    if (!point || !normal || !color || (0 >= value[0]) || (0 >= value[1]) || 
        !check_vector(point) || !check_vector(normal) || !check_vector(color))
    {
        allo_free(point);
        allo_free(normal);
        allo_free(color);
        return (ERROR);
    }
    cylinder = create_cylinder(create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2])),
        create_vector(ft_atod(normal[0]), ft_atod(normal[1]), ft_atod(normal[2])),
        value, create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2])));
    allo_free(point);
    allo_free(normal);
    allo_free(color);
    if (!cylinder)
        return (ERROR);
    if (check_normal(cylinder->normal) == FALSE || check_color(cylinder->color) == FALSE)
    {
        free(cylinder);
        return (ERROR);
    }
    object = create_object(CYLINDER, cylinder);
    if (!object)
    {
        free(cylinder);
        return (ERROR);
    }
    push_object(info, object);
    return (SUCCESS);
}
