/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:26:54 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:26:54 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_INTERSECTION_H
# define SPHERE_INTERSECTION_H

/**
 * Sphere intersection functions.
 */

# include "sphere_intersection_desc.h"

void
intersect_spheres(t_sphere_intersection_desc const *desc);

#endif
