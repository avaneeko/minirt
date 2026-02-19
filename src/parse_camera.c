/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:25:14 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:08:56 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	fill_camera(t_world *world, char **toks)
{
	if (parse_vec3(toks[1], &world->cam.pos))
		return (parse_error("Invalid Camera position", toks));
	if (parse_vec3(toks[2], &world->cam.fwd))
		return (parse_error("Invalid Camera orientation vector", toks));
	if (check_unit_vector(world->cam.fwd))
		return (parse_error("Invalid Camera orientation vector", toks));
	if (parse_number(toks[3], &world->cam.fov))
		return (parse_error("Invalid Camera field of view", toks));
	if (world->cam.fov < 0 || world->cam.fov > 180)
		return (parse_error("Field of view range 0 - 180", toks));
	world->cam.fov *= 0.0174532925;
	return (0);
}

int	parse_camera(t_world *world, char const *line)
{
	int		tok_count;
	char	**toks;

	tok_count = 0;
	toks = NULL;
	if (world->cam.is_set)
		return (parse_error("Only one camera set allowed", toks));
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		return (parse_error("Camera position needs 4 tokens", toks));
	if (fill_camera(world, toks))
		return (1);
	world->cam.is_set = 1;
	free_split(toks);
	return (0);
}
