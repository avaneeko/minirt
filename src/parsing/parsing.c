#include "minirt.h"

// check .rt extension
// open file
// ambient lighting
// camera
// light
// sphere or plane cylinder

void parse_line(t_world *world, char *line)
{
	if (!line)
		return ; //FIX ME
	if (line[0] == 'A')
		parse_ambient(world, line);
	 else if (line[0] == 'C')
	 	parse_camera(world, line);
	else if (line[0] == 'L')
	 	parse_light(world, line);
	// else if (line[0] == 's' && line[1] == 'p')
	// 	parse_sphere(line);
	// else if (line[0] == 'p' && line[1] == 'l')
	// 	parse_plane(line);
	// else if (line[0] =='c' && line[1] == 'y')
	// 	parse_cylinder(line);
	else
		parse_error(EXIT_FAILURE, "Map error, cannot parse content");
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

void parsing(t_world *world, int ac, char *filename)
{
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
		parse_line(world, line);
		printf("%s", line);
		if (line == NULL)
			break;
	}
}
