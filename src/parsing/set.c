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

int set_ambient(t_canvas *canvas, char **split)
{
    char    **element;
    t_color color;

    if (ft_strslen(split) != 2 && !check_double(split[0]))
        return (ERROR);
    element = ft_split(split[1], ',');
    if (!check_vector(element))
    {
        allo_free(element);
        return (ERROR);
    }
    canvas->ambient = ft_atod(split[0]);
    color = create_color(ft_atod(element[0]), ft_atod(element[1]), ft_atod(element[2]));
    allo_free(element);
    if ((0.0 > canvas->ambient || canvas->ambient > 1.0) && !check_color(color))
        return (ERROR);
    canvas->ambient_color = color;
    return (SUCCESS);
}

int set_camera(t_canvas *canvas, char **split)
{
    char **view_vector;
    char **norm_vector;
    int i;
    int rtn;

    view_vector = ft_split(split[0], ',');
    norm_vector = ft_split(split[1], ',');
    i = 0;
    rtn = SUCCESS;
    while (view_vector[i] != 0 || norm_vector[i] != 0)
    {
        if (check_double(view_vector[i]) == FALSE || check_double(norm_vector[i]) == FALSE)
            rtn = ERROR;
        if (ft_atod(norm_vector[i]) < -1 || ft_atod(norm_vector[i]) > 1)//줄 수 부족하면 위 조건과 합쳐도 됨
            rtn = ERROR;
        i++;
    }
    if (i != 3 || ft_atoi(split[2]) < 0 || ft_atoi(split[2]) > 180 || ft_strslen(split) != 3)
        rtn = ERROR;
    else if (rtn != ERROR)
    {
        canvas->camera.view_vector = create_vector(ft_atod(view_vector[0]), ft_atod(view_vector[1]), ft_atod(view_vector[2]));
        canvas->camera.normal = create_vector(ft_atod(norm_vector[0]), ft_atod(norm_vector[1]), ft_atod(norm_vector[2]));
        canvas->camera.fov = ft_atoi(split[2]);
    }
    allo_free(view_vector);
    allo_free(norm_vector);
    return (rtn);
}

int set_light(t_canvas *canvas, char **split)
{
    char    **point;
    char    **color;
    
    if (ft_strslen(split) != 3 && !check_double(split[1]))
        return (ERROR);
    point = ft_split(split[0], ',');
    color = ft_split(split[2], ',');
    if (!point && !color && !check_vector(point) && !check_vector(color))
    {
        allo_free(point);
        allo_free(color);
        return (ERROR);
    }
    canvas->light.light_point = create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2]));
    canvas->light.brightness = ft_atod(split[1]);
    canvas->light.color = create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]));
    allo_free(point);
    allo_free(color);
    if ((0 > canvas->light.brightness || canvas->light.brightness > 1.0) && !check_color(canvas->light.color))
        return (ERROR);
    return (SUCCESS);
}

int set_plane(t_info *info, char **split)
{
    char **point;
    char **normal;
    char **color;
    t_plane *plane = malloc(sizeof(t_plane));
    t_object *object;

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
    *plane = create_plane(create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2])),
        create_vector(ft_atod(normal[0]), ft_atod(normal[1]), ft_atod(normal[2])),
        create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2])));
    allo_free(point);
    allo_free(normal);
    allo_free(color);
    object = malloc(sizeof(t_object));
    if (check_normal(plane->normal) == FALSE || check_color(plane->color) == FALSE || !object)
        return (ERROR);
    object->type = PLANE;
    object->figure = plane;
    object->next = NULL;
    push_object(info, object);
    return (SUCCESS);
}

int set_sphere(t_info *info, char **split)
{
    t_sphere    *sp = malloc(sizeof(t_sphere));
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
    *sp = create_sphere(create_vector(ft_atod(centor[0]), ft_atod(centor[1]), ft_atod(centor[2])),
                        radius,create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2]))); 
    allo_free(centor);
    allo_free(color);
    object = malloc(sizeof(t_object));
    if (!check_color(sp->color) && !object)
        return (ERROR);
    object->type = SPHERE;
    object->figure = sp;
    object->next = NULL;
    push_object(info, object);
    return (SUCCESS);
}

int set_cylinder(t_info *info, char **split)
{
    char        **point;
    char        **normal;
    char        **color;
    double      value[2];
    t_cylinder  *cylinder = malloc(sizeof(t_cylinder));
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
    *cylinder = create_cylinder(create_vector(ft_atod(point[0]), ft_atod(point[1]), ft_atod(point[2])),
        create_vector(ft_atod(normal[0]), ft_atod(normal[1]), ft_atod(normal[2])),
        value, create_color(ft_atod(color[0]), ft_atod(color[1]), ft_atod(color[2])));
    allo_free(point);
    allo_free(normal);
    allo_free(color);
    object = malloc(sizeof(t_object));
    if (check_normal(cylinder->normal) == FALSE || check_color(cylinder->color) == FALSE || !object)
        return (ERROR);
    object->type = CYLINDER;
    object->figure = cylinder;
    object->next = NULL;
    push_object(info, object);
    return (SUCCESS);
}
