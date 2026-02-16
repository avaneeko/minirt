/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_from_pixel.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:22:54 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:22:55 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_FROM_PIXEL_H
# define RAY_FROM_PIXEL_H

# include "ray_def.h"
# include "cam_def.h"

t_ray	ray_from_pixel(t_cam const *cam, int x, int y);

#endif
