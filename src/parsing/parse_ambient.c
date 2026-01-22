#include "minirt.h"

/*
Ambient light is global. It does not have: position, direction.
Token	      Meaning	            Validation
A	          ambient identifier	must be unique
0.2	          ambient ratio	        0.0 ≤ value ≤ 1.0 {0.0 no ambient light. 1.0 very strong ambient light. 0.2 soft, realistic background light}
255,255,255	  RGB color	each        0–255  {255,255,255 = white light  255,0,0 = red ambient light   0,0,255 = blue ambient light}
*/
void parse_ambient(t_world *world, char *line)
{
	int i;
	int tok_count;
	char **toks;
	char **color;

	i = 0;
	tok_count = 0;
	toks = ft_split(line, ' '); //MALLOC
	if (!toks || !toks[0])
		parse_error(EXIT_FAILURE, "Line should start with specifier");
	while (toks[tok_count])
		tok_count++;
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Ambient light needs 3 tokens");
	world->A.ratio = parse_number(toks[1]);
	if (world->A.ratio > 1.0 || world->A.ratio < 0.0)
		parse_error(EXIT_FAILURE, "Ratio must be 0.0 - 1.0");
	color = ft_split(toks[2], ','); //MALLOC
	if (!color)
		parse_error(EXIT_FAILURE, "Color format 255,255,255");
	tok_count = 0;
	while (color[tok_count])
	{
		if (ft_strchr(color[tok_count], '.'))
			parse_error(EXIT_FAILURE, "Color format 255,255,255");
		tok_count++;
	}
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Color format 255,255,255");
	world->A.a_color.r = parse_number(color[0]);
	world->A.a_color.g = parse_number(color[1]);
	world->A.a_color.b = parse_number(color[2]);
	if (world->A.a_color.r > 255.0 || world->A.a_color.r < 0.0 || world->A.a_color.g > 255.0 || world->A.a_color.g < 0.0 || world->A.a_color.b > 255.0 || world->A.a_color.g < 0.0)
		parse_error(EXIT_FAILURE, "Color range 0 - 255");
}
