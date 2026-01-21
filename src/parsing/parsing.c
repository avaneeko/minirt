#include "minirt.h"

// check .rt extension
// open file
// ambient lighting
// camera
// light
// sphere or plane cylinder

#include <stdio.h>


void parse_error(int code, char *s)
{
	printf("%s\n", s);
	exit(code);
}
/*
Camera defines where we look from and how we look at the scene.
It represents the viewer’s eye.

Token	          Meaning	                        Validation / Notes
C	              camera identifier	            	must be unique (only one camera allowed)

-50.0,0,20	      Camera position (viewpoint)	    x,y,z coordinates in 3D space
													type: double
													any real number allowed
	                                            	example: -50.0 moves camera left on X axis

0,0,1	          Camera orientation vector	    	direction the camera is facing
	                                            	type: normalized vector (double)
	                                            	each component in range [-1.0, 1.0]
	                                            	vector length must be 1 (normalized)
	                                            	example:
	                                              	0,0,1  → camera looks forward (positive Z)
	                                              	0,1,0  → camera looks upward
	                                              	1,0,0  → camera looks right

70	              FOV (Field of View)	            horizontal field of view in degrees
	                                            	type: int or double
	                                            	range: 0 < value ≤ 180
	                                            	small value → zoomed in (telephoto)
	                                            	large value → wide angle (fisheye-like)
*/


void parse_line(t_world *world, char *line)
{
	if (!line)
		return ; //FIX ME
	if (line[0] == 'A')
		parse_ambient(world, line);
	 else if (line[0] == 'C')
	 	parse_camera(line);
	// else if (line[0] == 'L')
	// 	parse_light(line);
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
		//printf("%s", line);
		if (line == NULL)
			break;
	}
}
