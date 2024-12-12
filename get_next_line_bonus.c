/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:36:56 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/11 14:11:53 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdbool.h>

t_err		join_lst(t_buffer **lst, char **line);
t_buffer	*set_leftover(t_buffer *node);
t_err		fd_search(int fd, t_fd **lst, t_fd **node);
void		*buffer_clear(t_fd **lst, int fd);

char	*get_next_line(int fd)
{
	static t_fd	*fd_lst = NULL;
	t_fd		*current_fd;
	t_err		err;
	char		*line;

	err = NO_ERR;
	err = fd_search(fd, &fd_lst, &current_fd);
	if (!err)
		while (is_line_complete(current_fd->buffer_lst) == false && !err)
			err = lst_add(fd, &current_fd->buffer_lst);
	if (err == READ_ERR)
		return (buffer_clear(&fd_lst, fd));
	else if (err == MALLOC_ERR)
		return (lst_clear(&fd_lst));
	err = join_lst(&current_fd->buffer_lst, &line);
	if (err == MALLOC_ERR)
		return (lst_clear(&fd_lst));
	else if (err == LINE_ERR)
		return (buffer_clear(&fd_lst, fd));
	remove_unused_fd(&fd_lst);
	return (line);
}

t_err	join_lst(t_buffer **lst, char **line)
{
	t_buffer	*node;
	ssize_t		len;
	ssize_t		i;
	ssize_t		j;

	node = *lst;
	len = ft_calc_len(node);
	if (!len)
		return (LINE_ERR);
	*line = malloc(sizeof(char) * (len + 1));
	if (!(*line))
		return (MALLOC_ERR);
	i = 0;
	while (node)
	{
		j = 0;
		while (j < node->bytes_read && node->buffer[j] != '\n' && i < len)
			(*line)[i++] = node->buffer[j++];
		if (j < node->bytes_read && node->buffer[j] == '\n')
			(*line)[i++] = node->buffer[j];
		node = node->next;
	}
	(*line)[i] = '\0';
	*lst = set_leftover(*lst);
	return (NO_ERR);
}

t_buffer	*set_leftover(t_buffer *node)
{
	ssize_t		i;
	ssize_t		j;
	t_buffer	*tmp;

	while (node && node->next)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	i = 0;
	while (i < node->bytes_read && node->buffer[i] != '\n')
		++i;
	++i;
	j = 0;
	while (i < node->bytes_read)
		node->buffer[j++] = node->buffer[i++];
	node->bytes_read = j;
	if (node->bytes_read == 0)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

t_err	fd_search(int fd, t_fd **lst, t_fd **node)
{
	t_fd	*new;
	t_fd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		*node = tmp;
		if (!tmp->next || tmp->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->fd == fd)
		return (NO_ERR);
	new = malloc(sizeof(t_fd));
	if (!new)
		return (MALLOC_ERR);
	new->fd = fd;
	new->next = NULL;
	new->buffer_lst = NULL;
	*node = new;
	if (*lst)
		tmp->next = new;
	else
		*lst = new;
	return (NO_ERR);
}

void	*buffer_clear(t_fd **lst, int fd)
{
	t_fd		*fd_tmp;
	t_fd		*fd_tmp2;
	t_buffer	*buffer_tmp;
	t_buffer	*buffer_tmp2;

	fd_tmp = *lst;
	while (fd_tmp->fd != fd)
	{
		fd_tmp2 = fd_tmp;
		fd_tmp = fd_tmp->next;
	}
	buffer_tmp = fd_tmp->buffer_lst;
	while (buffer_tmp)
	{
		buffer_tmp2 = buffer_tmp;
		buffer_tmp = buffer_tmp->next;
		free(buffer_tmp2);
	}
	if (fd_tmp == *lst)
		*lst = fd_tmp->next;
	else
		fd_tmp2->next = fd_tmp->next;
	free(fd_tmp);
	return (NULL);
}
