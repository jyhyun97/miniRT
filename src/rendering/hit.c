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
    double      tmp_t = 0;
    
    os = vec_minus(ray.origin, sp->point);
    a = vec_dot(ray.normal, ray.normal);
    b = vec_dot(ray.normal, os);
    c = vec_dot(os, os) - pow(sp->radius, 2);
    discriminant = pow(b, 2) - (a * c);
    if (discriminant < 0)
        return (-1);
    return (1);
    // printf("a : %f, b : %f, c : %f\n", a, b, c);
    t1 = -b - sqrt(discriminant) / a;
    t2 = -b + sqrt(discriminant) / a;
    if (t1 < t2)
        tmp_t = t2;
    else if (t1 > t2)
        tmp_t = t1;
    // if (tmp_t > 0)
    //     return (tmp_t);
    if (tmp_t >= 0)
        return (tmp_t);
    else
        return (-1);
}

/*
double	vlength2(t_vector vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
double hit_sphere(t_sphere *sp, t_ray ray)
{
	t_vector oc;

	oc = vec_minus(ray.origin, sp->point);
	double a = vlength2(ray.normal);
	double b = vec_dot(oc, ray.normal);
	double c = vlength2(oc) - sp->radius;
	double d = b * b - a * c;

	if (d < 0)
		return (-1);
	else
		return (-b - sqrt(d) / a);
}
*/

// double  hit_plane(t_plane *pl, t_ray ray)
// {
    
// }

// double  hit_cylinder(t_cylinder *cl, t_ray ray)
// {
    
// }

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
            // printf("%f\n", tmp_min);
            if (0 <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = curr_ob;
            }
        }
        // else if (curr_ob->type = PLANE)
        // {
        //     tmp_min = hit_plane(curr_ob->figure, ray);
        //     if (tmp_min < min)
        //     {
        //         min = tmp_min;
        //         rtn = curr_ob;
        //     }
        // }
        // else // CYLINDER
        // {
        //     tmp_min = hit_cylinder(curr_ob->figure, ray);
        //     if (tmp_min < min)
        //     {
        //         min = tmp_min;
        //         rtn = curr_ob;
        //     }
        // }
        curr_ob = curr_ob->next;
    }
    return (rtn);
}
