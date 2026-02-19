/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:01:19 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 16:01:20 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ERROR_H
# define PARSE_ERROR_H

# include "world_def.h"
# include <stddef.h>

int		parse_error(char *s, char **toks);
void	parse_clean_exit(char *msg, t_world *world, int fd, char *line);
void	free_world(t_world *world);
void	cleanup_memories(t_world *world, int fd, char *line);

#endif
