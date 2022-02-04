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
    if (discriminant < 0)
        return (-1);
    t1 = (-b - sqrt(discriminant)) / a;
    t2 = (-b + sqrt(discriminant)) / a;
    if (t1 < t2 && t1 > ROUNDOFF)
        return (t1);
    else if (t1 > t2 && t2 > ROUNDOFF)
        return (t2);
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

double  hit_cylinder_cap(t_cylinder *cy, t_ray ray, double t)
{
    t_vector    rt;
    double      h;
    double      tp;
    double      len;

    rt = vec_plus(ray.origin, vec_mult_(ray.normal, t));// 교점의 좌표
    h = vec_dot(vec_minus(rt, cy->point), cy->normal);
    tp = hit_plane(cy->top, ray);
    if (tp != -1 && vec_dot(cy->top->normal, ray.normal) <= 0)
    {
        len = vec_len2(vec_minus(cy->top->point, vec_plus(ray.origin, vec_mult_(ray.normal, tp))));
        if (len <= pow(cy->radius, 2))
            return (tp);
    }
    tp = hit_plane(cy->bottom, ray);
    if (tp != -1 && vec_dot(cy->bottom->normal, ray.normal) <= 0)
    {
        len = vec_len2(vec_minus(cy->bottom->point, vec_plus(ray.origin, vec_mult_(ray.normal, tp))));
        if (len <= pow(cy->radius, 2))
            return (tp);
    }
    if (0 < h && h < cy->height)
        return (t);
    return (-1);
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
    if (discriminant < 0)
        return (-1);
    t1 = (-b - sqrt(discriminant)) / a;
    t2 = (-b + sqrt(discriminant)) / a;
    
    if (t1 <= 0)
    {
        if (t2 <= 0)
            return (-1);
        return (hit_cylinder_cap(cy, ray, t2));
    }
    if (t2 < t1 && t2 > 0)
        return (hit_cylinder_cap(cy, ray, t2));
    return (hit_cylinder_cap(cy, ray, t1));
    
    
    //둘 다 음수 -> -1
    //한 쪽만 음수 -> 양수인 쪽 반환
    //둘 다 양수 -> 둘 비교해서 더 작은 값 반환
    // if ((t1 < t2 && t1 > 0) || (t1 > t2 && t2 < 0 && t1 > 0))
    //     return (hit_cylinder_cap(cy, ray, t1));
    // else if ((t1 > t2 && t2 > 0) || (t2 > t1 && t1 < 0 && t2 > 0))
    //     return (hit_cylinder_cap(cy, ray, t2));
    // else
    //     return (-1);
}

t_vector find_cylinder_normal(t_object *curr_ob)
{
    t_vector    normal;
    t_cylinder  *cy;
    t_vector    oa;
    double      len;
    double      l;
    
    cy = curr_ob->figure;
    oa = vec_minus(curr_ob->point, cy->point);// 원기둥 중심점에서 교점까지의 벡터
    len = sqrt(vec_len2(oa) - pow(vec_dot(oa, cy->normal), 2));// 교점과 원기둥 축의 최단거리


    if (len <= cy->radius - ROUNDOFF)//- 측면, + 윗뚜껑
    {
        if (sqrt(vec_len2(oa)) > cy->height - ROUNDOFF)// (윗뚜껑)
            normal = cy->normal;
        else
            normal = vec_mult_(cy->normal, -1);
        return (normal);
    }
    l = vec_dot(oa, cy->normal);// oa dot N = l (높이 구함)
    normal = vec_unit(vec_minus(oa, vec_mult_(cy->normal, l)));// BA = A - (o + l * N)
    return (normal);
}

int find_point_normal(t_object *curr_ob, t_ray ray, double *min, double *tmp_min)
{
    t_sphere    *sp;
    t_plane     *pl;

    sp = NULL;
    pl = NULL;
    if (ROUNDOFF >= *tmp_min || *tmp_min >= *min - ROUNDOFF)
        return (FALSE);
    (*min) = (*tmp_min);
    curr_ob->point = vec_plus(ray.origin, vec_mult_(ray.normal, *min));
    if (curr_ob->type == SPHERE)
    {
        sp = curr_ob->figure;
        curr_ob->point_normal = vec_unit(vec_minus(curr_ob->point, sp->point));
    }
    else if (curr_ob->type == PLANE)
    {
        pl = curr_ob->figure;
        if (vec_dot(pl->normal, curr_ob->point) < ROUNDOFF)
            curr_ob->point_normal = pl->normal;
        else
            curr_ob->point_normal = vec_mult_(pl->normal, -1);
    }
    else
        curr_ob->point_normal = find_cylinder_normal(curr_ob);
    return (TRUE);
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
            if (find_point_normal(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        else if (curr_ob->type == PLANE)
        {
            tmp_min = hit_plane(curr_ob->figure, ray);
            if (find_point_normal(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        else// CYLINDER
        {
            tmp_min = hit_cylinder(curr_ob->figure, ray);
            if (find_point_normal(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        curr_ob = curr_ob->next;
    }
    return (rtn);
}

int hit_shadow_ray(t_info *info, t_ray ray, t_object *curr_ob)
{
    t_object    *rtn;
    t_object    *hit_ob;
    double      min;
    double      tmp_min;

    rtn = NULL;
    hit_ob = info->object;
    min = sqrt(vec_len2(vec_minus(info->canvas->light.light_point, ray.origin)));
    while (hit_ob)
    {
        if (hit_ob->type == SPHERE)
        {
            tmp_min = hit_sphere(hit_ob->figure, ray);
            if (ROUNDOFF <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = hit_ob;
            }
        }
        else if (hit_ob->type == PLANE)
        {
            tmp_min = hit_plane(hit_ob->figure, ray);
            if (ROUNDOFF <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = hit_ob;
            }
        }
        else// CYLINDER
        {
            tmp_min = hit_cylinder(hit_ob->figure, ray);
            if (ROUNDOFF <= tmp_min && tmp_min < min)
            {
                min = tmp_min;
                rtn = hit_ob;
            }

        }
        hit_ob = hit_ob->next;
    }
    if (rtn != NULL && rtn != curr_ob)
        return (TRUE);
    return (FALSE);
}
