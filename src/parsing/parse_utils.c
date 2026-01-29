#include "minirt.h"

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

void pworld_init(t_pworld *pworld)
{
	ft_bzero(pworld, sizeof(*pworld));
	pworld->A.is_set = false;
	pworld->C.is_set = false;
	pworld->L.is_set = false;
	pworld->objs.sp = NULL;
	pworld->objs.sphere_len = 0;
	pworld->objs.sphere_cap = 0;

	pworld->objs.pl = NULL;
	pworld->objs.pl_len = 0;
	pworld->objs.pl_cap = 0;

	pworld->objs.cy = NULL;
	pworld->objs.cy_len = 0;
	pworld->objs.cy_cap = 0;
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

void check_unit_vector(t_pvec3 v, char *err_msg)
{
	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0 || v.z < -1.0 || v.z > 1.0)
		parse_error(EXIT_FAILURE, err_msg);
	if (v.x == 0.0 && v.y == 0.0 && v.z == 0.0)
		parse_error(EXIT_FAILURE, err_msg);
}
t_pvec3 parse_vec3(char *tok)
{
	t_pvec3 vec;
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
t_pcolor parse_color(char *tok)
{
	int tok_count;
	t_pcolor color;
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
