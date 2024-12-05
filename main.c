/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kporceil <kporceil@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:52:07 by kporceil          #+#    #+#             */
/*   Updated: 2024/12/02 18:12:17 by kporceil         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int	fd;
	char	*line;

	fd = open("test", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		fflush(stdout);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
