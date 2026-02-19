/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: losypenk <losypenk@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:15:29 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 12:10:21 by losypenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (1);
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (1);
}

void	copy_line(t_ptrim *t)
{
	if (ft_isspace(t->old_line[t->i]))
	{
		(t->spaces)++;
		(t->i)++;
		if (t->spaces == 1)
		{
			t->line[t->j] = ' ';
			(t->j)++;
		}
	}
	else
	{
		t->spaces = 0;
		t->line[t->j] = t->old_line[t->i];
		(t->j)++;
		(t->i)++;
	}
}

char	*trim_line(char *old_line)
{
	t_ptrim	t;
	char	*line;

	if (!old_line)
		return (NULL);
	line = malloc(ft_strlen(old_line) + 1);
	if (!line)
	{
		free(old_line);
		return (NULL);
	}
	t.old_line = old_line;
	t.line = line;
	t.i = 0;
	t.j = 0;
	t.spaces = 0;
	while (ft_isspace(old_line[t.i]))
		t.i++;
	while (old_line[t.i] != '\0')
		copy_line(&t);
	if (t.j > 0 && t.line[t.j - 1] == ' ')
		t.j--;
	line[t.j] = '\0';
	return (line);
}
