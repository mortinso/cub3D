/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:52:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 17:28:39 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Trims spaces, tabs and newlines from all members of rgb
// Returns 0 if a malloc error occurs
int	clean_color(char **rgb)
{
	char	*tmp;
	int		i;

	i = 0;
	while (rgb[i])
	{
		tmp = ft_strtrim(rgb[i], " \t\n");
		if (!tmp)
		{
			ft_printf("Error\n Malloc failed\n");
			return (0);
		}
		free(rgb[i]);
		rgb[i] = ft_strdup(tmp);
		free (tmp);
		if (!rgb[i++])
		{
			ft_printf("Error\n Malloc failed\n");
			return (0);
		}
	}
	return (1);
}

// Scans rgb for any forbidden characters and invalid color values
// Returns 1 if no error is found
int	check_color(char **rgb)
{
	int		i;

	if (!clean_color(rgb))
		return (0);
	i = 0;
	while (rgb[i])
	{
		if (!is_all_digit(rgb[i]) || ft_atoi(rgb[i]) > 255 \
			|| ft_atoi(rgb[i]) < 0)
			break ;
		i++;
	}
	if (i == 3 && !rgb[i])
		return (1);
	free_array(rgb);
	ft_printf("Error\n Wrongly formatted color\n");
	return (0);
}

// Parses line and converts the string into an unsigned int color
unsigned int	get_color(int fd, char *line)
{
	int				i;
	unsigned int	color;
	char			**rgb;

	rgb = ft_split(line + 2, ',');
	if (!rgb)
	{
		// Will have to be handled differently because a texture value might
		// already be alloc'ed to the struct and it'll need to be freed
		ft_printf("Error\n Malloc failed\n");
		exit (1);
	}
	if (!check_color(rgb))
	{
		// Will have to be handled differently because a texture value might
		// already be alloc'ed to the struct and it'll need to be freed
		free(line);
		close(fd);
		exit (1);
	}
	i = 0;
	color = ft_atoi(rgb[i++]);
	while (rgb[i])
	{
		color *= 256;
		color += ft_atoi(rgb[i++]);
	}
	free_array(rgb);
	return (color);
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
