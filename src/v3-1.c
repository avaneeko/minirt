/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3-1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:27:12 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3_def.h"

void	v3_scalar_add(t_v3 const *a, t_f64 b, t_v3 *dst)
{
	dst->x = a->x + b;
	dst->y = a->y + b;
	dst->z = a->z + b;
}

void	v3_scalar_sub(t_v3 const *a, t_f64 b, t_v3 *dst)
{
	dst->x = a->x - b;
	dst->y = a->y - b;
	dst->z = a->z - b;
}

void	v3_scalar_mul(t_v3 const *a, t_f64 b, t_v3 *dst)
{
	dst->x = a->x * b;
	dst->y = a->y * b;
	dst->z = a->z * b;
}

void	v3_scalar_div(t_v3 const *a, t_f64 b, t_v3 *dst)
{
	dst->x = a->x / b;
	dst->y = a->y / b;
	dst->z = a->z / b;
}

void	v3_muladds(t_v3 const *a, t_v3 const *b, t_f64 t, t_v3 *dst)
{
	dst->x = a->x + b->x * t;
	dst->y = a->y + b->y * t;
	dst->z = a->z + b->z * t;
}
