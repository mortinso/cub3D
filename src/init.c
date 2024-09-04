/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:03:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/04 16:01:44 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Sets the players view angle according to the map
void	set_angle(t_cube *cube, char direction)
{
	if (direction == 'n')
	{
		cube->player.dir.x = 0;
		cube->player.dir.y = -1;
	}
	else if (direction == 's')
	{
		cube->player.dir.x = 0;
		cube->player.dir.y = 1;
	}
	else if (direction == 'e')
	{
		cube->player.dir.x = 1;
		cube->player.dir.y = 0;
	}
	else if (direction == 'w')
	{
		cube->player.dir.x = -1;
		cube->player.dir.y = 0;
	}
	cube->player.plane.x = -(cube->player.dir.y * 0.66);
	cube->player.plane.y = cube->player.dir.x * 0.66;
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
				cube->player.pos.x = x * CELL + CELL / 2;
				cube->player.pos.y = y * CELL + CELL / 2;
				set_angle(cube, cube->map.map[y][x]);
				cube->game.img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
				cube->game.addr = mlx_get_data_addr(cube->game.img, \
					&cube->game.bpp, &cube->game.length, &cube->game.endian);
				return ;
			}
			x++;
		}
		y++;
	}
}
