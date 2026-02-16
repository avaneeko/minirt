/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:25:39 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:25:39 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_INTERSECTION_H
# define PLANE_INTERSECTION_H

# include "plane_intersection_desc.h"

void
intersect_planes(t_plane_intersection_desc const *desc);

#endif
