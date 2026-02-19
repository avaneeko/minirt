/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:15:29 by jinzhang          #+#    #+#             */
/*   Updated: 2026/02/19 16:04:10 by jinzhang         ###   ########.fr       */
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

int	count_comma(char *tok)
{
	int	comma_count;
	int	i;

	i = 0;
	comma_count = 0;
	while (tok[i])
	{
		if (tok[i] == ',')
		{
			comma_count++;
		}
		i++;
	}
	if (comma_count != 2)
		return (1);
	return (0);
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
		return (NULL);
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
