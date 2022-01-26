#include "../../include/minirt.h"

void	my_mlx_pixel_put(t_img *img, t_color color, int x, int y)
{
	char	*dst;
    int     rgb_color;

    rgb_color = ((int)color.x << 16) | ((int)color.y << 8) | (int)color.z;
	dst = img->data + (x * img->bpp / 8) + ((WIN_HEIGHT - y - 1) * img->size_l);
	*(unsigned int *)dst = rgb_color;
}

t_ray   set_ray(t_cam cam, double u, double v)
{
    t_ray   ray;

    ray.origin = cam.origin;
    ray.normal = vec_unit(vec_minus(vec_plus(cam.left_bottom, 
         vec_plus(vec_mult_(cam.horizontal, u), 
         (vec_mult_(cam.vertical, v)))), ray.origin));
    return (ray);
}

t_color ambient_light(t_info *info)
{
    t_color color;
    color = vec_mult_(info->canvas->ambient_color, info->canvas->ambient);
    return (color);
}

t_color diffuse_light(t_info *info, t_ray ray, t_object *curr_ob)
{
    t_color     color;
    t_vector    light_dir;
    t_vector    point;
    t_vector    point_normal;
    double      kd;


    return (color);
}

t_color phong_model(t_info *info, t_ray ray, t_object *curr_ob)
{
    t_color color;
    
    (void)ray;
    (void)curr_ob;
    color = create_color(0, 0, 0);
    color = vec_plus(color, ambient_light(info));
    color = vec_plus(color, diffuse_light(info, ray, curr_ob));
    // color = vec_plus(color, specular_light());
    return (color);
}

/*
    t_vec   diffuse;
    t_vec   light_dir;
    double  kd;

    light_dir = unit_vec(sub_vec(light.origin, rec.p));//광원 ~ 교점 방향벡터
    kd = fmax(dot_vec(rec.normal, light_dir), 0.0);//교점에서 접하는 평면에 법선벡터
    diffuse = mul_vec_(light.light_color, kd);
    return (diffuse);
*/

t_color render_color(t_object *curr_ob)
{
    t_color     rtn;
    t_sphere    *sp;
    t_plane     *pl;
    t_cylinder  *cy;
    
    rtn = create_vector(255, 255, 255);
    sp = NULL;
    pl = NULL;
    cy = NULL;
    if (curr_ob->type == SPHERE)
    {
        sp = curr_ob->figure;
        rtn = sp->color;
    }
    else if (curr_ob->type == PLANE)
    {
        pl = curr_ob->figure;
        rtn = pl->color;
    }
    else if (curr_ob->type == CYLINDER)
    {
        cy = curr_ob->figure;
        rtn = cy->color;
    }
    return (rtn);
}


void   set_image(t_img *img, t_info *info)
{
    int         w;
    int         h;
    t_cam       cam;
    t_ray       ray;
    t_color     color;
    t_object    *curr_ob;
    
    cam = create_cam(info->canvas->camera);
    h = -1;
    while (++h < WIN_HEIGHT)
    {
        w = -1;
        while (++w < WIN_WIDTH)
        {
            //레이 설정
            ray = set_ray(cam, (double)w / (WIN_WIDTH - 1), (double)h / (WIN_HEIGHT - 1));
            curr_ob = hit_objects(info, ray);
            if (curr_ob)
            {
                // color = render_color(curr_ob);
                color = phong_model(info, ray, curr_ob);
            }
            else
                color = create_vector(0, 0, 0);
            //오브젝트면 퐁라이트 해주고 색깔 반환
            //아니면 배경색/쉐도우 확인해서 색깔 반환
            //색깔 img에 pixel put
            // 색 정하기
            my_mlx_pixel_put(img, color, w, h);
        }
    }
}

int	press_X(t_info *info)
{
	free_info(&info);
    printf("exit success\n");
    exit(0);
    return (0);
}

int exit_mlx(int keycode, t_info *info)
{
    if (keycode == ESC_KEY)
        press_X(info);
    return (0);
}

int rendering(t_info *info)
{
    t_mlx   mlx;
    t_img   img;

    mlx.mlx_ptr = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Mini RT");
    img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    img.data = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
    set_image(&img, info);
    mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, img.img_ptr, 0, 0);
    mlx_hook(mlx.win, KEY_PRESS, 0, &exit_mlx, info);
    mlx_hook(mlx.win, EXIT_BUTTON, 0, &press_X, info);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}