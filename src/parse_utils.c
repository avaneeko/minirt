/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:35:26 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:10:16 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "parsing.h"
#include "v3.h"
#include <stdlib.h>
#include "utils.h"

void	world_init(t_world *world)
{
	mset(world, 0, sizeof(*world));
	world->ambient.is_set = 0;
	world->cam.is_set = 0;
	world->light.is_set = 0;
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

int	check_unit_vector(t_v3 v)
{
	double	mag;

	if (v.x < -1.0 || v.x > 1.0 || v.y < -1.0 || v.y > 1.0 || v.z < -1.0
		|| v.z > 1.0)
		return (1);
	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (mag <= 0.999 || mag >= 1.001)
		return (1);
	return (0);
}

int count_comma(char *tok)
{
	int comma_count;
	int i;

	i = 0;
	comma_count = 0;
	while(tok[i])
	{
    	if (tok[i] == ',')
        	comma_count++;
		i++;
	}
	if (comma_count != 2)
    	return (1);
	return (0);
}
int	parse_vec3(char *tok, t_v3 *vec_out)
{
	t_v3	vec;
	int		tok_count;
	char	**vec_arr;

	tok_count = 0;
	vec_arr = NULL;
	if (count_comma(tok))
		return(1);
	vec_arr = ft_split(tok, ',');
	if (!vec_arr || !vec_arr[0])
		return (free_split(vec_arr));
	while (vec_arr[tok_count])
		tok_count++;
	if (tok_count != 3)
		return (free_split(vec_arr));
	if (parse_number(vec_arr[0], &vec.x) || parse_number(vec_arr[1], &vec.y)
		|| parse_number(vec_arr[2], &vec.z))
		return (free_split(vec_arr));
	*vec_out = vec;
	free_split(vec_arr);
	return (0);
}

static int	fill_color(t_v3 *color, char **color_arr, t_v3 *vec_out)
{
	if (parse_number(color_arr[0], &color->x) || parse_number(color_arr[1],
			&color->y) || parse_number(color_arr[2], &color->z))
		return (free_split(color_arr));
	if (color->x > 255.0 || color->x < 0.0 || color->y > 255.0 || color->y < 0.0
		|| color->z > 255.0 || color->z < 0.0)
		return (free_split(color_arr));
	color->x = color->x / 255.0f;
	color->y = color->y / 255.0f;
	color->z = color->z / 255.0f;
	*vec_out = *color;
	return (0);
}

int	parse_color(char *tok, t_v3 *vec_out)
{
	int		tok_count;
	t_v3	color;
	char	**color_arr;

	tok_count = 0;
	color_arr = NULL;
	if (count_comma(tok))
		return(1);
	color_arr = ft_split(tok, ',');
	if (!color_arr || !color_arr[0])
		return (free_split(color_arr));
	while (color_arr[tok_count])
	{
		if (ft_strchr(color_arr[tok_count], '.'))
			return (free_split(color_arr));
		tok_count++;
	}
	if (tok_count != 3)
		return (free_split(color_arr));
	if (fill_color(&color, color_arr, vec_out))
		return (1);
	free_split(color_arr);
	return (0);
}
