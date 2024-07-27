/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:14:48 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/27 13:04:15 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Errors if the map has any forbidden characters and empty lines or a wrong
// number of player starting positions
void	map_chars(t_cube *cube)
{
	int	player;
	int	y;
	int	x;

	y = 0;
	player = 0;
	while (y < cube->map.size)
	{
		x = 0;
		if (!cube->map.map[y][x])
			map_error(cube, -1, "Empty line found in the middle of the map");
		while (x < (int)ft_strlen(cube->map.map[y]))
		{
			if (!ft_strchr("01NSEW ", cube->map.map[y][x]))
				map_error(cube, -1, "Invalid character in map content");
			if (ft_strchr("NSEW", cube->map.map[y][x++]))
				player++;
		}
		y++;
	}
	if (player == 0)
		map_error(cube, -1, "No player starting position in map");
	if (player > 1)
		map_error(cube, -1, "Multiple player starting positions found");
}

// Check surrounding cells in order to check that the map is closed
void	check_surrounding(t_cube *cube, int x, int y)
{
	if (ft_strchr(" \n", cube->map.map[y][x]))
		map_error(cube, -1, "Map isn't surrounded by walls");
	if (ft_strchr("0NSEW", cube->map.map[y][x]))
	{
		if (x == 0 || y == 0)
			map_error(cube, -1, "Map isn't surrounded by walls");
		if (cube->map.map[y][x] == '0')
			cube->map.map[y][x] = 'O';
		if (ft_strchr("NSEW", cube->map.map[y][x]))
			cube->map.map[y][x] += 32;
		check_surrounding(cube, x - 1, y - 1);
		check_surrounding(cube, x, y - 1);
		check_surrounding(cube, x + 1, y - 1);
		check_surrounding(cube, x - 1, y);
		check_surrounding(cube, x + 1, y);
		check_surrounding(cube, x - 1, y + 1);
		check_surrounding(cube, x, y + 1);
		check_surrounding(cube, x + 1, y + 1);
	}
}

// Function to check that the map content is closed(surrounded by walls)
void	map_closed(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (ft_strchr("0NSEW", cube->map.map[y][x]))
				check_surrounding(cube, x, y);
			x++;
		}
		y++;
	}
}
