/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinzhang <jinzhang@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 20:18:29 by jinzhang          #+#    #+#             */
/*   Updated: 2025/06/01 15:23:05 by jinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	t_gnl		gnl;
	static char	buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl.line = malloc(1);
	if (!gnl.line)
		return (NULL);
	gnl.line[0] = '\0';
	gnl.nl = gnl_updatebuf(buf);
	while (1)
	{
		if (gnl.nl == -1)
		{
			gnl.bytes_read = read(fd, buf, BUFFER_SIZE);
			if (gnl.bytes_read <= 0)
				return (gnl_error_eof(&gnl, buf));
			buf[gnl.bytes_read] = '\0';
		}
		gnl.nl = gnl_find_nl(buf, '\n');
		gnl.line = gnl_strjoin(gnl.line, buf, gnl.nl);
		if (gnl.nl != -1 || gnl.line == NULL)
			break ;
	}
	return (gnl.line);
}
