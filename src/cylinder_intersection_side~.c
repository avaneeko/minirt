/**
 * This file is included directly since it defines static functions,
 * please do not include it into the build system.
 */

/**
 * Defines logic for intersecting the cylinder side (the round tube part).
 */

#include "cylinder_intersection_desc.h"
#include <math.h>

/**
 * Intersect with the side of the cylinder (the round part), NOT the flat part.
 * Only calculates the intersection distance.
 *
 * Returns non-zero on hit.
 */
static
int	ray_intersect_cylinder_side(t_cylinder const *cyl, t_ray const *r,
		t_f32 dist_min, t_f32 dist_max, t_f32 *out_dist)
{
	t_v3	oc;
	t_f32	d_par, oc_par;
	t_v3	d_perp, oc_perp;
	t_f32	a, b, c, disc, sqrtd;
	t_f32	t0, t1, t;
	t_f32	y;
	t_f32	half_h;

	half_h = cyl->h; /* treat h as half_h already. */

	/* oc = O - C */
	v3_sub(&r->pos, &cyl->pos, &oc);

	d_par = v3_dot(&r->dir, &cyl->ang);
	oc_par = v3_dot(&oc, &cyl->ang);

	/* d_perp = D - A*d_par */
	d_perp = r->dir;
	d_perp.x -= cyl->ang.x * d_par;
	d_perp.y -= cyl->ang.y * d_par;
	d_perp.z -= cyl->ang.z * d_par;

	/* oc_perp = oc - A*oc_par */
	oc_perp = oc;
	oc_perp.x -= cyl->ang.x * oc_par;
	oc_perp.y -= cyl->ang.y * oc_par;
	oc_perp.z -= cyl->ang.z * oc_par;

	a = v3_dot(&d_perp, &d_perp);
	if (a < 1e-8f) /* ray almost parallel to axis */
		return 0;

	b = 2.0f * v3_dot(&d_perp, &oc_perp);
	c = v3_dot(&oc_perp, &oc_perp) - cyl->r * cyl->r;

	disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
		return 0;

	sqrtd = sqrtf(disc);
	t0 = (-b - sqrtd) / (2.0f * a);
	t1 = (-b + sqrtd) / (2.0f * a);

	/* nearest valid root that also satisfies height clamp */
	t = t0;
	if (t < dist_min || t > dist_max)
		t = t1;
	if (t < dist_min || t > dist_max)
		return 0;

	y = oc_par + t * d_par;
	if (fabsf(y) > half_h)
	{
		/* try the other root */
		t = (t == t0) ? t1 : t0;
		if (t < dist_min || t > dist_max)
			return 0;
		y = oc_par + t * d_par;
		if (fabsf(y) > half_h)
			return 0;
	}

	*out_dist = t;
	return 1;
}

/**
 * Calculates the cylinder side hit normal.
 *
 * Requires flipping if dot(ray.dir, hit.norm) < 0.0f.
 */
static
void side_normal(t_cylinder const *cy, t_v3 const *p, t_v3 *out_n)
{
	t_v3	v;
	t_f32	k;

	/* v = P - C */
	v3_sub(p, &cy->pos, &v);

	/* k = dot(v, A) */
	k = v3_dot(&v, &cy->ang);

	/* out_n = v - A*k */
	out_n->x = v.x - cy->ang.x * k;
	out_n->y = v.y - cy->ang.y * k;
	out_n->z = v.z - cy->ang.z * k;

	v3_normalize_safe(out_n);
}

static
void	intersect_cylinder_side(t_cylinder_intersection_desc const *desc)
{
	t_f32	closest;
	t_u32	best_idx;
	t_u32	i;
	t_f32	d;

	closest = desc->dist_max;
	best_idx = ~(t_u32)0;

	i = 0;
	while (i < desc->cylinder_len)
	{
		if (ray_intersect_cylinder_side(desc->cylinders + i, &desc->ray,
									desc->dist_min, closest, &d))
		{
			best_idx = i;
			closest = d;
		}
		i++;
	}

	if (best_idx == ~(t_u32)0)
		return ;

	desc->hit->dist = closest;
	desc->hit->col = desc->cylinders[best_idx].col;

	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);
	side_normal(desc->cylinders + best_idx, &desc->hit->pos, &desc->hit->norm);
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}
