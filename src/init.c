/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:03:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/29 16:59:38 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	set_angle(t_cube *cube, char direction)
{
	if (direction == 'n')
		cube->player.angle = PI * 1.5;
	else if (direction == 'w')
		cube->player.angle = PI;
	else if (direction == 's')
		cube->player.angle = PI / 2;
	else if (direction == 'e')
		cube->player.angle = PI * 2;
	cube->player.delta_x = cos(cube->player.angle) * 5; // * 5 cause values are small
	cube->player.delta_y = sin(cube->player.angle) * 5; // * 5 cause values are small
}

// Figure out how to extract angle
// Call get_map, then init the player variables
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
				cube->player.x = (x * GRID_CELL) + ((GRID_CELL - PLAYER_SIZE) / 2);
				cube->player.y = (y * GRID_CELL) + ((GRID_CELL - PLAYER_SIZE) / 2);
				set_angle(cube, cube->map.map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
// maybe draw the first instance of the map? or should that be only in the drawing function?
}
