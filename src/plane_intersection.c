#include "plane_intersection.h"
#include <math.h>

static
int	ray_intersect_plane_dist(t_plane const *pl, t_ray const *r,
								t_f32 dist_min, t_f32 dist_max,
								t_f32 *out_dist)
{
	t_f32	denom;
	t_v3	p0_minus_o;
	t_f32	dist;

	denom = v3_dot(&pl->ang, &r->dir);
	if (fabsf(denom) < 1e-6f)
		return 0;

	v3_sub(&pl->pos, &r->pos, &p0_minus_o); /* P0 - O */
	dist = v3_dot(&pl->ang, &p0_minus_o) / denom;

	if (dist < dist_min || dist > dist_max)
		return 0;

	*out_dist = dist;
	return 1;
}

void intersect_planes(t_plane_intersection_desc const *desc)
{
	t_f32	closest;
	t_u32	best_idx;
	t_u32	i;
	t_f32	d;

	closest = desc->dist_max;
	best_idx = ~(t_u32)0;

	i = 0;
	while (i < desc->plane_len)
	{
		if (ray_intersect_plane_dist(&desc->planes[i], &desc->ray,
										desc->dist_min, closest, &d))
		{
			closest = d;
			best_idx = i;
		}
		i++;
	}

	if (best_idx == ~(t_u32)0)
		return;

	desc->hit->dist = closest;
	desc->hit->col = desc->planes[best_idx].col;

	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);

	desc->hit->norm = desc->planes[best_idx].ang;
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}
