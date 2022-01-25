#include "../../include/minirt.h"

double hit_sphere(t_sphere *sp, t_ray ray)
{
    t_vector    os;
    double      a;
    double      b;
    double      c;
    double      discriminant;
    double      t1;
    double      t2;
    
    os = vec_minus(ray.origin, sp->point);
    a = vec_dot(ray.normal, ray.normal);
    b = vec_dot(ray.normal, os);
    c = vec_dot(os, os) - (sp->radius *  sp->radius);
    discriminant = (b * b) - (a * c);
    // printf("discriminant: %f\n", discriminant);
    if (discriminant < 0)
        return (-1);
    t1 = (-b - sqrt(discriminant)) / a;
    t2 = (-b + sqrt(discriminant)) / a;
    // printf("t1: %f\tt2: %f\n", t1, t2);
    if (t1 < t2 && t2 > 0)
        return (t2);
    else if (t1 > t2 && t1 > 0)
        return (t1);
    else
        return (-1);
}

double  hit_plane(t_plane *pl, t_ray ray)
{
    t_vector    a = vec_minus(pl->point, ray.origin);
    double      b = vec_dot(pl->normal, ray.normal);
    double      t = vec_dot(pl->normal, a) / b;
    
    if (t < 0)
        return (-1);
    return (t);
}

double  hit_cylinder(t_cylinder *cy, t_ray ray)
{
    t_vector    pc;
    double      a;
    double      b;
    double      c;
    double      discriminant;
    double      t1;
    double      t2;
    
    pc = vec_minus(ray.origin, cy->point);
    a = vec_len2(vec_cross(ray.normal, cy->normal));
    b = vec_dot(vec_cross(ray.normal, cy->normal), vec_cross(pc, cy->normal));
    c = vec_len2(vec_cross(pc, cy->normal)) - pow(cy->radius, 2);
    
    discriminant = (b * b) - (a * c);
    printf("discriminant: %f\n", discriminant);
    if (discriminant < 0)
        return (-1);
    return (1);
    t1 = (-b - sqrt(discriminant)) / a;
    t2 = (-b + sqrt(discriminant)) / a;
    // printf("t1: %f\tt2: %f\n", t1, t2);
    if (t1 < t2 && t2 > 0)
        return (t2);
    else if (t1 > t2 && t1 > 0)
        return (t1);
    else
        return (-1);
   

}

t_object *hit_objects(t_info *info, t_ray ray)
{
    t_object    *rtn;
    t_object    *curr_ob;
    double      min;
    double      tmp_min;

    rtn = NULL;
    curr_ob = info->object;
    min = 99999;
    while (curr_ob)
    {
        if (curr_ob->type == SPHERE)
        {
            tmp_min = hit_sphere(curr_ob->figure, ray);//교점 double 리턴
            if (0 <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = curr_ob;
            }
        }
        else if (curr_ob->type == PLANE)
        {
            tmp_min = hit_plane(curr_ob->figure, ray);
            if (0 <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = curr_ob;
            }
        }
        else// CYLINDER
        {
            tmp_min = hit_cylinder(curr_ob->figure, ray);
            if (0 <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = curr_ob;
            }
        }
        curr_ob = curr_ob->next;
    }
    return (rtn);
}
