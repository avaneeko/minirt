/**
 * This file is included directly since it defines static functions,
 * please do not include it into the build system.
 */

/**
 * Defines logic for intersecting the cylinder caps (the flat parts).
 */

#include "cylinder_intersection_desc.h"
#include <math.h>

static
int	ray_intersect_cylinder_cap(t_cylinder const *cy, t_v3 cap_center,
									t_v3 cap_norm, t_ray const *r,
									t_f32 dist_min, t_f32 dist_max,
									t_f32 *out_dist)
{
    t_f32 denom = v3_dot(&cap_norm, &r->dir);
    if (fabsf(denom) < 1e-6f)
        return 0;

    t_v3 oc;
    v3_sub(&cap_center, &r->pos, &oc);

    t_f32 t = v3_dot(&cap_norm, &oc) / denom;
    if (t < dist_min || t > dist_max)
        return 0;

    /* p = O + D*t */
    t_v3 p;
    v3_muladds(&r->pos, &r->dir, t, &p);

    /* radial check: distance from axis <= r */
    t_v3 v;
    v3_sub(&p, &cap_center, &v);

    t_f32 k = v3_dot(&v, &cy->ang);
    v.x -= cy->ang.x * k;
    v.y -= cy->ang.y * k;
    v.z -= cy->ang.z * k;

    if (v3_dot(&v, &v) > cy->r * cy->r)
        return 0;

    *out_dist = t;
    return 1;
}

static
void	intersect_cylinder_cap(t_cylinder_intersection_desc const *desc)
{
	t_f32	closest;
	t_u32	best_idx;
	t_u32	i;
	t_f32	d;
	t_u8	is_bot;

	closest = desc->hit->dist;
	best_idx = ~(t_u32)0;

	i = 0;
	while (i < desc->cylinder_len)
	{
		t_v3 top = desc->cylinders[i].pos;
		t_v3 bot = desc->cylinders[i].pos;

		top.x += desc->cylinders[i].ang.x * desc->cylinders[i].h;
		top.y += desc->cylinders[i].ang.y * desc->cylinders[i].h;
		top.z += desc->cylinders[i].ang.z * desc->cylinders[i].h;

		bot.x -= desc->cylinders[i].ang.x * desc->cylinders[i].h;
		bot.y -= desc->cylinders[i].ang.y * desc->cylinders[i].h;
		bot.z -= desc->cylinders[i].ang.z * desc->cylinders[i].h;

		if (ray_intersect_cylinder_cap(desc->cylinders + i, top,
									desc->cylinders[i].ang, &desc->ray, desc->dist_min, closest, &d))
		{
			best_idx = i;
			closest = d;
			is_bot = 0;
		}
		if (ray_intersect_cylinder_cap(desc->cylinders + i, bot,
									(t_v3){-desc->cylinders[i].ang.x, -desc->cylinders[i].ang.y, -desc->cylinders[i].ang.z}, &desc->ray, desc->dist_min, closest, &d))
		{
			best_idx = i;
			closest = d;
			is_bot = 1;
		}
		i++;
	}

	if (best_idx == ~(t_u32)0)
		return ;

	desc->hit->dist = closest;
	desc->hit->col = desc->cylinders[best_idx].col;

	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);

	if ( !is_bot )
		desc->hit->norm = desc->cylinders[best_idx].ang;
	else
		desc->hit->norm = (t_v3){-desc->cylinders[best_idx].ang.x,
									-desc->cylinders[best_idx].ang.y,
									-desc->cylinders[best_idx].ang.z};

	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}
