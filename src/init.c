/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:03:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 21:08:05 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Sets the players view angle according to the map
// Also sets delta_x and delta_y
void	set_angle(t_cube *cube, char direction)
{
	if (direction == 'n')
		cube->player.angle = 3*PI/2;
	else if (direction == 'w')
		cube->player.angle = PI;
	else if (direction == 's')
		cube->player.angle = PI / 2;
	else if (direction == 'e')
		cube->player.angle = PI * 2;
	cube->player.delta_x = cos(cube->player.angle) * 5; // *5 to move faster
	cube->player.delta_y = sin(cube->player.angle) * 5; // *5 to move faster
}

// Calls get_map, then init the player variables
void	init(t_cube *cube, char *map_fd)
{
	int	x;
	int	y;

	get_map(cube, map_fd);
	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (ft_strchr("nsew", cube->map.map[y][x]))
			{
				cube->player.x = x * CELL;
				cube->player.y = y * CELL;
				set_angle(cube, cube->map.map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
// Should the first frame be drawn here?
}
