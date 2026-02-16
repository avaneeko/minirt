/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_def.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:26:44 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:26:44 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_DEF_H
# define SPHERE_DEF_H

# include "v3_def.h"

/**
 * This file contains the definition of the sphere.
 */

struct s_sphere
{
	t_v3	pos;	/* Position in world space. */
	t_f32	r;		/* Radius. */
	t_v3	col;	/* Color. */
};
typedef struct s_sphere	t_sphere;

#endif
