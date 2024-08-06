/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:13:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 22:54:15 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

float	distance(t_player *player, float hypo_x, float hypo_y)
{
	return (sqrt((player->x - hypo_x) * (player->x - hypo_x) + \
		(player->y - hypo_y) * (player->y - hypo_y)));
}

//dof is depth of field
void	drawRays3D(t_cube *cube)
{
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	x_offset;
	float	y_offset;
	int		map_x;
	int		map_y;
	float	angle_tan;

	ray_angle = cube->player.angle;
	// Horizontal lines
	float	horiz_dist = -1;
	float	horiz_x;
	float	horiz_y;
	angle_tan = -1 / tan(ray_angle);
	if (ray_angle > PI) // looking up
	{
		horiz_y = (((int)cube->player.y >> 6) << 6) - 0.0001;
		horiz_x = (cube->player.y - horiz_y) * angle_tan + cube->player.x;
		y_offset = -64;
		x_offset = -y_offset * angle_tan;
		printf("up\n");
	}
	else if (ray_angle < PI) // looking down
	{
		horiz_y = (((int)cube->player.y >> 6) << 6) + 64;
		horiz_x = (cube->player.y - horiz_y) * angle_tan + cube->player.x;
		y_offset = 64;
		x_offset = -y_offset * angle_tan;
		printf("down\n");
	}
	else // looking left or rightprintf("( %f , %f )\n", vert_x / CELL, vert_y / CELL);
	{
		horiz_x = cube->player.x;
		horiz_y = cube->player.y;
		y_offset = 0;
		printf("left/right\n");
	}
	map_x = (int)horiz_x >> 6;
	map_y = (int)horiz_y >> 6;
	while (y_offset != 0)// maybe protect to check that we're within the map
	{
		if (cube->map.map[map_y][map_x] == '1')
		{
			horiz_dist = distance(&cube->player, horiz_x, horiz_y);
			printf("calculating horizontal distance...\n");
			break ;
		}
		horiz_x += x_offset;
		horiz_y += y_offset;
		map_x = (int)horiz_x >> 6;
		map_y = (int)horiz_y >> 6;
	}

	//Vertical lines
	float	vert_dist = -1;
	float	vert_x;
	float	vert_y;
	angle_tan = -tan(ray_angle);
	if (ray_angle > PI/2 && ray_angle <= 269 * RAD_DEGREE) // looking left
	{
		vert_x = (((int)cube->player.x >> 6) << 6) - 0.0001;
		vert_y = (cube->player.x - vert_x) * angle_tan + cube->player.y;
		x_offset = -64;
		y_offset = -x_offset * angle_tan;
		printf("left\n");
	}
	else if (ray_angle < PI/2 || ray_angle >= 271 * RAD_DEGREE) // looking right
	{
		vert_x = (((int)cube->player.x >> 6) << 6) + 64;
		vert_y = (cube->player.x - vert_x) * angle_tan + cube->player.y;
		x_offset = 64;
		y_offset = -x_offset * angle_tan;
		printf("right\n");
	}
	else // looking up or down
	{
		vert_x = cube->player.x;
		vert_y = cube->player.y;
		x_offset = 0;
		printf("up/down\n");
	}
	map_x = (int)vert_x >> 6;
	map_y = (int)vert_y >> 6;
	printf("( %f , %f )\n", vert_x / CELL, vert_y / CELL);
	printf("( %i , %i )\n", map_x, map_y);
	while (x_offset != 0) // maybe protect to check that we're within the map
	{
		if (cube->map.map[map_y][map_x] == '1')
		{
			printf("calculating distance...\n");
			vert_dist = distance(&cube->player, vert_x, vert_y);
			break ;
		}
		vert_x += x_offset;
		vert_y += y_offset;
		map_x = (int)vert_x >> 6;
		map_y = (int)vert_y >> 6;
	}
	
	// For final comparisson I need
	// vert_x
	// vert_y
	// vert_dist
	// horiz_x
	// horiz_y
	// horiz_dist
	printf("comparing...\n");
	if (!horiz_dist || (vert_dist && vert_dist <= horiz_dist))
	{
		ray_x = vert_x;
		ray_y = vert_y;
	}
	else if (!vert_dist || (horiz_dist && vert_dist > horiz_dist))
	{
		ray_x = horiz_x;
		ray_y = horiz_y;
	}
	else
	{
		printf("ERROR on comparisson\n");
		destruct(cube);
	}
	printf("RAY ( %f , %f )\n", ray_x / CELL, ray_y / CELL);
	printf("putting pixel\n\n");
	for(int i = 0; i < 5; i++)
	{
		mlx_pixel_put(cube->mlx, cube->window, ray_x, ray_y + i, P_COLOR);
	}
	// Simplify to not be shitter code
	// Remove all of the dumb spaghetti shit
	// Name variables properly
	// Removed unnecessary variables
	// Remove redundancies
	// Separate code into functions like a normal human being
	// Loop everything to draw the fov instead of just one angle (like my function)
	// actually use this to draw somehow
	// Keep following the tutorial
	// Replace all mentions of 64 and bit shifting by 16 with the CELL macro
}
