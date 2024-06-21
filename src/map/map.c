/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/21 18:12:06 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Frees and destroys everything when an error is found when parsing the map
void	map_error(t_cube *cube, int fd)
{
	if (fd >= 0)
		close(fd);
	purge_textures(cube);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit (1);
}

// Function to initiate the textures/colors
void	get_map(t_cube *cube, char *map_fd)
{
	int		fd;
	char	*line;

	cube->textures.c_ceil = -1;
	cube->textures.c_floor = -1;
	cube->textures.east.addr = NULL;
	cube->textures.west.addr = NULL;
	cube->textures.south.addr = NULL;
	cube->textures.north.addr = NULL;
	if (ft_strlen(map_fd) < 5 || \
		!ft_strnstr(map_fd + (ft_strlen(map_fd) - 4), ".cub", 5))
	{
		ft_printf("Error\n Map is not type '<name>.cub'\n");
		map_error(cube, -1);
	}
	fd = open(map_fd, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n Map is inacessible\n");
		map_error(cube, -1);
	}
	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("gnl failed\n");
		map_error(cube, fd);
	}
	while (line)
	{
		// Check if the program is looking at the map before the colors/textures have been set, if so error
		if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			save_color(cube, fd, line);
		// Add support for the textures and check if texture has already been set, if so error
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
			|| ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0)
			save_texture(cube, fd, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	// Should empty spaces before identifier be allowed?
}
