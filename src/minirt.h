#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_scene
{
	
}	t_scene;

///parsing/parsing.c
void parsing(t_scene *scene, int ac, char *filename);

//utils/string_utils.c
int ft_strlen(char *s);
int	ft_strcmp(char *s1, char *s2);

#endif