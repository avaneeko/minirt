/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_side.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:18 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Defines logic for intersecting the cylinder side (the round tube part).
 */

#include "cylinder_intersection_desc.h"
#include "cylinder_side_context_def.h"
#include "v3.h"

int	cyl_side_setup(t_cyl_side_ctx *ctx, t_cylinder const *cyl, t_ray const *r);
int	cyl_side_roots(t_cyl_roots *rt, t_cyl_side_ctx const *ctx);
int	cyl_side_pick_t(t_f64 *out_t, t_cyl_roots const *rt,
		t_cyl_side_ctx const *ctx, t_ray_limits const *lim);

/**
 * Intersect with the side of the cylinder (the round part), NOT the flat part.
 * Only calculates the intersection distance.
 *
 * Returns non-zero on hit.
 */
static
int	ray_intersect_cylinder_side(t_cylinder const *cyl, t_ray const *r,
		t_ray_limits const *lim)
{
	t_cyl_side_ctx	ctx;
	t_cyl_roots		rt;
	t_f64			t;

	if (!cyl_side_setup(&ctx, cyl, r))
		return (0);
	if (!cyl_side_roots(&rt, &ctx))
		return (0);
	if (!cyl_side_pick_t(&t, &rt, &ctx, lim))
		return (0);
	*(lim->out) = t;
	return (1);
}

/**
 * Calculates the cylinder side hit normal.
 *
 * Requires flipping if dot(ray.dir, hit.norm) < 0.0f.
 */
static
void	side_normal(t_cylinder const *cy, t_v3 const *p, t_v3 *out_n)
{
	t_v3	v;
	t_f64	k;

	v3_sub(p, &cy->pos, &v);
	k = v3_dot(&v, &cy->ang);
	out_n->x = v.x - cy->ang.x * k;
	out_n->y = v.y - cy->ang.y * k;
	out_n->z = v.z - cy->ang.z * k;
	v3_normalize_safe(out_n);
}

static
void	fill_hit(t_cylinder_intersection_desc const *desc,
			t_u32 best_idx, t_f64 closest)
{
	desc->hit->dist = closest;
	desc->hit->col = desc->cylinders[best_idx].col;
	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);
	side_normal(desc->cylinders + best_idx, &desc->hit->pos, &desc->hit->norm);
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}

void	intersect_cylinder_side(t_cylinder_intersection_desc const *desc)
{
	t_f64	closest;
	t_u32	best_idx;
	t_u32	i;
	t_f64	d;

	closest = desc->dist_max;
	best_idx = ~(t_u32)0;
	i = 0;
	while (i < desc->cylinder_len)
	{
		if (ray_intersect_cylinder_side(desc->cylinders + i, &desc->ray,
				&(t_ray_limits const){desc->dist_min, closest, &d}))
		{
			best_idx = i;
			closest = d;
		}
		i++;
	}
	if (best_idx == ~(t_u32)0)
		return ;
	fill_hit(desc, best_idx, closest);
}
