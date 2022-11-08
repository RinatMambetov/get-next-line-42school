/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greita <greita@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 15:29:41 by greita            #+#    #+#             */
/*   Updated: 2021/12/15 15:23:50 by greita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	split_lines(char *ptr_n, char **line, char **lines)
{
	char	*temp;

	*ptr_n = '\0';
	*line = ft_strjoin(*lines, "\n");
	temp = ft_strdup(ptr_n + 1);
	free(*lines);
	*lines = temp;
}

char	*get_line(char **lines)
{
	char	*temp;
	char	*line;
	char	*ptr_n;

	ptr_n = ft_strchr(*lines, '\n');
	if (!ptr_n && **lines)
	{
		temp = *lines;
		*lines = NULL;
		return (temp);
	}
	else if (!**lines)
	{
		free(*lines);
		return (*lines = NULL);
	}
	split_lines(ptr_n, &line, lines);
	if (!line)
		return (NULL);
	if (!*lines)
	{
		free(line);
		return (line = NULL);
	}
	return (line);
}

int	read_buf(int fd, ssize_t *bytes, char **lines)
{
	char	*temp;
	char	buf[BUFFER_SIZE + 1];

	*bytes = read(fd, buf, BUFFER_SIZE);
	if (*bytes <= 0)
		return (0);
	buf[*bytes] = '\0';
	temp = ft_strjoin(*lines, buf);
	free(*lines);
	*lines = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char		*lines[FD_MAX] = {NULL};
	ssize_t			bytes;

	if (fd < 0)
		return (NULL);
	bytes = 0;
	if (!lines[fd])
	{
		lines[fd] = malloc(sizeof(*lines));
		if (!lines[fd])
			return (NULL);
		*lines[fd] = '\0';
	}
	while (!ft_strchr(lines[fd], '\n') && read_buf(fd, &bytes, &lines[fd]))
		if (!lines[fd])
			return (NULL);
	if (bytes < 0)
	{
		free(lines[fd]);
		return (lines[fd] = NULL);
	}
	return (get_line(&lines[fd]));
}
