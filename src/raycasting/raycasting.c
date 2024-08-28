/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:37:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/28 19:22:34 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Calculates the distance to the nearest line, both horizontally and vertically
void	step_side_dist(t_vector pos, t_vector dir, t_raycast *cast)
{
	if (dir.x != 0)
		cast->delta_dist.x = fabs(1 / dir.x);
	if (dir.y != 0)
		cast->delta_dist.y = fabs(1 / dir.y);
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

// Sets the ray to half the FOV behind, so minus 45º if FOV is 90º
t_vector	set_ray(t_vector dir)
{
	t_vector	new;

	new.x = dir.x * cos(-(FOV / 2 * RAD_DEGREE)) - dir.y * sin(-(FOV / 2 * \
		RAD_DEGREE));
	new.y = dir.x * sin(-(FOV / 2 * RAD_DEGREE)) + dir.y * cos(-(FOV / 2 * \
		RAD_DEGREE));
	return (new);
}

void	raycasting(t_cube *cube, t_vector dir)
{
	t_vector	angle;
	double		tmp_x;

	cube->raycast.screen_x = 0;
	angle = set_ray(dir);
	draw_floor(cube);
	while (cube->raycast.screen_x < SCREEN_W)
	{
		cube->raycast.delta_dist.x = 1e30;
		cube->raycast.delta_dist.y = 1e30;
		cube->raycast.map_x = (int)cube->player.pos.x / CELL;
		cube->raycast.map_y = (int)cube->player.pos.y / CELL;
		step_side_dist(cube->player.pos, angle, &cube->raycast);
		wall_distance(cube, &cube->raycast);
		draw_wall(cube, &cube->raycast);
		cube->raycast.screen_x += SCREEN_W / FOV;
		tmp_x = angle.x;
		angle.x = angle.x * cos(RAD_DEGREE) - angle.y * sin(RAD_DEGREE);
		angle.y = tmp_x * sin(RAD_DEGREE) + angle.y * cos(RAD_DEGREE);
	}
}
