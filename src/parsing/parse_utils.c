#include "minirt.h"
void world_init(t_world *world)
{
	world->A.is_set = false;
	world->C.is_set = false;
	world->L.is_set = false;
	world->objs.sp = NULL;
	world->objs.sphere_len = 0;
	world->objs.sphere_cap = 0;
	world->objs.pl = NULL;
	world->objs.pl_len = 0;
	world->objs.pl_cap = 0;
	world->objs.cy = NULL;
	world->objs.cy_len = 0;
	world->objs.cy_cap = 0;
}
void free_split(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

t_vec3 parse_vec3(char *tok)
{	
	t_vec3 vec;
	int tok_count;
	char **vec_arr;

	vec_arr = ft_split(tok, ','); //MALLOC
	if (!vec_arr || !vec_arr[0])
		parse_error(EXIT_FAILURE, "Vectors nonexistant");
	tok_count = 0;
	while (vec_arr[tok_count])
		tok_count++;
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Vector token amount wrong");
	vec.x = parse_number(vec_arr[0]);
	vec.y = parse_number(vec_arr[1]);
	vec.z = parse_number(vec_arr[2]);
	free_split(vec_arr);
	return (vec);
}
t_color parse_color(char *tok)
{
	int tok_count;
	t_color color;
	char **color_arr;

	color_arr = ft_split(tok, ','); //MALLOC
	if (!color_arr || !color_arr[0])
		parse_error(EXIT_FAILURE, "Color format 255,255,255");
	tok_count = 0;
	while (color_arr[tok_count])
	{
		if (ft_strchr(color_arr[tok_count], '.'))
			parse_error(EXIT_FAILURE, "Color format 255,255,255");
		tok_count++;
	}
	if (tok_count != 3)
		parse_error(EXIT_FAILURE, "Color format 255,255,255");
	color.r = parse_number(color_arr[0]);
	color.g = parse_number(color_arr[1]);
	color.b = parse_number(color_arr[2]);
	if (color.r > 255.0 || color.r < 0.0 || color.g > 255.0 || color.g < 0.0 || color.b > 255.0 || color.b < 0.0)
		parse_error(EXIT_FAILURE, "Color range 0 - 255");
	free_split(color_arr);
	return(color);
}
