#include "minirt.h"
# include "v3.h"
# include "math.h"
void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
	return (s);
}

void world_init(t_world *world)
{
	ft_bzero(world, sizeof(*world));
	world->amb.is_set = false;
	world->cam.is_set = false;
	world->light.is_set = false;
	world->objs.spheres = NULL;
	world->objs.sphere_len = 0;
	world->objs.sphere_cap = 0;

	world->objs.planes = NULL;
	world->objs.plane_len = 0;
	world->objs.plane_cap = 0;

	world->objs.cylinders = NULL;
	world->objs.cylinder_len = 0;
	world->objs.cylinder_cap = 0;
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

void check_unit_vector(t_v3 v)
{
	double mag;
	//check if it is valid direction
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0 || v.z < -1.0 || v.z > 1.0)
		parse_error(EXIT_FAILURE, "Not valid vector direction");
	//vector cannot be 0
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		parse_error(EXIT_FAILURE, "Vector cannot be 0");
	//need to also check the formula thing is here
	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (mag <= 0.999 || mag >= 1.001)
		parse_error(EXIT_FAILURE, "Not unit vector");
}

t_v3 parse_vec3(char *tok)
{
	t_v3 vec;
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
t_v3 parse_color(char *tok)
{
	int tok_count;
	t_v3 color;
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
	color.x = parse_number(color_arr[0]) / 255.0;
	color.y = parse_number(color_arr[1]) / 255.0;
	color.z = parse_number(color_arr[2]) / 255.0;
	if (color.x > 1.0 || color.x < 0.0 || color.y > 1.0 || color.y < 0.0 || color.z > 1.0 || color.z < 0.0)
		parse_error(EXIT_FAILURE, "Color range 0 - 255");
	free_split(color_arr);
	return(color);
}
