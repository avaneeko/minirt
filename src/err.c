/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 14:24:39 by losypenk          #+#    #+#             */
/*   Updated: 2026/02/19 15:54:19 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.h"
#include "parse_error.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

/**
 * Fatal error defines an application termination point that conveys the error
 * occurred to the user, performs a complete clean up of all resources held by
 * the application and gracefully exits the program.
 */

void	app_fatal_error(t_app *app, t_world *world, char const *msg)
{
	if (msg)
		(void)write_exact(2, msg, slen(msg));
	free_world(world);
	app_destroy(app);
	exit(1);
}
