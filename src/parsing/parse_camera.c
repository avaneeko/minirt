#include "minirt.h"

/*
Camera defines where we look from and how we look at the scene.
It represents the viewer’s eye.

Token	          Meaning	                        Validation / Notes
C	              camera identifier	            	must be unique (only one camera allowed)

-50.0,0,20	      Camera position (moving your body)	    x,y,z coordinates in 3D space
													type: double
													any real number allowed
	                                            	example: -50.0 moves camera left on X axis

0,0,1	          Camera orientation vector(turning your head)	    	direction the camera is facing
	                                            	type: normalized vector (double)
	                                            	each component in range [-1.0, 1.0]
	                                            	vector length must be 1 (normalized)
	                                            	example:
	                                              	0,0,1  → camera looks forward (positive Z)
	                                              	0,1,0  → camera looks upward
	                                              	1,0,0  → camera looks right

70	              FOV (view angle)	            horizontal field of view in degrees
	                                            	type: int or double
	                                            	range: 0 < value ≤ 180
	                                            	small value → zoomed in (telephoto)
	                                            	large value → wide angle (fisheye-like)
*/


void parse_camera(t_world *world, char const*line)
{
	int tok_count;
	char **toks;

	if (world->cam.is_set == true)
		parse_error(EXIT_FAILURE, "Only one camera set allowed");
	tok_count = 0;
	toks = NULL;
	toks = ft_split(line, ' ');
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		parse_error(EXIT_FAILURE, "Camera position needs 4 tokens");
	// parse view point
	world->cam.pos = parse_vec3(toks[1]);
	//parse orientation vector, can it be all 0?
	world->cam.fwd = parse_vec3(toks[2]);
	check_unit_vector(world->cam.fwd);
	//parse fov
	world->cam.fov = parse_number(toks[3]);
	if (world->cam.fov < 0 || world->cam.fov > 180)
		parse_error(EXIT_FAILURE, "Field of view range 0 - 180");
	world->cam.is_set = true;
	free_split(toks);
}
