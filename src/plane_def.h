/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:23:35 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:23:36 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_DEF_H
# define PLANE_DEF_H

/**
 * This file defines the plane struct.
 */

# include "v3_def.h"

struct s_plane
{
	t_v3	pos;	/* Position.	*/
	t_v3	ang;	/* Angles.		*/
	t_v3	col;	/* Color.		*/
};
typedef struct s_plane	t_plane;

#endif
