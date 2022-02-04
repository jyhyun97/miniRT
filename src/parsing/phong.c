#include "../../include/minirt.h"

t_color ambient_light(t_info *info)
{
    t_color color;
    
    color = vec_mult_(info->canvas->ambient_color, info->canvas->ambient);
    return (color);
}

t_color diffuse_light(t_info *info, t_object *curr_ob)
{
    t_color     color;
    t_vector    light_dir;
    double      kd;

    light_dir = vec_unit(vec_minus(info->canvas->light.light_point, curr_ob->point));
    kd = fmax(vec_dot(curr_ob->point_normal, light_dir), 0.0);
    color = vec_mult_(info->canvas->light.color, kd);
    return (color);
}

t_color specular_light(t_info *info, t_ray ray, t_object *curr_ob)
{
    t_vector    light_dir;
    t_vector    replect_dir;
    t_vector    a;
    t_vector    specular;
    double      spec;

    light_dir = vec_unit(vec_minus(info->canvas->light.light_point, curr_ob->point));// 빛의 방향
    a = vec_mult_(curr_ob->point_normal, vec_dot(light_dir, curr_ob->point_normal));// 빛의 방향과 법선벡터와 내적한 값
    replect_dir = vec_plus(vec_mult_(light_dir, -1), vec_mult_(a, 2));// 반사광 벡터
    spec = pow(fmax(vec_dot(replect_dir, vec_mult_(ray.normal, -1)), 0.0), SHININESS);// (ray와 반사광의 내적값)^광택계수
    specular = vec_mult_(vec_mult_(info->canvas->light.color, info->canvas->light.brightness), spec);//빛의 색깔 밝기 적용
    return (specular);
}

int is_shadow(t_info *info, t_object *curr_ob)
{
    t_ray shadow;

    shadow.origin = curr_ob->point;
    shadow.normal = vec_unit(vec_minus(info->canvas->light.light_point, curr_ob->point));
    if (hit_shadow_ray(info, shadow, curr_ob))
        return (TRUE);
    return (FALSE);
}

t_color phong_model(t_info *info, t_ray ray, t_object *curr_ob)
{
    t_color color;

    color = ambient_light(info);
    color = vec_plus(color, diffuse_light(info, curr_ob));
    color = vec_plus(color, specular_light(info, ray, curr_ob));
    color = vec_mult_(color, info->canvas->light.brightness);
    if (is_shadow(info, curr_ob) == TRUE)
        color = ambient_light(info);
    return (vec_max(color, 255));
}