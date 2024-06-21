/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:47 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/21 19:35:54 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	purge_textures(t_cube *cube)
{
	if (cube->textures.east.addr)
		mlx_destroy_image(cube->mlx, cube->textures.east.img);
	if (cube->textures.west.addr)
		mlx_destroy_image(cube->mlx, cube->textures.west.img);
	if (cube->textures.south.addr)
		mlx_destroy_image(cube->mlx, cube->textures.south.img);
	if (cube->textures.north.addr)
		mlx_destroy_image(cube->mlx, cube->textures.north.img);
}

char	*texture_path(const char *line)
{
	char	*path;

	path = ft_strtrim(line + 3, " \t\n");
	if (!path)
		ft_printf("Error\n Malloc failed\n");
	else if (ft_strlen(path) < 5 || !ft_strnstr(path + (ft_strlen(path) - 4), \
		".xpm", 5))
	{
		ft_printf("path = <%s>\n", path);
		ft_printf("Error\n Texture is not type '.xpm'\n");
		free(path);
		path = NULL;
	}
	return (path);
}

void	check_texture(t_cube *cube, int fd, char *line) //Need to either receive image or return the path
{
	char	*fd_path;
	int		texture_fd;

	fd_path = texture_path(line);
	if (!fd_path)
	{
		free(line);
		map_error(cube, fd);
	}
	texture_fd = open(fd_path, O_RDONLY);
	if (texture_fd < 0)
	{
		free(fd_path);
		ft_printf("Error\n Can't open texture file\n");
		free(line);
		map_error(cube, fd);
	}
	// Init image
	close(texture_fd);
	ft_printf("Texture %c%c is valid\n", line[0], line[1]); //<-
	free(fd_path); //
}

void	save_texture(t_cube *cube, int fd, char *line)
{
	t_img	*img;

	if (ft_strncmp(line, "NO ", 3) == 0)
		img = &cube->textures.north;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		img = &cube->textures.south;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		img = &cube->textures.west;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		img = &cube->textures.east;
	if (img->addr)
	{
		ft_printf("Error\nMultiple definition of %c%c\n", line[0], line[1]);
		free(line);
		map_error(cube, fd);
	}
	check_texture(cube, fd, line);
}
