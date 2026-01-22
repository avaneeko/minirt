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


void parse_camera(t_world *world, char *line)
{
	int i;
	int tok_count;
	char **toks;
	char **vpoint;
	char **orien;

	i = 0;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		parse_error(EXIT_FAILURE, "Camera position needs 4 tokens");
	// parse view point 
	vpoint = ft_split(toks[1], ','); //MALLOC
	if (!vpoint || !vpoint[0])
		parse_error(EXIT_FAILURE, "Viewpoint format 50.0,0,20");
	world->C.vpoint.x = parse_number(vpoint[0]);
	world->C.vpoint.y = parse_number(vpoint[1]);
	world->C.vpoint.z = parse_number(vpoint[2]);
	//parse orientation vector
	orien = ft_split(toks[2], ','); //MALLOC
	if (!orien || !orien[0])
		parse_error(EXIT_FAILURE, "Orientation vector format 0.0,0.0,1.0");
	world->C.orien.x = parse_number(orien[0]);
	world->C.orien.y = parse_number(orien[1]);
	world->C.orien.z = parse_number(orien[2]);
	if (world->C.orien.x > 1.0 || world->C.orien.x < -1.0 || world->C.orien.y > 1.0 || world->C.orien.y < -1.0 || world->C.orien.z > 1.0 || world->C.orien.z < -1.0)
		parse_error(EXIT_FAILURE, "Orientation vector format 0.0,0.0,-1.0");
	//parse fov
	world->C.fov = parse_number(toks[3]);
	if (world->C.fov < 0 || world->C.fov > 180)
		parse_error(EXIT_FAILURE, "Field of view range 0 - 180");
}
