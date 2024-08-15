/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:37:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/15 18:10:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Calculates the distance to the nearest line, both horizontally and vertically
void	step_side_dist(t_vector pos, t_vector dir, t_raycast cast)
{
	if (dir.x != 0)
		cast.delta_dist.x = fabs(1 / dir.x);
	if (dir.y != 0)
		cast.delta_dist.y = fabs(1 / dir.y);
	if (dir.x < 0)
	{
		cast.step_x = -1;
		cast.line_dist.x = (pos.x - cast.map_x) * cast.delta_dist.x;
	}
	else
	{
		cast.step_x = 1;
		cast.line_dist.x = (cast.map_x + 1.0 - pos.x) * cast.delta_dist.x;
	}
	if (dir.y < 0)
	{
		cast.step_y = -1;
		cast.line_dist.y = (pos.y - cast.map_y) * cast.delta_dist.y;
	}
	else
	{
		cast.step_y = 1;
		cast.line_dist.y = (cast.map_y + 1.0 - pos.y) * cast.delta_dist.y;
	}
}

// Calculates the distance to the nearest horizontal/vertical lines using DDA
// Sets ray.wall_dist to the shortest one
void	wall_distance(t_cube *cube, t_vector pos, t_vector dir, t_raycast cast)
{
	int	orientation;
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (cast.line_dist.x < cast.line_dist.y)
		{
			cast.line_dist.x += cast.delta_dist.x;
			cast.map_x += cast.step_x;
			orientation = 0;
		}
		else
		{
			cast.line_dist.y += cast.delta_dist.y;
			cast.map_y += cast.step_y;
			orientation = 1;
		}
		printf("( %f , %f )  ", (pos.x + cast.line_dist.x) / 64, (pos.y + cast.line_dist.y) / 64); //
		mlx_pixel_put(cube->mlx, cube->window, pos.x + cast.line_dist.x, pos.y + cast.line_dist.y, 0x00ff0000); //
		if (cube->map.map[cast.map_y][cast.map_x] == '1')
			hit = 1;
	}
	if (orientation == 0)
		cast.wall_dist = (cast.map_x - pos.x + (1 - cast.step_x) / 2) / dir.x;
	else
		cast.wall_dist = (cast.map_y - pos.y + (1 - cast.step_y) / 2) / dir.y;
	printf("\n"); //
}

void	raycasting(t_cube *cube, t_vector dir)
{
	cube->raycast.delta_dist.x = 1e30;
	cube->raycast.delta_dist.y = 1e30;
	cube->raycast.map_x = (int)cube->player.pos.x / CELL;
	cube->raycast.map_y = (int)cube->player.pos.y / CELL;
	step_side_dist(cube->player.pos, dir, cube->raycast);
	wall_distance(cube, cube->player.pos, dir, cube->raycast);
}
