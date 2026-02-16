/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:24:29 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/16 14:24:29 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app_def.h"
#include "mlx.h"
#include <stdlib.h>

void	app_destroy(t_app const *app)
{
	t_s32	i;

	if (app->mlx)
	{
		if (app->wnd)
			mlx_destroy_window(app->mlx, app->wnd);
		if (app->fb_cnt)
		{
			i = 0;
			while (i < app->fb_cnt)
				mlx_destroy_image(app->mlx, app->fb[app->fb_cnt - 1 - i++]);
			free(app->fb);
		}
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
}
