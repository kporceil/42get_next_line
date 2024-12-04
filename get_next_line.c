/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:05:28 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/04 13:05:45 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

t_err	add_leftover(char *leftover, char **line);
t_err	set_line(int fd, char **line);
t_err	set_leftover(char **leftover, char *line);
t_err	resize_line(char **line);

char	*get_next_line(int fd)
{
	t_err		err;
	char		*line;
	static char	*leftover = NULL;

	err = add_leftover(leftover, &line);
	free(leftover);
	leftover = NULL;
	if (err)
		return (NULL);
	err = set_line(fd, &line);
	if (err)
	{
		free(line);
		return (NULL);
	}
	err = set_leftover(&leftover, line);
	if (err)
	{
		free(line);
		return (NULL);
	}
	err = resize_line(&line);
	if (err && leftover)
		free(leftover);
	return (line);
}

t_err	add_leftover(char *leftover, char **line)
{
	size_t	i;
	size_t	len;

	if (!leftover)
	{
		*line = NULL;
		return (NO_ERR);
	}
	len = ft_strlen(leftover);
	*line = malloc(sizeof(char) * (len + 1));
	if (!(*line))
		return (MALLOC_ERR);
	i = 0;
	while (leftover[i])
	{
		(*line)[i] = leftover[i];
		++i;
	}
	(*line)[i] = '\0';
	return (NO_ERR);
}

t_err	set_line(int fd, char **line)
{
	char	*buffer;
	ssize_t	read_size;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (!buffer)
		return (MALLOC_ERR);
	read_size = 0;
	while (is_line_complete(*line) == false)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size < 1)
			break ;
		buffer[read_size] = '\0';
		*line = ft_strjoin(*line, buffer);
		if (!(*line))
		{
			free(buffer);
			return (MALLOC_ERR);
		}
	}
	free(buffer);
	if (read_size < 0)
		return (READ_ERR);
	return (NO_ERR);
}

t_err	set_leftover(char **leftover, char *line)
{
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	while (line && line[len])
		++len;
	i = 0;
	while (i < len && line[i] != '\n')
		++i;
	if (i < len && line[i] == '\n')
		++i;
	if (i == len)
		return (NO_ERR);
	*leftover = malloc(sizeof(char) * (len - i + 1));
	if (!(*leftover))
		return (MALLOC_ERR);
	j = 0;
	while (i + j < len)
	{
		(*leftover)[j] = line[i + j];
		++j;
	}
	(*leftover)[j] = '\0';
	return (NO_ERR);
}

t_err	resize_line(char **line)
{
	size_t	len;
	size_t	i;
	char	*newline;

	len = 0;
	while (*line && (*line)[len] && (*line)[len] != '\n')
		++len;
	if (*line && (*line)[len] == '\n')
		++len;
	if (!len)
		return (NO_ERR);
	newline = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (newline && i < len)
	{
		newline[i] = (*line)[i];
		++i;
	}
	free(*line);
	*line = newline;
	if (!newline)
		return (MALLOC_ERR);
	newline[i] = '\0';
	return (NO_ERR);
}
