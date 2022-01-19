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
    ray.normal = vec_unit(vec_plus(cam.left_bottom, 
                    vec_plus(vec_mult_(cam.horizontal, u), 
                    (vec_mult_(cam.vertical, v)))));
    return (ray);
}

void   set_image(t_img *img, t_info *info)
{
    int w;
    int h;
    t_cam cam;
    t_ray ray;
    t_color color;
    
    cam = create_cam(info->canvas->camera);
    h = -1;
    while (++h < WIN_HEIGHT)
    {
        w = -1;
        while (++w < WIN_WIDTH)
        {
            //레이 설정
            ray = set_ray(cam, (double)w / (WIN_WIDTH - 1), (double)h / (WIN_HEIGHT - 1));
            color = create_vector(255, 255, 255);
            //오브젝트면 퐁라이트 해주고 색깔 반환
            //아니면 배경색/쉐도우 확인해서 색깔 반환
            //색깔 img에 pixel put
            // 색 정하기
            my_mlx_pixel_put(img, color, w, h);
        }
    }
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
    mlx_loop(mlx.mlx_ptr);
    return (0);
}