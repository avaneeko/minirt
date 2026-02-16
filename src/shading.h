/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:26:26 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:26:26 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADING_H
# define SHADING_H

# include "shading_desc.h"
# include "hit_def.h"

/**
 * This file defines shading functions, they're run after
 * the intersection (raytracing) stage to determine the pixel's final color.
 */

t_v3
shade(t_hit const *hit, t_shading_desc const *desc);

#endif
