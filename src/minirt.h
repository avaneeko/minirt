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
	t_vec3 lpoint;
	t_color lcolor;
	float  brightness;
}	t_light;

typedef struct s_camera
{
	t_vec3	vpoint;
	t_vec3 	orien;
	float	fov;
}	t_camera;

typedef struct s_ambient
{
	float ratio;
	t_color a_color;
}	t_ambient;

typedef struct s_world
{
	t_ambient A;
	t_camera  C;
	t_light	  L;
}	t_world;


//parsing/parsing.c
void parsing(t_world *world, int ac, char *filename);

//parsing/parse_ambient.c
void parse_ambient(t_world *world, char *line);

//parsing/parse_camera.c
void parse_camera(t_world *world, char *line);

//parsing/parse_light.c
void parse_light(t_world *world, char *line);

//utils/string_utils.c
int	ft_isspace(char c);
int ft_strlen(const char *s);
int	ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);

//utils/ft_split.c
char	**ft_split(char const *s, char c);

//utils/number_utils.c
double	parse_number(const char *str);

//utils/parse_error.c
void parse_error(int code, char *s);

#endif