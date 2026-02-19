/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:25:44 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:19:38 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cylinder_def.h"
#include "parsing.h"
#include "world_def.h"
#include <stdlib.h>

static int	push_to_world_cylinder(t_world *world, t_cylinder cylinder)
{
	t_u32		new_cap;
	t_cylinder	*new_arr;
	t_u32		i;

	i = ~0;
	if (world->objs.cylinder_len == world->objs.cylinder_cap)
	{
		if (world->objs.cylinder_cap != 0)
		{
			world->objs.cylinder_cap *= 2;
			new_cap = world->objs.cylinder_cap;
		}
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_cylinder));
		if (!new_arr)
			return (1);
		while (++i < world->objs.cylinder_len)
			new_arr[i] = world->objs.cylinders[i];
		free(world->objs.cylinders);
		world->objs.cylinders = new_arr;
		world->objs.cylinder_cap = new_cap;
	}
	world->objs.cylinders[world->objs.cylinder_len++] = cylinder;
	return (0);
}

static int	fill_cylinder(t_cylinder *cy, char **toks)
{
	if (parse_vec3(toks[1], &cy->pos))
		return (parse_error("Cylinder center position invalid", toks));
	if (parse_vec3(toks[2], &cy->ang))
		return (parse_error("Cylinder angle invalid", toks));
	if (check_unit_vector(cy->ang))
		return (parse_error("Cylinder angle invalid", toks));
	if (parse_number(toks[3], &cy->r))
		return (parse_error("Cylinder diameter invalid", toks));
	if (parse_number(toks[4], &cy->h))
		return (parse_error("cylinder center position invalid", toks));
	if (cy->r <= 0 || cy->h <= 0)
		return (parse_error("Cylinder diameter and height are > 0", toks));
	cy->r /= 2.f;
	cy->h /= 2.f;
	if (parse_color(toks[5], &cy->col))
		return (parse_error("Cylinder color invalid", toks));
	return (0);
}

int	parse_cylinder(t_world *world, char const *line)
{
	int			tok_count;
	char		**toks;
	t_cylinder	cy;

	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 6)
		return (parse_error("Cylinder input invalid", toks));
	if (fill_cylinder(&cy, toks))
		return (1);
	if (push_to_world_cylinder(world, cy))
		return (parse_error("Cylinder malloc fail", toks));
	free_split(toks);
	return (0);
}
