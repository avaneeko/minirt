/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_def.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:25:45 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:25:48 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_DEF_H
# define RAY_DEF_H

/**
 * Defines ray struct which has an origin and a direction.
 */

# include "v3_def.h"

struct s_ray
{
	t_v3	pos;
	t_v3	dir;
};
typedef struct s_ray	t_ray;

#endif
