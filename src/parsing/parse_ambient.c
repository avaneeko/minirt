#include "minirt.h"
#include "world_def.h"
#include "amb.h"
/*
Ambient light is global. It does not have: position, direction.
Token	      Meaning	            Validation
A	          ambient identifier	must be unique
0.2	          ambient ratio	        0.0 ≤ value ≤ 1.0 {0.0 no ambient light. 1.0 very strong ambient light. 0.2 soft, realistic background light}
255,255,255	  RGB color	each        0–255  {255,255,255 = white light  255,0,0 = red ambient light   0,0,255 = blue ambient light}
*/
void parse_ambient(t_world *world, char const*line)
{
	int tok_count;
	char **toks;

	if (world->amb.is_set == true)
		parse_error(EXIT_FAILURE, "Only one ambient set allowed");
	tok_count = 0;
	toks = NULL;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Ambient light needs 3 tokens");
	world->amb.ratio = parse_number(toks[1]);
	if (world->amb.ratio > 1.0 || world->amb.ratio < 0.0)
		parse_error(EXIT_FAILURE, "Ratio must be 0.0 - 1.0");
	world->amb.color = parse_color(toks[2]);
	world->amb.is_set = true;
	free_split(toks);
}
