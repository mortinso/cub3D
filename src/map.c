/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/14 18:36:58 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Function to turn RGB string from map file into an unsigned int
unsigned int	map_color(int fd, char *line)
{
	int		i;
	int		color;
	char	**buf;

	i = 0;
	color = 0;
	buf = ft_split(line + 2, ',');
	// if any member contains forbidden character or there's more than 3 members
	// close(fd);
	// ft_printf error message
	// exit (1);
	while (i < 2)
	{
		color += ft_atoi(buf[i++]);
		color *= 256;
	}
	color += ft_atoi(buf[i]);
	while (buf[i])
	{
		free(buf[i++]);
	}
	if (i != 3)
		close(fd);
	return (color);
}

// Function to initiate the textures/colors
void	get_map(t_cube *cube, char *fd_map)
{
	int		fd;
	char	*line;

	if (!ft_strnstr(fd_map + (ft_strlen(fd_map) - 4), ".cub", 5))
	{
		ft_printf("ERROR: Map is not type '.cub'\n");
		exit (1);
	}
	fd = open(fd_map, O_RDONLY);
	if (read(fd, NULL, 0) < 0)
	{
		ft_printf("ERROR: Map is inacessible\n");
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
		if (ft_strncmp(line, "F ", 2) == 0)
			cube->textures.c_floor = map_color(fd, line);
		else if (ft_strncmp(line, "C ", 2) == 0)
			cube->textures.c_ceil = map_color(fd, line);
		// Add support for the textures
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
