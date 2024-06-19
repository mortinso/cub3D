/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 17:39:16 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Function to initiate the textures/colors
void	get_map(t_cube *cube, char *fd_map)
{
	int		fd;
	char	*line;

	if (!ft_strnstr(fd_map + (ft_strlen(fd_map) - 4), ".cub", 5))
	{
		ft_printf("Error\n Map is not type '.cub'\n");
		exit (1);
	}
	fd = open(fd_map, O_RDONLY);
	if (read(fd, NULL, 0) < 0)
	{
		ft_printf("Error\n Map is inacessible\n");
		exit (1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("gnl failed\n");
		close(fd);
		exit (1);
	}
	while (line)
	{
		// Add way to check if texture/color has already been set, if so error
		if (ft_strncmp(line, "F ", 2) == 0)
			cube->textures.c_floor = get_color(fd, line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			cube->textures.c_ceil = get_color(fd, line);
		// Add support for the textures
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	exit (0);
	// Should empty spaces before identifier be allowed?
}
