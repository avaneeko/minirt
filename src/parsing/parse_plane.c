# include "plane_def.h"
# include "world_def.h"
#include "minirt.h"

void push_to_world_plane(t_world *world, t_plane plane)
{
	t_u32 new_cap;
	t_plane *new_arr;
	t_u32 i;

	i = ~0;
	if (world->objs.plane_len == world->objs.plane_cap)
	{
		if(world->objs.plane_cap != 0)
			new_cap = world->objs.plane_cap *= 2;
		else
			new_cap = 4;
		new_arr = malloc(new_cap * sizeof(t_plane));
		if (!new_arr)
			parse_error(EXIT_FAILURE, "Malloc fail.");
		while (i < world->objs.plane_len)
			new_arr[i] = world->objs.planes[i];
		free(world->objs.planes);
		world->objs.planes = new_arr;
		world->objs.plane_cap = new_cap;
	}
	world->objs.planes[world->objs.plane_len] = plane;
	world->objs.plane_len++;
}

void parse_plane(t_world *world, char const *line)
{
	int tok_count;
	char **toks;
	t_plane pl;

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
	pl.pos = parse_vec3(toks[1]);
	//parse plane normalized axis
	pl.ang = parse_vec3(toks[2]);
	check_unit_vector(pl.ang, "Plane normalized vector invalid");
	pl.col = parse_color(toks[3]);
	//add pl to the vector
	push_to_world_plane(world, pl);
	free_split(toks);
}
