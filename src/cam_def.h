/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_def.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:24:12 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:24:12 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAM_DEF_H
# define CAM_DEF_H

# include "v3_def.h"

struct s_cam
{
	t_v3	pos;	/* Position in world space. */
	t_v3	dir;	/* View angles (normalized). */
	t_v3	fwd;	/* Forward vector. */
	t_v3	right;	/* Right vector. */
	t_v3	up;		/* Up vector. */
	t_f32	fov;	/* Field of view (in radians). */
	t_f32	aspect;	/* Aspect ratio. */
	t_f32	half_w;	/* Half of window width. */
	t_f32	half_h;	/* Half of window height. */
	t_u8	is_set;	/* Parser state. */
};
typedef struct s_cam	t_cam;

#endif
