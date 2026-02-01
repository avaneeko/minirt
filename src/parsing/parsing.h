#ifndef PARSING_H
# define PARSING_H

#include <stdbool.h>
#include <stddef.h>
# include "world_def.h"
//# include "v3.h"
typedef struct s_ptrim
{
	int   i;
	int   j;
	int   spaces;
	char *old_line;
	char *line;
} t_ptrim;

//parsing/parsing.c
void parsing(t_world *world, int ac, char const*filename);

//parsing/parse_ambient.c
void parse_ambient(t_world *world, char const*line);

//parsing/parse_camera.c
void parse_camera(t_world *world, char const*line);

//parsing/parse_light.c
void parse_light(t_world *world, char const*line);

//parsing/parse_object.c
void parse_sphere(t_world *world, char const*line);
void parse_plane(t_world *world, char const*line);
void parse_cylinder(t_world *world, char const*line);
void push_to_world_sphere(t_world *world, t_sphere sphere);
//utils/parse_error.c
void parse_error(int code, char *s);

//utils/ft_split.c
char	**ft_split(char const *s, char c);

//utils/number_utils.c
double	parse_number(char const*str);

//parsing/parse_utils.c
void world_init(t_world *world);
void check_unit_vector(t_v3 v, char *err_msg);
t_v3 parse_color(char *tok);
t_v3 parse_vec3(char *tok);
void	free_split(char **arr);

//utils/string_utils.c
int	ft_isspace(char c);
int ft_strlen(const char *s);
int	ft_strcmp(char const*s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char const *s1);

#endif