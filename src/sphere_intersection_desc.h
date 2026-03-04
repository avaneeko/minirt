/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection_desc.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:26:48 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_INTERSECTION_DESC_H
# define SPHERE_INTERSECTION_DESC_H

/**
 * Sphere intersection descriptor.
 *
 * This describes all the information needed to calculate the closest sphere
 * intersection.
 */

# include "sphere_def.h"
# include "hit_def.h"
# include "ray_def.h"

struct s_sphere_intersection_desc
{
	t_sphere const	*spheres;
	t_u32			sphere_len;
	t_ray			ray;
	t_f64			dist_min;
	t_f64			dist_max;
	t_hit			*hit;
};
typedef struct s_sphere_intersection_desc	t_sphere_intersection_desc;

#endif
