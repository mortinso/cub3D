/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:37:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/04 16:01:51 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Calculates the distance to the nearest line, both horizontally and vertically
void	step_side_dist(t_vector pos, t_vector dir, t_raycast *cast)
{
	cast->step_x = 1;
	cast->line_dist.x = fabs((cast->map_x + 1.0 - (pos.x / CELL)) * \
		cast->delta_dist.x);
	if (dir.x < 0)
	{
		cast->step_x = -1;
		cast->line_dist.x = fabs(((pos.x / CELL) - cast->map_x) * \
			cast->delta_dist.x);
	}
	cast->step_y = 1;
	cast->line_dist.y = fabs((cast->map_y + 1.0 - (pos.y / CELL)) * \
		cast->delta_dist.y);
	if (dir.y < 0)
	{
		cast->step_y = -1;
		cast->line_dist.y = fabs(((pos.y / CELL) - cast->map_y) * \
			cast->delta_dist.y);
	}
}

// Calculates the distance to the nearest horizontal/vertical lines using DDA
// Sets cast->wall_dist to the shortest one
void	wall_distance(t_cube *cube, t_raycast *cast)
{
	while (1)
	{
		if (cast->line_dist.x < cast->line_dist.y)
		{
			cast->line_dist.x += cast->delta_dist.x;
			cast->map_x += cast->step_x;
			cast->orientation = 0;
		}
		else
		{
			cast->line_dist.y += cast->delta_dist.y;
			cast->map_y += cast->step_y;
			cast->orientation = 1;
		}
		if (cube->map.map[cast->map_y][cast->map_x] == '1')
			break ;
	}
	if (cast->orientation == 0)
		cast->wall_dist = cast->line_dist.x - cast->delta_dist.x;
	else
		cast->wall_dist = cast->line_dist.y - cast->delta_dist.y;
}

void	raycasting(t_cube *cube, t_raycast *cast, t_vector dir)
{
	int	x;

	x = 0;
	draw_floor(cube);
	while (x < SCREEN_W)
	{
		cast->map_x = (int)cube->player.pos.x / CELL;
		cast->map_y = (int)cube->player.pos.y / CELL;
		cast->win_x = 2 * x / (double)SCREEN_W - 1;
		cast->ray_dir.x = dir.x + cube->player.plane.x * cast->win_x;
		cast->ray_dir.y = dir.y + cube->player.plane.y * cast->win_x;
		cast->delta_dist.x = fabs(1 / cast->ray_dir.x);
		cast->delta_dist.y = fabs(1 / cast->ray_dir.y);
		step_side_dist(cube->player.pos, cast->ray_dir, cast);
		wall_distance(cube, cast);
		if (cast->orientation == 0)
			cast->wall_x = (cube->player.pos.y / CELL) + cast->wall_dist * \
				cast->ray_dir.y;
		else
			cast->wall_x = (cube->player.pos.x / CELL) + cast->wall_dist * \
				cast->ray_dir.x;
		cast->wall_x -= floor((cast->wall_x));
		draw_wall(cube, cast, &cast->draw, x);
		x++;
	}
}
