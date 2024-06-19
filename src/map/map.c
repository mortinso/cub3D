/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 18:30:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Frees and destroys everything when an error is found when parsing the map
void	map_error(t_cube *cube, int fd)
{
	close(fd);
	purge_textures(cube);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit (1);
}

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
	cube->textures.c_ceil = -1;
	cube->textures.c_floor = -1;
	cube->textures.east.addr = NULL;
	cube->textures.west.addr = NULL;
	cube->textures.south.addr = NULL;
	cube->textures.north.addr = NULL;
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("gnl failed\n");
		close(fd);
		exit (1);
	}
	while (line)
	{
		// Add way to check if texture has already been set, if so error
		if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (cube->textures.c_floor > 0)
			{
				ft_printf("Error\nMultiple definition of %c\n", line[0]);
				free(line);
				map_error(cube, fd);
			}
			cube->textures.c_floor = get_color(cube, fd, line);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (cube->textures.c_ceil > 0)
			{
				ft_printf("Error\nMultiple definition of %c\n", line[0]);
				free(line);
				map_error(cube, fd);
			}
			cube->textures.c_ceil = get_color(cube, fd, line);
		}
		// Add support for the textures
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	// Should empty spaces before identifier be allowed?
}
