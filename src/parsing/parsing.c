#include "minirt.h"

// check .rt extension
// open file
// ambient lighting
// camera
// light
// sphere or plane cylinder
// char *skip_spaces(char *line)
// {
// 	int	i;
// 	char new_line;

// 	new_line = malloc(sizeof(line))
// 	i = 0;
// 	while (line[i])
// 	{

// 	}
// }
void parse_line(t_world *world, char *line)
{

	if (!line) //skip extra spaces and empty lines or \n
		return ; //FIX ME
	if (line[0] == 'A')
		parse_ambient(world, line);
	else if (line[0] == 'C')
	 	parse_camera(world, line);
	else if (line[0] == 'L')
	 	parse_light(world, line);
	else if (line[0] == 's' && line[1] == 'p')
	 	parse_sphere(world, line);
	else if (line[0] == 'p' && line[1] == 'l')
	 	parse_plane(world,line);
	else if (line[0] =='c' && line[1] == 'y')
	 	parse_cylinder(world, line);
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

void copy_line(t_trim *t)
{
	if (ft_isspace(t->old_line[t->i]))
	{
		(t->spaces)++;
		(t->i)++;
		if (t->spaces == 1)
		{
			t->line[t->j] = ' ';
			(t->j)++;
		}
	}
	else
	{
		t->spaces = 0;
		t->line[t->j] = t->old_line[t->i];
		(t->j)++;
		(t->i)++;
	}
}

char *trim_line(char *old_line)
{
	t_trim	t;
	char	*line;

	if (!old_line)
		return (NULL);

	line = malloc(ft_strlen(old_line) + 1);
	if (!line)
		parse_error(EXIT_FAILURE, "malloc fail");

	t.old_line = old_line;
	t.line = line;
	t.i = 0;
	t.j = 0;
	t.spaces = 0;
	while (ft_isspace(old_line[t.i]))
		t.i++;
	while (old_line[t.i] != '\0')
		copy_line(&t);
	if (t.j > 0 && t.line[t.j - 1] == ' ')
		t.j--;
	line[t.j] = '\0';
	free(old_line);
	return (line);
}

void parsing(t_world *world, int ac, char *filename)
{
	char *old_line;
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
		old_line = get_next_line(fd);
		if (old_line == NULL)
			break;
		line = trim_line(old_line);
		parse_line(world, line);
		free(line);
	}
	close (fd);
}
