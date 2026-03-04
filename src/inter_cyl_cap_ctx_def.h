/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cyl_cap_ctx_def.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:27:30 by losypenk          #+#    #+#             */
/*   Updated: 2026/03/04 10:19:46 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTER_CYL_CAP_CTX_DEF_H
# define INTER_CYL_CAP_CTX_DEF_H

# include "cylinder_def.h"
# include "ray_def.h"

struct s_inter_cyl_cap_ctx
{
	t_cylinder const	*cy;
	t_v3				cap_center;
	t_v3				cap_norm;
	t_ray const			*r;
	t_f64				dist_min;
	t_f64				dist_max;
	t_f64				*out_dist;
};
typedef struct s_inter_cyl_cap_ctx	t_inter_cyl_cap_ctx;

#endif
