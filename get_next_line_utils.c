/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 13:05:49 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/04 13:06:04 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*join;

	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (join && s1 && s1[i])
	{
		join[i] = s1[i];
		++i;
	}
	j = 0;
	while (join && s2 && s2[j])
	{
		join[i + j] = s2[j];
		++j;
	}
	if (join)
	{
		free(s1);
		join[i + j] = '\0';
	}
	return (join);
}

bool	is_line_complete(char *line)
{
	size_t	i;

	if (!line)
		return (false);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			return (true);
		++i;
	}
	return (false);
}
