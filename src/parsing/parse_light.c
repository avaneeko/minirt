#include "minirt.h"

void parse_light(t_world *world, char *line)
{
	int i;
	int tok_count;
	char **toks;
	char **lpoint;

	i = 0;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Light needs 3 tokens");
	// parse light point
	lpoint = ft_split(toks[1], ','); //MALLOC
	if (!lpoint || !lpoint[0])
		parse_error(EXIT_FAILURE, "Viewpoint format 50.0,0,20");
	world->L.lpoint.x = parse_number(lpoint[0]);
	world->L.lpoint.y = parse_number(lpoint[1]);
	world->L.lpoint.z = parse_number(lpoint[2]);
	// parse brightness
	world->L.brightness = parse_number(toks[2]);
	if (world->L.brightness > 1.0 || world->L.brightness < 0.0)
		parse_error(EXIT_FAILURE, "Brightness ratio range 0.0 - 1.0");
	printf("x:%f y:%f z:%f b:%f\n", world->L.lpoint.x, world->L.lpoint.y, world->L.lpoint.z, world->L.brightness);
}
