/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/25 18:32:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Frees and destroys everything when an error is found when parsing the map
void	map_error(t_cube *cube, int fd, char *error_msg)
{
	if (error_msg != NULL)
		ft_printf("Error\n%s\n", error_msg);
	if (fd >= 0)
		close(fd);
	purge_textures(cube);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit (1);
}

// Returns 1 if all media has been set
int	media_is_set(t_cube *cube)
{
	if (cube->textures.c_ceil < 0 || cube->textures.c_floor < 0)
		return (0);
	if (!(cube->textures.north.addr && cube->textures.south.addr && \
		cube->textures.east.addr && cube->textures.west.addr))
		return (0);
	return (1);
}

// Parses the map file and initiates the colors and textures
void	get_media(t_cube *cube, char *map_fd)
{
	int		fd;
	char	*line;

	fd = open(map_fd, O_RDONLY);
	if (fd < 0)
		map_error(cube, -1, "Failed to open map file");
	line = get_next_line(fd);
	if (!line)
		map_error(cube, fd, "GNL failed");
	while (line)
	{
		// Error if the program looks at the map before the media has been set
		// Maybe create a function that checks if the string is a valid texture
		// identifier, this would save us some lines of code for the norme
		if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			set_color(cube, fd, line);
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) \
			== 0 || ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0)
			set_texture(cube, fd, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (!media_is_set(cube))
		map_error(cube, fd, "Color/Texture definition missing in the map file");
	close(fd);
	// Should empty spaces be allowed before an identifier? I don't think so
}

// This fucntion will serve as a sort of hub
// It calls `get_media()` to initiate the textures/colors and then it'll call
// the function to check that the map is valid (function is yet to be created)
void	get_map(t_cube *cube, char *map_fd)
{
	// V-- This should probably be moved to a different function --V
	cube->textures.c_ceil = -1;
	cube->textures.c_floor = -1;
	cube->textures.east.addr = NULL;
	cube->textures.west.addr = NULL;
	cube->textures.south.addr = NULL;
	cube->textures.north.addr = NULL;
	if (ft_strlen(map_fd) < 5 || \
		!ft_strnstr(map_fd + (ft_strlen(map_fd) - 4), ".cub", 5))
		map_error(cube, -1, "Map is not type '<name>.cub'");
	get_media(cube, map_fd);
}
