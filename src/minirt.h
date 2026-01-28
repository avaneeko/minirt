#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_color
{
	float r;
	float g;
	float b;
}	t_color;

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_light
{
	bool   is_set;
	t_vec3 lpoint;
	t_color lcolor;
	float  brightness;
}	t_light;

typedef struct s_camera
{
	bool    is_set;
	t_vec3	vpoint;
	t_vec3 	orien;
	float	fov;
}	t_camera;

typedef struct s_ambient
{
	bool  is_set;
	float ratio;
	t_color a_color;
}	t_ambient;

typedef struct s_sphere
{
	t_vec3 sp_center;
	float  sp_diamtr;
	t_color sp_color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3 point;
	t_vec3 normal;
	t_color pl_color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3 cy_center;
	t_vec3 cy_normal;
	float  cy_diamtr;
	float cy_height;
	t_color cy_color;
}	t_cylinder;

typedef struct  s_objs
{
	t_sphere *sp;
	uint32_t		sphere_len;
	uint32_t		sphere_cap;
	t_plane  *pl;
	uint32_t		pl_len;
	uint32_t		pl_cap;
	t_cylinder *cy;
	uint32_t		cy_len;
	uint32_t		cy_cap;
}	t_objs;

typedef struct s_world
{
	t_ambient A;
	t_camera  C;
	t_light	  L;
	t_objs  objs;
}	t_world;


//parsing/parsing.c
void parsing(t_world *world, int ac, char *filename);

//parsing/parse_ambient.c
void parse_ambient(t_world *world, char *line);

//parsing/parse_camera.c
void parse_camera(t_world *world, char *line);

//parsing/parse_light.c
void parse_light(t_world *world, char *line);

//parsing/parse_object.c
void parse_sphere(t_world *world, char *line);
void parse_plane(t_world *world, char *line);
void parse_cylinder(t_world *world, char *line);

//utils/parse_error.c
void parse_error(int code, char *s);

//utils/ft_split.c
char	**ft_split(char const *s, char c);

//utils/number_utils.c
double	parse_number(const char *str);


//parsing/parse_utils.c
void world_init(t_world *world);
t_color parse_color(char *tok);
t_vec3 parse_vec3(char *tok);
void	free_split(char **arr);

//utils/string_utils.c
int	ft_isspace(char c);
int ft_strlen(const char *s);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);


#endif