#include "../include/minirt.h"


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
            tmp_sphere = cur->figure;
            print_vector("\nsphere point ", tmp_sphere->point);
            printf("sphere radius %f\n", tmp_sphere->radius);
            print_vector("sphere color ", tmp_sphere->color);
        }
        else if (cur->type == PLANE)
        {
            tmp_plane = cur->figure;
            print_vector("\nplane point ", tmp_plane->point);
            print_vector("plane normal ", tmp_plane->normal);
            print_vector("plane color ", tmp_plane->color);
        }
        else if (cur->type == CYLINDER)
        {
            tmp_cylinder = cur->figure;
            print_vector("\ncylinder point ", tmp_cylinder->point);
            print_vector("cylinder normal ", tmp_cylinder->normal);
            print_vector("cylinder color ", tmp_cylinder->color);
            printf("cylinder radius %f\n", tmp_cylinder->radius);
            printf("cylinder height %f\n", tmp_cylinder->height);
        }
        cur = cur->next;
    }
}

void print_info(t_info *info)
{
    printf("ambient %f\n", info->canvas->ambient);
    print_vector("ambient color", info->canvas->ambient_color);
    print_vector("light point", info->canvas->light.light_point);    
    print_vector("light color", info->canvas->light.color);
    printf("brightness %f\n", info->canvas->light.brightness);
    print_vector("camera origin", info->canvas->camera.origin);
    print_vector("camera normal", info->canvas->camera.normal);
    printf("camera fov %d\n", info->canvas->camera.fov);
    print_object(info->object);
}
