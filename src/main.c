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

    error = SUCCESS;
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
        error = ERROR;
    return (error);
}

void    print_vector(char *str, t_vector vec)
{
    printf("%s ", str);
    printf("(x, y, z) = (%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void    print_object(t_object *object)
{
    t_object    *cur = object;
    t_sphere    *tmp_sphere;
    t_plane     *tmp_plane;
    t_cylinder  *tmp_cylinder;

    while (cur != NULL)
    {
        if (cur->type == SPHERE)
        {
            tmp_sphere = object->figure;
            print_vector("sphere point ", tmp_sphere->point);
            printf("sphere radius %f\n", tmp_sphere->radius);
            print_vector("sphere color ", tmp_sphere->color);
        }
        else if (cur->type == PLANE)
        {
            tmp_plane = object->figure;
            print_vector("plane point ", tmp_plane->point);
            print_vector("plane normal ", tmp_plane->normal);
            print_vector("plane color ", tmp_plane->color);
        }
        else if (cur->type == CYLINDER)
        {
            tmp_cylinder = object->figure;
            print_vector("cylinder point ", tmp_cylinder->point);
            print_vector("cylinder normal ", tmp_cylinder->normal);
            print_vector("cylinder color ", tmp_cylinder->color);
            printf("cylinder radius %f", tmp_cylinder->radius);
            printf("cylinder height %f", tmp_cylinder->height);
        }
        cur = cur->next;
    }
}

void print_info(t_info *info)
{
    printf("canvas width %d\n", info->canvas->width);
    printf("canvas height %d\n", info->canvas->height);
    printf("ambient %f\n", info->canvas->ambient);
    print_vector("ambient color", info->canvas->ambient_color);
    print_vector("light point", info->canvas->light.light_point);    
    print_vector("light color", info->canvas->light.color);
    printf("brightness %f\n", info->canvas->light.brightness);
    print_vector("camera view_vector", info->canvas->camera.view_vector);
    print_vector("camera normal", info->canvas->camera.normal);
    printf("camera fov %d\n", info->canvas->camera.fov);
    print_object(info->object);
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
        if (split[0] != 0 && save_info(info, split))
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
    print_info(info);
    free_info(&info);
    return (SUCCESS);
}