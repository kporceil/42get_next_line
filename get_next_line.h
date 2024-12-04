/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:07:46 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/04 14:27:58 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>

typedef enum e_err
{
	NO_ERR,
	MALLOC_ERR,
	READ_ERR,
}	t_err;

size_t	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
bool	is_line_complete(char *line);

char	*get_next_line(int fd);

#endif
