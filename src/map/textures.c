/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:47 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/04 16:18:59 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Returns true if line has a valid texture identifier
int	is_texture_identifier(const char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 || \
		ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

// Destroy textures, if they have already been set
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

// Trims spaces and newlines from line and checks if the file is of type '.xpm'
// Returns a cleaned up (char *)path if no error is found
char	*texture_path(const char *line)
{
	char	*path;

	path = ft_strtrim(line + 3, " \n");
	if (!path)
		ft_putstr_fd("Error\n Malloc failed\n", 2);
	else if (ft_strlen(path) < 5 || !ft_strnstr(path + (ft_strlen(path) - 4), \
		".xpm", 5))
	{
		ft_putstr_fd("Error\n Texture is not type '.xpm'\n", 2);
		free(path);
		path = NULL;
	}
	return (path);
}

// Initiates the texture to the struct.
// Returns 0 if it error, this was done to follow the norme
int	init_texture(t_cube *cube, char *line, t_img *img)
{
	char	*path;
	int		texture_fd;

	path = texture_path(line);
	if (!path)
		return (0);
	texture_fd = open(path, O_RDONLY);
	if (texture_fd < 0)
	{
		ft_putstr_fd("Error\n Can't open texture file\n", 2);
		free(path);
		return (0);
	}
	close(texture_fd);
	img->img = mlx_xpm_file_to_image(cube->mlx, path, &img->width, \
		&img->height);
	free(path);
	if (img->img == NULL)
	{
		ft_putstr_fd("Error\nFailed to read texture\n", 2);
		return (0);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
		&img->endian);
	return (1);
}

// Finds which texture should be set and checks that it hasn't already been set
// Handles any errors that might be found in `init_texture()`
void	set_texture(t_cube *cube, int fd, char *line)
{
	t_img	*img;

	img = NULL;
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
		free(line);
		map_error(cube, fd, "Multiple definitions of the same texture element");
	}
	if (!init_texture(cube, line, img))
	{
		free(line);
		map_error(cube, fd, NULL);
	}
}
