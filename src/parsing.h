/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:10:45 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/18 18:11:07 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "world_def.h"
# include <stddef.h>

typedef struct s_ptrim
{
	int		i;
	int		j;
	int		spaces;
	char	*old_line;
	char	*line;
}			t_ptrim;

// parsing.c
void		parsing(t_world *world, int ac, char const *filename);

// parse_ambient.c
int			parse_ambient(t_world *world, char const *line);

// parse_camera.c
int			parse_camera(t_world *world, char const *line);

// parse_light.c
int			parse_light(t_world *world, char const *line);

// parse_sphere.c
int			parse_sphere(t_world *world, char const *line);

// parse_plane.c
int			parse_plane(t_world *world, char const *line);

// parse_cylinder.c
int			parse_cylinder(t_world *world, char const *line);

// ft_split.c
char		**ft_split(char const *s, char c);

// number_utils.c
int			parse_number(char const *str, float *out);

// parse_error.c
int			parse_error(char *s, char **toks);
void		parse_clean_exit(char *msg, t_world *world, int fd, char *line);
void		free_world(t_world *world);
void		cleanup_memories(t_world *world, int fd, char *line);

// parse_utils.c
void		world_init(t_world *world);
int			check_unit_vector(t_v3 v);
int			parse_color(char *tok, t_v3 *vec_out);
int			parse_vec3(char *tok, t_v3 *vec_out);

// parse_str_utils.c
int			ft_isspace(char c);
int			ft_strcmp(char const *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char const *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// parse_str_utils2.c
char		*trim_line(char *old_line);
void		copy_line(t_ptrim *t);
int			free_split(char **arr);
int			ft_strlen(const char *s);
void		*ft_bzero(void *s, size_t n);

#endif
