/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tutorial.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 18:13:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/05 20:04:18 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Teorema de pitagoras
float	distance(t_player *player, float hypo_x, float hypo_y, float ray_angle)
{
	return (sqrt((player->x - hypo_x) * (player->x - hypo_x) + \
		(player->y - hypo_y) * (player->y - hypo_y)));
}

//dof is depth of field
void	drawRays3D(t_cube *cube)
{
	int		ray, map_x, map_y, map_pos, dof;
	float	ray_x, ray_y, ray_angle, x_offset, y_offset;

	ray_angle = cube->player.angle;
	{
		// Horizontal lines
		dof = 0;
		float	horiz_dist = -1;
		float	horiz_x = cube->player.x;
		float	horiz_y = cube->player.y;
		float	angle_tan = -1/tan(ray_angle);
		if (ray_angle > PI) // looking down
		{
			ray_y = (((int)cube->player.y >> 6) << 6) - 0.0001;
			ray_x = (cube->player.y - ray_y) * angle_tan + cube->player.x;
			y_offset = -64;
			x_offset = -y_offset * angle_tan;
		}
		else if (ray_angle < PI) // looking up
		{
			ray_y = (((int)cube->player.y >> 6) << 6) + 64;
			ray_x = (cube->player.y - ray_y) * angle_tan + cube->player.x;
			y_offset = 64;
			x_offset = -y_offset * angle_tan;
		}
		else if (ray_angle == 0 || ray_angle == PI) // looking straight left or right
		{
			ray_x = cube->player.x;
			ray_y = cube->player.y;
			dof = 8;
		}
		while (dof < 8) // remove dof
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			if (cube->map.map[map_y][map_x] == '1')
			{
				horiz_x = ray_x;
				horiz_y = ray_y;
				horiz_dist = distance(&cube->player, horiz_x, horiz_y, ray_angle);
				break ;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				dof++;
			}
		}

		//Vertical lines
		dof = 0;
		float	vert_dist = -1;
		float	vert_x = cube->player.x;
		float	vert_y = cube->player.y;
		float neg_tan = -tan(ray_angle);
		if (ray_angle > PI/2 && ray_angle < 3*PI/2) // looking left
		{
			ray_x = (((int)cube->player.x >> 6) << 6) - 0.0001;
			ray_y = (cube->player.x - ray_x) * neg_tan + cube->player.y;
			x_offset = -64;
			y_offset = -x_offset * neg_tan;
		}
		else if (ray_angle < PI/2 || ray_angle > 3*PI/2) // looking right
		{
			ray_x = (((int)cube->player.x >> 6) << 6) + 64;
			ray_y = (cube->player.x - ray_x) * neg_tan + cube->player.y;
			x_offset = 64;
			y_offset = -x_offset * neg_tan;
		}
		else if (ray_angle == PI/2 || ray_angle == 3*PI/2) // looking up or down
		{
			ray_x = cube->player.x;
			ray_y = cube->player.y;
			dof = 8;
		}
		while (dof < 8) // remove dof
		{
			map_x = (int)ray_x >> 6;
			map_y = (int)ray_y >> 6;
			if (cube->map.map[map_y][map_x] == '1')
			{
				vert_x = ray_x;
				vert_y = ray_y;
				vert_dist = distance(&cube->player, vert_x, vert_y, ray_angle);
				break ;
			}
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				dof++;
			}
		}
		if (!horiz_dist || (vert_dist && vert_dist < horiz_dist))
		{
			ray_x = vert_x;
			ray_y = vert_y;
		}
		else if (!vert_dist || (horiz_dist && vert_dist > horiz_dist))
		{
			ray_x = horiz_x;
			ray_y = horiz_y;
		}
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
