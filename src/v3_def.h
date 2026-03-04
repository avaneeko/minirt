/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3_def.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:27:06 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
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
	t_f64	x;
	t_f64	y;
	t_f64	z;
};
typedef struct s_v3	t_v3;

#endif
