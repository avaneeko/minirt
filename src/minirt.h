#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_color
{
	float r;
	float g;
	float b;
}	t_color;

typedef struct s_ambient
{
	float ratio;
	t_color color;
}	t_ambient;


typedef struct s_world
{
	t_ambient A;
}	t_world;


//parsing/parsing.c
void parsing(t_world *world, int ac, char *filename);

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

#endif