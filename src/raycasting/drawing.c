/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:08:45 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/03 19:06:52 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Sets the values of the variables in `draw`
void	set_values(t_raycast *cast, t_textures *textures, t_draw *draw)
{
	if (cast->orientation == 1 && cast->ray_dir.y < 0)
		draw->texture = textures->north;
	else if (cast->orientation == 1 && cast->ray_dir.y >= 0)
		draw->texture = textures->south;
	else if (cast->orientation == 0 && cast->ray_dir.x < 0)
		draw->texture = textures->west;
	else
		draw->texture = textures->east;
	draw->step = 1.0 * draw->texture.height / draw->line_height;
	draw->pos = (draw->start - SCREEN_H / 2 + draw->line_height / 2) * \
		draw->step;
	draw->x = (int)(cast->wall_x * (double)draw->texture.width);
	if (cast->orientation == 0 && cast->ray_dir.x < 0)
		draw->x = draw->texture.width - draw->x - 1;
	if (cast->orientation == 1 && cast->ray_dir.y > 0)
		draw->x = draw->texture.width - draw->x - 1;
}

// Draws the walls
void	draw_wall(t_cube *cube, t_raycast *cast, t_draw *draw, int x)
{
	char	*color;
	int		win_y;

	draw->line_height = (int)(SCREEN_H / cast->wall_dist);
	draw->start = SCREEN_H / 2 - draw->line_height / 2;
	if (draw->start < 0 || draw->line_height < 0)
		draw->start = 0;
	draw->end = SCREEN_H / 2 + draw->line_height / 2;
	if (draw->end >= SCREEN_H || draw->line_height < 0)
		draw->end = SCREEN_H;
	set_values(cast, &cube->textures, draw);
	win_y = draw->start;
	while (win_y < draw->end)
	{
		draw->y = (int)draw->pos;
		draw->pos += draw->step;
		color = draw->texture.addr + (draw->y * draw->texture.length + draw->x \
			* (draw->texture.bpp / 8));
		my_mlx_pixel_put(&cube->game, x, win_y, *(unsigned int *)color);
		win_y++;
	}
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
