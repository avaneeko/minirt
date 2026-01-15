#include "minirt.h"

// check .rt extension
// open file
// ambient lighting
// camera
// light
// sphere or plane cylinder

#include <stdio.h>
static bool file_end_with_rt(char *filename)
{
	int	len;

	if (!filename[0])
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	if (ft_strcmp(filename + len  - 3, ".rt"))
		return (false);
	return (true);
}

void parsing(t_scene *scene, int ac, char *filename)
{
	(void)scene;
	char *line;
	int fd;
	if (ac != 2)
		exit (EXIT_FAILURE);
	if (!file_end_with_rt(filename))
		exit (EXIT_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit (EXIT_FAILURE);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break;
	}
}