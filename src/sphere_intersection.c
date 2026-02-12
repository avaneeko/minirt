#include "minitypes.h"
#include "v3.h"
#include "sphere_intersection.h"
#include <math.h>

void	fill_hit(t_sphere_intersection_desc const *desc,
			t_f32 closest, t_u32 best_idx)
{
	desc->hit->dist = closest;
	desc->hit->col = desc->spheres[best_idx].col;
	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);
	v3_sub(&desc->hit->pos, &desc->spheres[best_idx].pos, &desc->hit->norm);
	v3_scalar_div(&desc->hit->norm, desc->spheres[best_idx].r,
		&desc->hit->norm);
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}

/*
dist[0] is dist_min
dist[1] is dist_max
n[0] is a
n[1] is b
n[2] is c
n[3] is disc
n[4] is sqrtd
n[5] is d0
n[6] is d1
*/
int	sphere_intersect_dist(t_sphere const *sp, t_ray const *r,
							t_f32 dist[2],
							t_f32 *out_dist)
{
	t_v3	oc;
	t_f32	n[7];

	v3_sub(&sp->pos, &r->pos, &oc);
	n[0] = v3_dot(&r->dir, &r->dir);
	n[1] = -2.0f * v3_dot(&r->dir, &oc);
	n[2] = v3_dot(&oc, &oc) - sp->r * sp->r;
	n[3] = n[1] * n[1] - 4.0f * n[0] * n[2];
	if (n[3] < 0.0f)
		return (0);
	n[4] = sqrtf(n[3]);
	n[5] = (-n[1] - n[4]) / (2.0f * n[0]);
	n[6] = (-n[1] + n[4]) / (2.0f * n[0]);
	if (n[5] >= dist[0] && n[5] <= dist[1])
		return (*out_dist = n[5], 1);
	if (n[6] >= dist[0] && n[6] <= dist[1])
		return (*out_dist = n[6], 1);
	return (0);
}

void	intersect_spheres(t_sphere_intersection_desc const *desc)
{
	t_f32			closest;
	t_u32			best_idx;
	t_u32			i;
	t_f32			d;

	closest = desc->hit->dist;
	best_idx = ~(t_u32)0;
	i = 0;
	while (i < desc->sphere_len)
	{
		if (sphere_intersect_dist(desc->spheres + i, &desc->ray,
				(float []){desc->dist_min, closest}, &d))
		{
			closest = d;
			best_idx = i;
		}
		i++;
	}
	if (best_idx == ~(t_u32)0)
		return ;
	fill_hit(desc, closest, best_idx);
}
