/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3-2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:27:14 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:28:13 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v3_def.h"
#include <math.h>

t_f64	v3_len(t_v3 const *a)
{
	return (sqrt(a->x * a->x + a->y * a->y + a->z * a->z));
}

t_f64	v3_len2(t_v3 const *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

void	v3_normalize(t_v3 *a)
{
	t_f64 const	norm = v3_len(a);

	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
}

void	v3_normalize_to(t_v3 const *a, t_v3 *dst)
{
	t_f64 const	norm = v3_len(a);

	dst->x = a->x / norm;
	dst->y = a->y / norm;
	dst->z = a->z / norm;
}

int	v3_normalize_safe(t_v3 *a)
{
	t_f64 const	epsilon = __FLT_EPSILON__ * 10.f;
	t_f64 const	norm = v3_len(a);

	if (isnan(norm) || norm < epsilon)
		return (0);
	a->x /= norm;
	a->y /= norm;
	a->z /= norm;
	return (!isnan(a->x) && !isnan(a->y) && !isnan(a->z));
}
