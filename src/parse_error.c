/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:33:31 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 13:33:33 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "unistd.h"

int	parse_error(char *s, char **toks)
{
	printf("Error\n%s\n", s);
	free_split(toks);
	return (1);
}

void	free_world(t_world *world)
{
	if (!world)
		return ;
	if (world->objs.spheres)
	{
		free(world->objs.spheres);
		world->objs.spheres = NULL;
		world->objs.sphere_len = 0;
		world->objs.sphere_cap = 0;
	}
	if (world->objs.planes)
	{
		free(world->objs.planes);
		world->objs.planes = NULL;
		world->objs.plane_len = 0;
		world->objs.plane_cap = 0;
	}
	if (world->objs.cylinders)
	{
		free(world->objs.cylinders);
		world->objs.cylinders = NULL;
		world->objs.cylinder_len = 0;
		world->objs.cylinder_cap = 0;
	}
}

void	cleanup_memories(t_world *world, int fd, char *line)
{
	if (world)
		free_world(world);
	if (fd >= 0)
		close(fd);
	if (line)
		free(line);
}

void	parse_clean_exit(char *msg, t_world *world, int fd, char *line)
{
	if (msg)
		printf("Error\n%s\n", msg);
	cleanup_memories(world, fd, line);
	exit(EXIT_FAILURE);
}
