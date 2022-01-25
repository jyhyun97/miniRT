/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungmki <seungmki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:06:10 by seungmki          #+#    #+#             */
/*   Updated: 2021/03/09 20:26:40 by seungmki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		is_shadow_in_cap(t_scene s, t_ray *shad_r, int i)
{//원통 몸통에 교차점 없거나 원통과 광원 사이 방향 벡터 없으면 이 함수로 들어옴
	t_sub_plane	sub_pl;
	t_cylinder	*tmp;

	tmp = s.cylinder[i];
	if (tmp->m != 0 && tmp->m > tmp->height)
		sub_pl.point = vec3_add_vec3(tmp->point,//아래 뚜껑 좌표(tmp->point)에, 원통 높이와 아래 뚜껑 법선 곱한 거 더해 위 뚜껑 좌표 확보
			scalar_multiply_vec3(tmp->height, tmp->n));
	else
		sub_pl.point = tmp->point;//위 뚜껑 아니면 아래 뚜껑 좌표
	sub_pl.n = tmp->n;//위, 아래 뚜껑 법선은 같다
	if ((is_ray_intersect_cap(&s, shad_r, i, &sub_pl)) != 0)
		if ((between_light_n_obj(s.light[s.i_light]->pos, sub_pl.p,
		shad_r->origin)) != 0)
			return (1);
	return (0);
}

int		is_shadow_in_cylinder(t_scene s, t_ray *shad_r, int i)
{
	t_cylinder *tmp;

	tmp = s.cylinder[i];
	tmp->m = 0;//원통 법선(tmp->n)과, 교차점에서 아랫점 빼서 확보한 벡터(tmp->p - tmp->point)를 내적해 각도 확보한 걸 다시 0 대입
	if (is_ray_intersect_cylinder(&s, shad_r, i) != 0)
	{
		tmp->p = vec3_add_vec3(shad_r->origin,//shad_r->origin은 캔버스에 그림 그릴 위치, shad_r->global은 패레럴, 정규화된 광원 방향 벡터
			scalar_multiply_vec3(shad_r->t, shad_r->global));//교차점 p 확보
		if ((between_light_n_obj(s.light[s.i_light]->pos, tmp->p,
		shad_r->origin)) != 0)//음영 처리할 지점이 있는지 없는지 검사. 광원과 물체 사이에 방향 벡터 있는지 검사
		{
			tmp->m = vec3_dot_product(tmp->n,//원통의 교차점에서 캔버스에 그림 그릴 위치 뺴서 벡터 op 확보하고, 원통 법선과 내적
				vec3_subtraction(tmp->p, tmp->point));//draw_cylinder_on_canvas()의 m은 교차점(tmp->p) - 아랫점(tmp->point)로 확보한 벡터와 tmp->n를 내적함
			if (tmp->m > 0 && tmp->m < tmp->height)//이런 뚜껑이 아닌 몸통에서 교차점 나온 것
				return (1);
		}
	}
	if ((is_shadow_in_cap(s, shad_r, i)) != 0)
		return (1);
	return (0);
}

t_vec3	get_nearest_cap(t_scene s, int i)
{
	t_vec3		vec3[2];
	t_vec3		top_cap;
	double		distance[2];
	t_cylinder	*tmp;

	tmp = s.cylinder[i];
	top_cap = vec3_add_vec3(tmp->point,//위 뚜껑 위치 확보
		scalar_multiply_vec3(tmp->height, tmp->n));
	vec3[0] = vec3_subtraction(s.camera[s.i_cam]->pos, tmp->point);//카메라에서 아랫점 빼서 벡터 확보
	vec3[1] = vec3_subtraction(s.camera[s.i_cam]->pos, top_cap);//카메라에서 위 뚜껑 빼서 벡터 확보
	distance[0] = vec3_self_dot_sqrt(vec3[0]);//두 벡터의 길이 구해 비교
	distance[1] = vec3_self_dot_sqrt(vec3[1]);
	if (distance[0] > distance[1])
		return (top_cap);//위 뚜겅 거리가 짧으면 위 뚜껑이 더 가까운 거고 아니면 아래 뚜껑
	return (tmp->point);
}

int		is_ray_intersect_cap(t_scene *s, t_ray *r, int i, t_sub_plane *pl)
{
	double length;

	if ((is_ray_intersect_plane(s, r, pl)) == 0)
		return (0);//뚜껑도 평면임. 그러니 광선-평면 교차 함수 씀
	if (get_intersection_of_plane(s, r, pl) == 0)
		return (0);//pl.p에 교차점 얻어 옴
	length = vec3_self_dot_sqrt(vec3_subtraction(pl->p, pl->point));//교차점에서 뚜껑 위치 빼고 길이 확보
	if (length >= s->cylinder[i]->radius)
		return (0);//그 길이가 반지름 넘어가면 광선-뚜껑 교차 안 함 
	if (pl->den > 0)//분모가 0 이상이면 뚜껑 점 법선 방향 조정
		pl->n = scalar_multiply_vec3(-1, pl->n);
	return (1);
}

void	draw_cylinder_cap(t_scene s, t_ray *r, int i)
{
	double		t;
	t_obj_clr	obj;
	t_cylinder	*tmp;
	t_sub_plane	sub_pl;

	t = r->t;
	tmp = s.cylinder[i];
	if (tmp->m != 0 && tmp->m > tmp->height)
		sub_pl.point = vec3_add_vec3(tmp->point,
		scalar_multiply_vec3(tmp->height, tmp->n));//바닥 법선을 높이만큼 곱해 아랫점에 더하면 위 뚜껑 좌표 나옴
	else
		sub_pl.point = get_nearest_cap(s, i);//아니면 더 가까운 뚜겅이 뭔지 따져서 그 좌표 확보
	sub_pl.n = tmp->n;//아랫점 법선 전달
	if (is_ray_intersect_cap(&s, r, i, &sub_pl) != 0)
	{//sub_pl.p에 교차점 얻어 옴
		obj.p = sub_pl.p;
		obj.normal = sub_pl.n;//뚜껑의 법선 전달
		obj.rgb = tmp->rgb;
		r->color = obj_color_to_canvas(s, obj);
	}
	r->t = t;
}
