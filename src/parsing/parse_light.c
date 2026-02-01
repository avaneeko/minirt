#include "minirt.h"

void parse_light(t_world *world, char const*line)
{
	int tok_count;
	char **toks;

	if (world->light.is_set == true)
		parse_error(EXIT_FAILURE, "Only one light set allowed");
	toks = NULL;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 3 && tok_count != 4)
		parse_error(EXIT_FAILURE, "Light needs at least 3 tokens");
		// parse light point
	world->light.point = parse_vec3(toks[1]);
	// parse brightness
	world->light.brightness = parse_number(toks[2]);
	if (world->light.brightness > 1.0 || world->light.brightness < 0.0)
		parse_error(EXIT_FAILURE, "Brightness ratio range 0.0 - 1.0");
	//optional color
	if (tok_count == 4)
		world->light.color = parse_color(toks[3]);
	world->light.is_set = true;
	free_split(toks);
}
