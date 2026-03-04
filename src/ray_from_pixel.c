/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_from_pixel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:22:52 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_from_pixel.h"
#include "config.h"
#include "v3.h"

t_ray	ray_from_pixel(t_cam const *cam, int x, int y)
{
	t_f64	u;
	t_f64	v;
	t_f64	sx;
	t_f64	sy;
	t_v3	dir;

	u = ((t_f64)x + 0.5f) / (t_f64)WINDOW_WIDTH;
	v = ((t_f64)y + 0.5f) / (t_f64)WINDOW_HEIGHT;
	sx = (2.0f * u - 1.0f) * cam->half_w;
	sy = (1.0f - 2.0f * v) * cam->half_h;
	dir = cam->fwd;
	dir.x += cam->right.x * sx + cam->up.x * sy;
	dir.y += cam->right.y * sx + cam->up.y * sy;
	dir.z += cam->right.z * sx + cam->up.z * sy;
	v3_normalize(&dir);
	return ((t_ray){cam->pos, dir});
}
