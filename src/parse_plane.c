/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:34:24 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 18:24:28 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "plane_def.h"
#include "world_def.h"
#include <stdlib.h>

static int	push_to_world_plane(t_world *world, t_plane plane)
{
	t_u32	new_cap;
	t_plane	*new_arr;
	t_u32	i;

	if (world->objs.plane_len == world->objs.plane_cap)
	{
		if (world->objs.plane_cap != 0)
		{
			world->objs.plane_cap *= 2;
			new_cap = world->objs.plane_cap;
		}
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_plane));
		if (!new_arr)
			return (1);
		i = ~0;
		while (++i < world->objs.plane_len)
			new_arr[i] = world->objs.planes[i];
		free(world->objs.planes);
		world->objs.planes = new_arr;
		world->objs.plane_cap = new_cap;
	}
	world->objs.planes[world->objs.plane_len++] = plane;
	return (0);
}

static int	fill_plane(t_plane *pl, char **toks)
{
	if (parse_vec3(toks[1], &pl->pos))
		return (parse_error("Invalid plane postion", toks));
	if (parse_vec3(toks[2], &pl->ang))
		return (parse_error("Invalid plane angle", toks));
	if (check_unit_vector(pl->ang))
		return (parse_error("Invalid plane angle", toks));
	if (parse_color(toks[3], &pl->col))
		return (parse_error("Invalid plane color", toks));
	return (0);
}

int	parse_plane(t_world *world, char const *line)
{
	int		tok_count;
	char	**toks;
	t_plane	pl;

	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		return (parse_error("Plane needs 4 tokens", toks));
	if (fill_plane(&pl, toks))
		return (1);
	if (push_to_world_plane(world, pl))
		return (parse_error("Plane malloc fail", toks));
	free_split(toks);
	return (0);
}
