/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_cap.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:56 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/19 11:37:45 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Defines logic for intersecting the cylinder caps (the flat parts).
 */

#include "cylinder_intersection_desc.h"
#include "inter_cyl_cap_ctx_def.h"
#include "minitypes.h"
#include "utils.h"
#include "v3.h"
#include <math.h>

/*
t is f[0]
k is f[1]
*/
static
int	ray_intersect_cylinder_cap(t_inter_cyl_cap_ctx const *ctx)
{
	t_f32 const	denom = v3_dot(&ctx->cap_norm, &ctx->r->dir);
	t_v3		oc;
	t_v3		p;
	t_f32		f[2];
	t_v3		v;

	if (fabsf(denom) < 1e-6f)
		return (0);
	v3_sub(&ctx->cap_center, &ctx->r->pos, &oc);
	f[0] = v3_dot(&ctx->cap_norm, &oc) / denom;
	if (f[0] < ctx->dist_min || f[0] > ctx->dist_max)
		return (0);
	v3_muladds(&ctx->r->pos, &ctx->r->dir, f[0], &p);
	v3_sub(&p, &ctx->cap_center, &v);
	f[1] = v3_dot(&v, &ctx->cy->ang);
	v.x -= ctx->cy->ang.x * f[1];
	v.y -= ctx->cy->ang.y * f[1];
	v.z -= ctx->cy->ang.z * f[1];
	if (v3_dot(&v, &v) > ctx->cy->r * ctx->cy->r)
		return (0);
	*ctx->out_dist = f[0];
	return (1);
}

static
void	fill_hit(t_cylinder_intersection_desc const *desc,
			t_u32 best_idx, t_f32 closest, t_u8 is_bot)
{
	if (best_idx == ~(t_u32)0)
		return ;
	desc->hit->dist = closest;
	desc->hit->col = desc->cylinders[best_idx].col;
	v3_muladds(&desc->ray.pos, &desc->ray.dir, closest, &desc->hit->pos);
	if (!is_bot)
		desc->hit->norm = desc->cylinders[best_idx].ang;
	else
		desc->hit->norm = (t_v3){-desc->cylinders[best_idx].ang.x,
			-desc->cylinders[best_idx].ang.y,
			-desc->cylinders[best_idx].ang.z};
	desc->hit->front = (v3_dot(&desc->ray.dir, &desc->hit->norm) < 0.0f);
	if (!desc->hit->front)
		v3_scalar_mul(&desc->hit->norm, -1.0f, &desc->hit->norm);
}

static
int	trace_caps(t_inter_cyl_cap_ctx *ctx, t_u8 *is_bot)
{
	t_v3	top;

	top = ctx->cy->pos;
	top.x += ctx->cy->ang.x * ctx->cy->h;
	top.y += ctx->cy->ang.y * ctx->cy->h;
	top.z += ctx->cy->ang.z * ctx->cy->h;
	mcpy(&ctx->cap_center, &top, sizeof(top));
	if (ray_intersect_cylinder_cap(ctx))
	{
		*is_bot = 0;
		return (1);
	}
	return (0);
}

static
int	trace_caps2(t_inter_cyl_cap_ctx *ctx, t_u8 *is_bot)
{
	t_v3	bot;

	bot = ctx->cy->pos;
	bot.x -= ctx->cy->ang.x * ctx->cy->h;
	bot.y -= ctx->cy->ang.y * ctx->cy->h;
	bot.z -= ctx->cy->ang.z * ctx->cy->h;
	mcpy(&ctx->cap_center, &bot, sizeof(bot));
	ctx->cap_norm.x = -ctx->cap_norm.x;
	ctx->cap_norm.y = -ctx->cap_norm.y;
	ctx->cap_norm.z = -ctx->cap_norm.z;
	if (ray_intersect_cylinder_cap(ctx))
	{
		*is_bot = 1;
		return (1);
	}
	return (0);
}

void	intersect_cylinder_cap(t_cylinder_intersection_desc const *desc)
{
	t_f32	closest;
	t_u32	best_idx;
	t_u32	i;
	t_f32	d;
	t_u8	is_bot;

	closest = desc->hit->dist;
	best_idx = ~(t_u32)0;
	i = ~0;
	while (++i < desc->cylinder_len)
	{
		if (trace_caps(&(t_inter_cyl_cap_ctx)
				{desc->cylinders + i, desc->cylinders[i].pos,
					desc->cylinders[i].ang, &desc->ray, desc->dist_min, closest,
					&d}, &is_bot)
			|| trace_caps2(&(t_inter_cyl_cap_ctx)
				{desc->cylinders + i, desc->cylinders[i].pos,
					desc->cylinders[i].ang, &desc->ray, desc->dist_min, closest,
					&d}, &is_bot))
		{
			best_idx = i;
			closest = d;
		}
	}
	fill_hit(desc, best_idx, closest, is_bot);
}
