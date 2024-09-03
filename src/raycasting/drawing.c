/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:08:45 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/03 15:18:21 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Draws the walls
void	draw_wall(t_cube *cube, t_raycast *cast, int x)
{
	int		line_height;
	double	draw_start;
	double	draw_end;
	int		color;

	if (cast->orientation == 0 && cast->ray_dir.x < 0) // north
		color = 0x009cc2ff;
	else if (cast->orientation == 0 && cast->ray_dir.x >= 0) // south
		color = 0x0063ffa9;
	else if (cast->orientation == 1 && cast->ray_dir.y < 0) // west
		color = 0x00ff82f0;
	else if (cast->orientation == 1 && cast->ray_dir.y >= 0) // east
		color = 0x00ffba6b;
	line_height = (int)(SCREEN_H / cast->wall_dist);
	draw_start = SCREEN_H / 2 - line_height / 2;
	if (draw_start < 0 || line_height < 0)
		draw_start = 0;
	draw_end = SCREEN_H / 2 + line_height / 2;
	if (draw_end >= SCREEN_H || line_height < 0)
		draw_end = SCREEN_H;
	while (draw_start < draw_end)
		my_mlx_pixel_put(&cube->game, x, draw_start++, color);
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
