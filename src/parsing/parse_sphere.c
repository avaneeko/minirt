# include "sphere_def.h"
# include "world_def.h"
# include "minirt.h"
//create a local object, then APPEND it into world->objs (the array)

void push_to_world_sphere(t_world *world, t_sphere sphere)
{
	t_u32 new_cap;
	t_sphere *new_arr;
	t_u32 i;

	i = ~0;
	if (world->objs.sphere_len == world->objs.sphere_cap)
	{
		if(world->objs.sphere_cap != 0)
			new_cap = world->objs.sphere_cap *= 2;
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_sphere));
		if (!new_arr)
			parse_error(EXIT_FAILURE, "Malloc fail.");
		while (++i < world->objs.sphere_len)
			new_arr[i] = world->objs.spheres[i];
		free(world->objs.spheres);
		world->objs.spheres = new_arr;
		world->objs.sphere_cap = new_cap;
	}
	world->objs.spheres[world->objs.sphere_len] = sphere;
	world->objs.sphere_len++;
}

void parse_sphere(t_world *world, char const*line)
{
	int tok_count;
	char **toks;
	t_sphere sp;

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
	sp.pos = parse_vec3(toks[1]);
	//parse sphere diameter
	sp.r = parse_number(toks[2]);
	if(sp.r <= 0)
		parse_error(EXIT_FAILURE, "Sphere diameter should be > 0");
	//parse sphere color
	sp.col = parse_color(toks[3]);
	//add the sp to vector here
	push_to_world_sphere(world, sp);
	free_split(toks);
}
