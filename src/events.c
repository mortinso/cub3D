/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/29 17:00:31 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	destruct(t_cube *cube)
{
	if (cube->map.map)
		free_array(cube->map.map);
	purge_textures(cube);
	mlx_destroy_image(cube->mlx, cube->screen.img);
	mlx_clear_window(cube->mlx, cube->window);
	mlx_destroy_window(cube->mlx, cube->window);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit (0);
	return (0);
}

// Function to move
// 1 = forward
// -1 = backwards
void	move(t_cube *cube, int direction)
{
	if (direction != 1 && direction != -1)
		return ;
	draw_player(cube, cube->player.x, cube->player.y, (unsigned int)cube->textures.c_ceil);
	if (direction == 1)
	{
		cube->player.x += cube->player.delta_x;
		cube->player.y += cube->player.delta_y;
	}
	if (direction == -1)
	{
		cube->player.x -= cube->player.delta_x;
		cube->player.y -= cube->player.delta_y;
	}
	draw_player(cube, cube->player.x, cube->player.y, 0x0000ff00);
}

int	keypress(int key, t_cube *cube)
{
	if (key == KEY_ESC)
		destruct(cube);
	if (key == KEY_W)
		move(cube, 1);
	if (key == KEY_S)
		move(cube, -1);
	if (key == KEY_A)
	{
		cube->player.angle -= 0.1;
		if (cube->player.angle < 0)
			cube->player.angle += 2 * PI;
		cube->player.delta_x = cos(cube->player.angle) * 5; // * 5 cause values are small
		cube->player.delta_y = sin(cube->player.angle) * 5; // * 5 cause values are small
	}
	if (key == KEY_D)
	{
		cube->player.angle += 0.1;
		if (cube->player.angle > 2 * PI)
			cube->player.angle -= 2 * PI;
		cube->player.delta_x = cos(cube->player.angle) * 5; // * 5 cause values are small
		cube->player.delta_y = sin(cube->player.angle) * 5; // * 5 cause values are small
	}
	return (0);
}
