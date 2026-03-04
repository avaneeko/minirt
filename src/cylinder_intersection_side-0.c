/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_side-0.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:25 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:28:10 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_def.h"
#include "cylinder_side_context_def.h"
#include "ray_def.h"
#include "v3.h"
#include <math.h>

static
t_v3	v3_perp(t_v3 v, t_v3 axis, t_f64 v_par)
{
	v.x -= axis.x * v_par;
	v.y -= axis.y * v_par;
	v.z -= axis.z * v_par;
	return (v);
}

static
int	cyl_side_height_ok(t_cyl_side_ctx const *ctx, t_f64 t)
{
	t_f64	y;

	y = ctx->oc_par + t * ctx->d_par;
	return (fabs(y) <= ctx->half_h);
}

int	cyl_side_setup(t_cyl_side_ctx *ctx, t_cylinder const *cyl, t_ray const *r)
{
	ctx->half_h = cyl->h;
	v3_sub(&r->pos, &cyl->pos, &ctx->oc);
	ctx->d_par = v3_dot(&r->dir, &cyl->ang);
	ctx->oc_par = v3_dot(&ctx->oc, &cyl->ang);
	ctx->d_perp = v3_perp(r->dir, cyl->ang, ctx->d_par);
	ctx->oc_perp = v3_perp(ctx->oc, cyl->ang, ctx->oc_par);
	ctx->a = v3_dot(&ctx->d_perp, &ctx->d_perp);
	if (ctx->a < 1e-8f)
		return (0);
	ctx->b = 2.0f * v3_dot(&ctx->d_perp, &ctx->oc_perp);
	ctx->c = v3_dot(&ctx->oc_perp, &ctx->oc_perp) - cyl->r * cyl->r;
	return (1);
}

int	cyl_side_roots(t_cyl_roots *rt, t_cyl_side_ctx const *ctx)
{
	t_f64	disc;
	t_f64	sqrtd;

	disc = ctx->b * ctx->b - 4.0f * ctx->a * ctx->c;
	if (disc < 0.0f)
		return (0);
	sqrtd = sqrt(disc);
	rt->t0 = (-ctx->b - sqrtd) / (2.0f * ctx->a);
	rt->t1 = (-ctx->b + sqrtd) / (2.0f * ctx->a);
	return (1);
}

int	cyl_side_pick_t(t_f64 *out_t, t_cyl_roots const *rt,
		t_cyl_side_ctx const *ctx, t_ray_limits const *lim)
{
	t_f64	t;

	t = rt->t0;
	if (t < lim->min || t > lim->max)
		t = rt->t1;
	if (t < lim->min || t > lim->max)
		return (0);
	if (!cyl_side_height_ok(ctx, t))
	{
		if (t == rt->t0)
			t = rt->t1;
		if (t < lim->min || t > lim->max)
			return (0);
		if (!cyl_side_height_ok(ctx, t))
			return (0);
	}
	*out_t = t;
	return (1);
}
