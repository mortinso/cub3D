/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:33:28 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/04 16:38:57 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Trims spaces and newlines from all members of rgb
// Returns 0 if a malloc error occurs
int	clean_color(char **rgb)
{
	char	*tmp;
	int		i;

	i = 0;
	while (rgb[i])
	{
		tmp = ft_strtrim(rgb[i], " \n");
		if (!tmp)
		{
			free_array(rgb);
			ft_putstr_fd("Error\n Malloc failed\n", 2);
			return (0);
		}
		free(rgb[i]);
		rgb[i] = ft_strdup(tmp);
		if (!rgb[i++])
		{
			rgb[i] = tmp;
			free_array(rgb);
			ft_putstr_fd("Error\n Malloc failed\n", 2);
			return (0);
		}
		free (tmp);
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
	ft_putstr_fd("Error\n Wrongly formatted color\n", 2);
	return (0);
}

// Parses line and converts the string into an unsigned int color
unsigned int	get_color(t_cube *cube, int fd, char *line)
{
	unsigned int	color;
	char			**rgb;
	int				i;

	rgb = ft_split(line + 2, ',');
	if (!rgb)
	{
		free(line);
		map_error(cube, fd, "Malloc failed");
	}
	if (!check_color(rgb))
	{
		free(line);
		map_error(cube, fd, NULL);
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

// Finds what color should be set and checks that it hasn't already been set
void	set_color(t_cube *cube, int fd, char *line)
{
	int	*color;

	color = NULL;
	if (ft_strncmp(line, "F ", 2) == 0)
		color = &cube->textures.c_floor;
	else if (ft_strncmp(line, "C ", 2) == 0)
		color = &cube->textures.c_ceil;
	if (*color > 0)
	{
		free(line);
		map_error(cube, fd, "Multiple definitions of the same color element");
	}
	if (ft_strstr(line, ",,"))
	{
		free(line);
		map_error(cube, fd, "Multiple commas in color definition");
	}
	*color = get_color(cube, fd, line);
}
