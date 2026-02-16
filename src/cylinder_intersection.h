/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:31:20 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:31:21 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_INTERSECTION_H
# define CYLINDER_INTERSECTION_H

# include "cylinder_intersection_desc.h"

void
intersect_cylinders(t_cylinder_intersection_desc const *desc);

#endif
