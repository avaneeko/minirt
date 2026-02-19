/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:34:57 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:04:30 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "sphere_def.h"
#include "stdlib.h"
#include "world_def.h"

static int	push_to_world_sphere(t_world *world, t_sphere sphere)
{
	t_u32		new_cap;
	t_sphere	*new_arr;
	t_u32		i;

	i = ~0;
	if (world->objs.sphere_len == world->objs.sphere_cap)
	{
		if (world->objs.sphere_cap != 0)
		{
			world->objs.sphere_cap *= 2;
			new_cap = world->objs.sphere_cap;
		}
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_sphere));
		if (!new_arr)
			return (1);
		while (++i < world->objs.sphere_len)
			new_arr[i] = world->objs.spheres[i];
		free(world->objs.spheres);
		world->objs.spheres = new_arr;
		world->objs.sphere_cap = new_cap;
	}
	world->objs.spheres[world->objs.sphere_len++] = sphere;
	return (0);
}

static int	fill_sphere(t_sphere *sp, char **toks)
{
	if (parse_vec3(toks[1], &sp->pos))
		return (parse_error("Invalid sphere position", toks));
	if (parse_number(toks[2], &sp->r)) // chekc in render if /2
		return (parse_error("Invalid sphere diameter", toks));
	if (sp->r <= 0)
		return (parse_error("Sphere diameter should be > 0", toks));
	sp->r /= 2.f;
	if (parse_color(toks[3], &sp->col))
		return (parse_error("Invalid sphere color", toks));
	return (0);
}

int	parse_sphere(t_world *world, char const *line)
{
	int			tok_count;
	char		**toks;
	t_sphere	sp;

	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		return (parse_error("Sphere needs 4 tokens", toks));
	if (fill_sphere(&sp, toks))
		return (1);
	if (push_to_world_sphere(world, sp))
		return (parse_error("Sphere malloc fail", toks));
	free_split(toks);
	return (0);
}
