# include "cylinder_def.h"
# include "world_def.h"
# include "minirt.h"

void push_to_world_cylinder(t_world *world, t_cylinder cylinder)
{
	t_u32 new_cap;
	t_cylinder *new_arr;
	t_u32 i;

	i = ~0;
	if (world->objs.cylinder_len == world->objs.cylinder_cap)
	{
		if(world->objs.cylinder_cap != 0)
			new_cap = world->objs.cylinder_cap *= 2;
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_cylinder));
		if (!new_arr)
			parse_error(EXIT_FAILURE, "Malloc fail.");
		while (++i < world->objs.cylinder_len)
			new_arr[i] = world->objs.cylinders[i];
		free(world->objs.cylinders);
		world->objs.cylinders = new_arr;
		world->objs.cylinder_cap = new_cap;
	}
	world->objs.cylinders[world->objs.cylinder_len] = cylinder;
	world->objs.cylinder_len++;
}

void parse_cylinder(t_world *world, char const*line)
{
	int tok_count;
	char **toks;
	t_cylinder cy;

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
	cy.pos = parse_vec3(toks[1]);
	//parse cy normalized axis
	cy.ang = parse_vec3(toks[2]);
	check_unit_vector(cy.ang, "Cylinder normalized axis invalid");
	//parse cy diameter snf height
	cy.r = parse_number(toks[3]);
	cy.h = parse_number(toks[4]);
	if(cy.r <= 0 || cy.h <=0)
		parse_error(EXIT_FAILURE, "Cylinder diameter and height should be > 0");
	//parse cy color
	cy.col = parse_color(toks[5]);
	push_to_world_cylinder(world, cy);
	free_split(toks);
}

