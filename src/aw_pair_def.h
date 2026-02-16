/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aw_pair_def.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:22:50 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:22:50 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AW_PAIR_DEF_H
# define AW_PAIR_DEF_H

/*
	App-World pair.
*/

# include "app_def.h"
# include "world_def.h"

struct s_aw_pair
{
	t_app	*a;
	t_world	*w;
};
typedef struct s_aw_pair	t_aw_pair;

#endif
