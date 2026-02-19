/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:33:53 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 18:24:21 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	fill_light(t_world *world, char **toks, int tok_count)
{
	if (parse_vec3(toks[1], &world->light.pos))
		return (parse_error("Invalid light point", toks));
	if (parse_number(toks[2], &world->light.bright))
		return (parse_error("Invalid light brightness", toks));
	if (world->light.bright > 1.0 || world->light.bright < 0.0)
		return (parse_error("Brightness ratio range 0.0 - 1.0", toks));
	if (tok_count == 4)
		if (parse_color(toks[3], &world->light.col))
			return (parse_error("Light color range 0 - 255", toks));
	return (0);
}

int	parse_light(t_world *world, char const *line)
{
	int		tok_count;
	char	**toks;

	toks = NULL;
	tok_count = 0;
	if (world->light.is_set == 1)
		return (parse_error("Only one light set allowed", toks));
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (!(tok_count == 3 || tok_count == 4))
		return (parse_error("Light needs 3 tokens", toks));
	if (fill_light(world, toks, tok_count))
		return (1);
	world->light.is_set = 1;
	free_split(toks);
	return (0);
}
