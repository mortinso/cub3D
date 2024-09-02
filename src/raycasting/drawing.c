/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:08:45 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/02 20:06:27 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Draws the walls
void	draw_wall(t_cube *cube, t_raycast *cast, int x)
{
	int		line_height;
	double	draw_start;
	double	draw_end;

	line_height = (int)(SCREEN_H / cast->wall_dist);
	draw_start = SCREEN_H / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = SCREEN_H / 2 + line_height / 2;
	if (draw_end >= SCREEN_H)
		draw_end = SCREEN_H;
	while (draw_start < draw_end)
		my_mlx_pixel_put(&cube->game, x, draw_start++, 0x00ff0000);
}

// Draws the ceiling and the floor
void	draw_floor(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
		{
			if (y < SCREEN_H / 2)
				my_mlx_pixel_put(&cube->game, x, y, cube->textures.c_ceil);
			else
				my_mlx_pixel_put(&cube->game, x, y, cube->textures.c_floor);
			x++;
		}
		y++;
	}
}
