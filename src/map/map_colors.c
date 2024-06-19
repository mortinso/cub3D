/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:33:28 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 17:34:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

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
