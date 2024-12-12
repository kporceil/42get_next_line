/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:37:38 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/10 16:25:27 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_buffer
{
	char			buffer[BUFFER_SIZE];
	ssize_t			bytes_read;
	struct s_buffer	*next;
}					t_buffer;

typedef enum e_err
{
	NO_ERR,
	MALLOC_ERR,
	READ_ERR,
}					t_err;

t_err				lst_add(int fd, t_buffer **lst);
bool				is_line_complete(t_buffer *buffer);
void				*lst_clear(t_buffer **lst);
ssize_t				ft_calc_len(t_buffer *lst);

char				*get_next_line(int fd);

#endif
