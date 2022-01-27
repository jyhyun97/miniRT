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
    if (t1 < t2 && t1 > 0)
        return (t1);
    else if (t1 > t2 && t2 > 0)
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
    t_vector    ro;
    double      h;
    double      tp;
    double      len;

    rt = vec_plus(ray.origin, vec_mult_(ray.normal, t));
    ro = vec_minus(rt, cy->point);
    h = vec_dot(ro, cy->normal);
    if (0 <= h && h <= cy->height)
        return (t);
    else
    {
        if (h < 0)
        {
            tp = vec_dot(cy->normal, vec_minus(cy->point, ray.origin)) / vec_dot(cy->normal, ray.normal);
            len = sqrt(vec_len2(vec_minus(cy->point, vec_plus(ray.origin, vec_mult_(ray.normal,tp)))));
        }
        else
        {
            tp = vec_dot(cy->normal, vec_minus(vec_plus(cy->point, vec_mult_(cy->normal, cy->height)), ray.origin)) / vec_dot(cy->normal, ray.normal);
            len = sqrt(vec_len2(vec_minus(vec_plus(cy->point, vec_mult_(cy->normal, cy->height)), vec_plus(ray.origin, vec_mult_(ray.normal,tp)))));
        }
        if (0 <= len && len <= cy->radius)
            return (tp);
        return (-1);
    }
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
    if (t1 < t2 && t1 > 0)
        return (hit_cylinder_cap(cy, ray, t1));
    else if (t1 > t2 && t2 > 0)
        return (hit_cylinder_cap(cy, ray, t2));
    else
        return (-1);
}

t_vector find_cylinder_normal(t_object *curr_ob)
{
    t_vector    normal;
    t_cylinder  *cy;
    t_vector    oa;
    double      len;
    double      l;
    
/*
	t_v3 ctp;
	t_v3 normal;

	ctp = substract(point, cylinder.p);
	normal = substract(ctp, v3_multiply(cylinder.normal, dot_product(cylinder.normal, ctp)));
	normalize_vector(&normal);
	return (normal);
*/
    
    cy = curr_ob->figure;
    oa = vec_minus(curr_ob->point, cy->point);// 원기둥 중심점에서 교점까지의 벡터
    len = sqrt(vec_len2(oa) - pow(vec_dot(oa, cy->normal), 2));// 교점과 원기둥 축의 최단거리
    if (len < cy->radius - 0.00001)
    {
        if (sqrt(vec_len2(oa)) > cy->radius)// (윗뚜껑)
            normal = cy->normal;
        else// (아랫뚜껑)
            normal = vec_mult_(cy->normal, -1);
    }
    else// (측면)
    {
        l = vec_dot(oa, cy->normal);// oa dot N = l (높이 구함)
        normal = vec_unit(vec_minus(oa, vec_mult_(cy->normal, l)));// BA = A - (o + l * N)
    }
    return (normal);
}

int set_hit_point(t_object *curr_ob, t_ray ray, double *min, double *tmp_min)
{
    t_sphere    *sp;
    t_plane     *pl;

    sp = NULL;
    pl = NULL;
    if (0 >= *tmp_min || *tmp_min >= *min)
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
        if (vec_dot(pl->normal, curr_ob->point) < 0)
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
            if (set_hit_point(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        else if (curr_ob->type == PLANE)
        {
            tmp_min = hit_plane(curr_ob->figure, ray);
            if (set_hit_point(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        else// CYLINDER
        {
            tmp_min = hit_cylinder(curr_ob->figure, ray);
            if (set_hit_point(curr_ob, ray, &min, &tmp_min))
                rtn = curr_ob;
        }
        curr_ob = curr_ob->next;
    }
    
    return (rtn);
}
