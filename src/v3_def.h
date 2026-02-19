/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_def.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:27:06 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/19 12:17:10 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V3_DEF_H
# define V3_DEF_H

/**
 * This file defines vector3.
 */

# include "minitypes.h"

struct s_v3
{
	t_f32	x;
	t_f32	y;
	t_f32	z;
};
typedef struct s_v3	t_v3;

#endif
