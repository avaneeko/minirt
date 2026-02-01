#include <iso646.h>
#include <math.h>
#include "sphere_intersection.h"

int	sphere_intersect_dist(t_sphere const *sp, t_ray const *r,
							t_f32 dist_min, t_f32 dist_max,
							t_f32 *out_dist)
{
	t_v3	oc;
	t_f32	a, b, c;
	t_f32	disc, sqrtd;
	t_f32	d0, d1;

	v3_sub(&sp->pos, &r->pos, &oc); /* oc = C - O */

	a = v3_dot(&r->dir, &r->dir);
	b = -2.0f * v3_dot(&r->dir, &oc);
	c = v3_dot(&oc, &oc) - sp->r * sp->r;

	disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
		return 0;

	sqrtd = sqrtf(disc);
	d0 = (-b - sqrtd) / (2.0f * a);
	d1 = (-b + sqrtd) / (2.0f * a);

	if (d0 >= dist_min && d0 <= dist_max)
		return (*out_dist = d0, 1);
	if (d1 >= dist_min && d1 <= dist_max)
		return (*out_dist = d1, 1);
	return 0;
}

void
intersect_spheres(t_sphere_intersection_desc const *desc)
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
									desc->dist_min, closest, &d))
		{
			closest = d;
			best_idx = i;
		}
		i++;
	}

	if (best_idx == ~(t_u32)0)
		return ;

	desc->hit->dist = closest; /* before or after early dist reject? */

	/* material/color */
	desc->hit->col = desc->spheres[best_idx].col;

	/* pos = O + D*dist */
	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);

	/* norm = normalize((pos - C) / r) */
	v3_sub(&desc->hit->pos, &desc->spheres[best_idx].pos, &desc->hit->norm);
	v3_scalar_div(&desc->hit->norm, desc->spheres[best_idx].r, &desc->hit->norm);

	/* faceforward */
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}
