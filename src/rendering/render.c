#include "../../include/minirt.h"

void   set_image(t_img *img, t_info *info)
{
    int w;
    int h;

    h = -1;
    while (++h < WIN_HEIGHT)
    {
        w = -1;
        while (++w < WIN_WIDTH)
        {
            //레이 설정
            //오브젝트면 퐁라이트 해주고 색깔 반환
            //아니면 배경색/쉐도우 확인해서 색깔 반환
            //색깔 img에 pixel put
            // 색 정하기
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
}