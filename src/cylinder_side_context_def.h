/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side_context_def.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:48 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_SIDE_CONTEXT_DEF_H
# define CYLINDER_SIDE_CONTEXT_DEF_H

# include "minitypes.h"
# include "v3_def.h"

struct s_ray_limits
{
	t_f64	min;
	t_f64	max;
	t_f64	*out;
};
typedef struct s_ray_limits		t_ray_limits;

struct s_cyl_side_ctx
{
	t_v3	oc;
	t_v3	d_perp;
	t_v3	oc_perp;
	t_f64	d_par;
	t_f64	oc_par;
	t_f64	a;
	t_f64	b;
	t_f64	c;
	t_f64	half_h;
};
typedef struct s_cyl_side_ctx	t_cyl_side_ctx;

struct s_cyl_roots
{
	t_f64	t0;
	t_f64	t1;
};
typedef struct s_cyl_roots		t_cyl_roots;

#endif
