/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/30 13:52:33 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Function for a clean exit
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
	cube->player.x += (cube->player.delta_x * direction);
	cube->player.y += (cube->player.delta_y * direction);
	if (cube->player.x < 0 || cube->player.x >= SCREEN_W || cube->player.y < 0 \
		|| cube->player.y >= SCREEN_H)
	{
		cube->player.x -= (cube->player.delta_x * direction);
		cube->player.y -= (cube->player.delta_y * direction);
	}
}

// Function to change the players angle
// 1 = increase angle
// -1 = decrease angle
void	pan(t_cube *cube, int angle)
{
	if (angle != 1 && angle != -1)
		return ;
	cube->player.angle += (0.1 * angle);
	if (angle == 1 && cube->player.angle > 2 * PI)
		cube->player.angle -= 2 * PI;
	if (angle == -1 && cube->player.angle < 0)
		cube->player.angle += 2 * PI;
	cube->player.delta_x = cos(cube->player.angle) * 5; // multiplying so the player moves faster
	cube->player.delta_y = sin(cube->player.angle) * 5; // multiplying so the player moves faster
}

// Keypress handler
int	keypress(int key, t_cube *cube)
{
	if (key == KEY_ESC)
		destruct(cube);
	if (key == KEY_W)
		move(cube, 1);
	if (key == KEY_S)
		move(cube, -1);
	if (key == KEY_A)
		pan(cube, -1);
	if (key == KEY_D)
		pan(cube, 1);
	return (0);
}
