/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:03:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/27 16:25:18 by mortins-         ###   ########.fr       */
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
}

// Draws the minimap
void	draw_frame(t_cube *cube)
{
	int	x;
	int	y;

	cube->minimap.img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
	cube->minimap.addr = mlx_get_data_addr(cube->minimap.img, \
		&cube->minimap.bpp, &cube->minimap.length, &cube->minimap.endian);
	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == '1')
				put_texture(cube, &cube->textures.north, x * CELL, y * CELL);
			if (ft_strchr("nsewO", cube->map.map[y][x]))
				draw_cell(cube, x * CELL, y * CELL, cube->textures.c_floor);
			x++;
		}
		y++;
	}
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
				cube->player.pos.x = x * CELL;
				cube->player.pos.y = y * CELL;
				set_angle(cube, cube->map.map[y][x]);
				// draw_frame(cube);
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
