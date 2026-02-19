/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:24:38 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 18:23:35 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ambient_def.h"
#include "parsing.h"
#include "world_def.h"
#include <stdlib.h>

int	parse_ambient(t_world *world, char const *line)
{
	int		tok_count;
	char	**toks;

	tok_count = 0;
	toks = NULL;
	if (world->ambient.is_set)
		return (parse_error("Only one ambient set allowed", toks));
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		return (parse_error("Line should start with specifier", toks));
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 3)
		return (parse_error("Ambient light needs 3 tokens", toks));
	if (parse_number(toks[1], &world->ambient.bright))
		return (parse_error("Invalid ambient brightness", toks));
	if (world->ambient.bright > 1.0 || world->ambient.bright < 0.0)
		return (parse_error("Ratio must be 0.0 - 1.0", toks));
	if (parse_color(toks[2], &world->ambient.col))
		return (parse_error("Invalid ambient color", toks));
	world->ambient.is_set = 1;
	free_split(toks);
	return (0);
}
