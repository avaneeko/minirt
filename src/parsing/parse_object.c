#include "minirt.h"
//You now create a local object, then APPEND it into world->objs (the array)
void parse_cylinder(t_world *world, char *line)
{
	int tok_count;
	char **toks;
	t_cylinder cy;
	(void)world;
	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 5)
		parse_error(EXIT_FAILURE, "cylinder needs 5 tokens");
	// parse cy center coordinates
	cy.cy_center = parse_vec3(toks[1]);
	//parse cy normalized axis 
	cy.cy_normal = parse_vec3(toks[2]);
	if (cy.cy_normal.x > 1.0 || cy.cy_normal.x < -1.0 || cy.cy_normal.y > 1.0 || cy.cy_normal.y < -1.0 || cy.cy_normal.z > 1.0 || cy.cy_normal.z < -1.0 )
		parse_error(EXIT_FAILURE, "Cy normalized vector format 0.0,0.0,-1.0");
	//parse cy diameter snf height
	cy.cy_diamtr = parse_number(toks[3]);
	cy.cy_height = parse_number(toks[4]);
	if(cy.cy_diamtr <= 0 || cy.cy_height <=0)
		parse_error(EXIT_FAILURE, "Sphere diameter and height should be > 0");
	//parse cy color
	cy.cy_color = parse_color(toks[5]);
	//add the cy to vector here
	free_split(toks);
}

void parse_plane(t_world *world, char *line)
{
	int tok_count;
	char **toks;
	t_plane pl;
	(void)world;
	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		parse_error(EXIT_FAILURE, "Plane needs 4 tokens");
	// parse plane point
	pl.point = parse_vec3(toks[1]);
	//parse plane normalized axis
	pl.normal = parse_vec3(toks[2]);
	if (pl.normal.x > 1.0 || pl.normal.x < -1.0 || pl.normal.y > 1.0 || pl.normal.y < -1.0 || pl.normal.z > 1.0 || pl.normal.z < -1.0 )
		parse_error(EXIT_FAILURE, "Plane normalized vector format 0.0,0.0,-1.0");
	pl.pl_color = parse_color(toks[3]);
	//add pl to the vector
	free_split(toks);
}

void parse_sphere(t_world *world, char *line)
{
	int tok_count;
	char **toks;
	t_sphere sp;
	(void)world;
	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 4)
		parse_error(EXIT_FAILURE, "Sphere needs 4 tokens");
	// parse sp center coordinates, anything to consider here?
	sp.sp_center = parse_vec3(toks[1]);
	//parse sphere diameter
	sp.sp_diamtr = parse_number(toks[2]);
	if(sp.sp_diamtr <= 0)
		parse_error(EXIT_FAILURE, "Sphere diameter should be > 0");
	//parse sphere color
	sp.sp_color = parse_color(toks[3]);
	//add the sp to vector here
	free_split(toks);
	printf("x:%f y:%f z:%f dia:%f r:%f g:%f b:%f", sp.sp_center.x, sp.sp_center.y, sp.sp_center.z, sp.sp_diamtr, sp.sp_color.r,sp.sp_color.g,sp.sp_color.b);
}
