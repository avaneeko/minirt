#include "minirt.h"
//create a local object, then APPEND it into world->objs (the array)
void parse_cylinder(char *line)
{
	int tok_count;
	char **toks;
	t_pcylinder cy;

	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 6)
		parse_error(EXIT_FAILURE, "cylinder input invalid");
	// parse cy center coordinates
	cy.cy_center = parse_vec3(toks[1]);
	//parse cy normalized axis
	cy.cy_normal = parse_vec3(toks[2]);
	check_unit_vector(cy.cy_normal, "Cylinder normalized axis invalid");
	//parse cy diameter snf height
	cy.cy_diamtr = parse_number(toks[3]);
	cy.cy_height = parse_number(toks[4]);
	if(cy.cy_diamtr <= 0 || cy.cy_height <=0)
		parse_error(EXIT_FAILURE, "Cylinder diameter and height should be > 0");
	//parse cy color
	cy.cy_color = parse_color(toks[5]);
	//add the cy to vector here
	free_split(toks);
}

void parse_plane(char *line)
{
	int tok_count;
	char **toks;
	t_pplane pl;

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
	check_unit_vector(pl.normal, "Plane normalized vector invalid");
	pl.pl_color = parse_color(toks[3]);
	//add pl to the vector
	free_split(toks);
}

void push_to_world_sphere(t_world *pworld)
{
	t_u32 new_cap;
	char *new_arr;

	if (world->objs.sphere_len == world->objs.sphere_cap)
	{
		if(world->objs.sphere_cap != 0)
			new_cap = world->objs.sphere_cap *= 2;
		else
			new_cap = 4;
		new_arr = malloc(new_cap * size_of(t_psphere))
	}

}
void parse_sphere(char const*line, t_world *world)
{
	int tok_count;
	char **toks;
	t_psphere sp;

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
	push_to_world_sphere(world);
	free_split(toks);
}
