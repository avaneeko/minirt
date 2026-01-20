#include "minirt.h"

// check .rt extension
// open file
// ambient lighting
// camera
// light
// sphere or plane cylinder

#include <stdio.h>

void parse_line(char *line)
{
	
}

void parse_error(int code, char *s)
{
	printf("%s\n", s);
	exit(code);
}
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
		parse_error(EXIT_FAILURE, "argc must be 2");
	if (!file_end_with_rt(filename))
		parse_error(EXIT_FAILURE, "file must end with .rt");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		parse_error(EXIT_FAILURE, "file open failed");
	while (1)
	{
		line = get_next_line(fd);
		parse_line(line);
		//printf("%s", line);
		if (line == NULL)
			break;
	}
}