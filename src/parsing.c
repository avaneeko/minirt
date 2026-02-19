/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:36:01 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:18:02 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	parse_line(t_world *world, char *line)
{
	if (!line || line[0] == '\0')
		return (0);
	if (line[0] == 'A' && line[1] == ' ')
		return (parse_ambient(world, line));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_camera(world, line));
	else if (line[0] == 'L' && line[1] == ' ')
		return (parse_light(world, line));
	else if (line[0] == 's' && line[1] == 'p' && line[2] == ' ')
		return (parse_sphere(world, line));
	else if (line[0] == 'p' && line[1] == 'l' && line[2] == ' ')
		return (parse_plane(world, line));
	else if (line[0] == 'c' && line[1] == 'y' && line[2] == ' ')
		return (parse_cylinder(world, line));
	else
		return (parse_error("Map error, cannot parse content", NULL));
}

static int	file_end_with_rt(char const *filename)
{
	int	len;

	if (!filename[0])
		return (1);
	len = slen(filename);
	if (len < 4)
		return (1);
	if (ft_strcmp(filename + len - 3, ".rt"))
		return (1);
	return (0);
}

static void	file_handler(t_world *world, int *fd, char const *filename)
{
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		parse_clean_exit("File open failed", world, -1, NULL);
}

void	parsing(t_world *world, int ac, char const *filename)
{
	char	*old_line;
	char	*line;
	int		fd;

	if (ac != 2)
		parse_clean_exit("Argc must be 2", world, -1, NULL);
	if (file_end_with_rt(filename))
		parse_clean_exit("File must end with .rt", world, -1, NULL);
	file_handler(world, &fd, filename);
	while (1)
	{
		old_line = get_next_line(fd);
		if (old_line == NULL)
			break ;
		line = trim_line(old_line);
		free(old_line);
		if (!line)
			parse_clean_exit("Fail to trim line", world, fd, NULL);
		if (parse_line(world, line))
			parse_clean_exit(NULL, world, fd, line);
		free(line);
	}
	if (!world->ambient.is_set || !world->cam.is_set || !world->light.is_set)
		parse_clean_exit("Missing required elements", world, fd, NULL);
	close(fd);
}
