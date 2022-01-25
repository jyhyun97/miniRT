/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungmki <seungmki@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:06:10 by seungmki          #+#    #+#             */
/*   Updated: 2021/03/09 19:06:14 by seungmki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
R(t) = o + td  |  x² + z² = r²  |  (ox+tdx)² + (oz+tdz)² = r²
(ox)² + 2oxtdx + (tdx)² + (oz)² + 2oztdz + (tdz)² = r²
t²(dx + dz) + 2t(oxdx + ozdz) + (ox)² + (oz)² - r² = 0
a=(dx + dz); b = 2(oxdx + ozdz); c = (ox)² + (oz)² - r²
이 공식 이용해 교차점 몇 개인지 파악하게 하는 계수 확보
*/
void	get_cylinder_surface(t_scene *s, t_ray *r, int i)
{
	t_cylinder	*tmp;
	double		sub;

	tmp = s->cylinder[i];
	if (is_vec3_void(r->origin) != 0)//세계 좌표로 카메라 중심에서 도형 위치 빼서 벡터 oc 확보
		tmp->oc = vec3_subtraction(r->origin, tmp->point);
	else//r->origin == 0,0,0면 파싱한 카메라 중심에서 도형 위치 빼서 벡터 oc 확보
		tmp->oc = vec3_subtraction(s->camera[s->i_cam]->pos,
		tmp->point);
	sub = vec3_dot_product(r->global, tmp->n);//r->global은 캔버스 좌표 P를 세계 좌표 P'로 바꾼 걸 정규화한 것
	tmp->a = 1 - sub * sub;
	sub = vec3_dot_product(tmp->oc, tmp->n);
	tmp->b = 2 * (vec3_dot_product(r->global, tmp->oc) -
		vec3_dot_product(r->global, tmp->n) *
		vec3_dot_product(tmp->oc, tmp->n));
	tmp->c = vec3_dot_product(tmp->oc, tmp->oc) - sub * sub -
		tmp->radius * tmp->radius;
	tmp->delta = tmp->b * tmp->b - 4 * tmp->a * tmp->c;//교차점이 몇 개인지 알 수 있는 판별자 확보
}

int		is_ray_intersect_cylinder(t_scene *s, t_ray *r, int i)
{
	double		t;
	t_cylinder	*tmp;

	tmp = s->cylinder[i];
	get_cylinder_surface(s, r, i);//교차점 몇 개인지 판별하게 하는 delta 확보
	if (tmp->delta < 0)
		return (0);//delta > 0은 교차점 2개, delta = 0은 1개, delta < 0은 없음
	t = 0;
	tmp->x1 = (sqrt(tmp->delta) - tmp->b) / (2 * tmp->a);
	tmp->x2 = (-tmp->b - sqrt(tmp->delta)) / (2 * tmp->a);//교차점 거리 2개 확보해옴
	if (tmp->x1 > tmp->x2)
		t = tmp->x2;//둘 중 가까운 것 선택
	if (t < 0 || (t > r->t && is_vec3_void(r->origin) == 0))
		return (0);//광선 뒤에 있거나 원통 교차점 앞에 다른 도형 있으면 교차 안 함
	r->t = t;
	return (1);
}

void	get_cylinder_color(t_scene s, t_ray *r, int i)
{
	t_obj_clr obj;

	obj.p = s.cylinder[i]->p;//교차점 전달
	obj.normal = s.cylinder[i]->n_surface;//교차점의 법선 전달
	obj.rgb = s.cylinder[i]->rgb;
	r->color = obj_color_to_canvas(s, obj);
}

void	draw_cylinder_on_canvas(t_scene s, t_ray *r, int i)
{
	double		t;
	t_cylinder	*tmp;

	g_now_obj = s.cylinder[i]->filter == 'r' ? 'c' : 0;
	t = r->t;
	tmp = s.cylinder[i];
	if ((is_ray_intersect_cylinder(&s, r, i)) != 0)
	{//광선과 원통이 교차하는지, 교차한다면 교차점까지의 거리 t 확보
		tmp->p = vec3_add_vec3(s.camera[s.i_cam]->pos,//r->global은 캔버스 좌표 P를 세계 좌표 P'로 바꾼 것을 정규화한 것
			scalar_multiply_vec3(r->t, r->global));//세계 좌표 P' 방향에 r->t만큼 곱한 후 그걸 카메라 좌표에 더하면 교차점 p 나옴
		tmp->m = vec3_dot_product(tmp->n,
			vec3_subtraction(tmp->p, tmp->point));//교차점에서 아랫점 빼서 확보한 벡터와 내적해 각도 확보
		tmp->center = vec3_add_vec3(tmp->point,//교차점과 수직인 중심 확보
			scalar_multiply_vec3(tmp->m, tmp->n));
		tmp->n_surface = vec3_subtraction(tmp->p, tmp->center);//교차점에서의 법선 확보
		if (tmp->m < tmp->height && tmp->m > 0)
		{//m이 0부다 크면서 높이보다 작아야 원통 몸통의 교차점 색을 가져올 수 있음
			get_cylinder_color(s, r, i);
			return ;
		}
		r->t = t;
	}
	draw_cylinder_cap(s, r, i);//캡이 보이면 캡 그려줘야 함
}
