/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:31:11 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:31:12 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_intersection.h"

void	intersect_cylinder_side(t_cylinder_intersection_desc const *desc);
void	intersect_cylinder_cap(t_cylinder_intersection_desc const *desc);

void	intersect_cylinders(t_cylinder_intersection_desc const *desc)
{
	intersect_cylinder_side(desc);
	intersect_cylinder_cap(desc);
}
