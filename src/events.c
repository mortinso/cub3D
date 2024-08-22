/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/22 17:03:24 by mortins-         ###   ########.fr       */
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

// Function to move forward/backward (*5 to move faster)
// 1 = forward
// -1 = backward
void	move_straight(t_cube *cube, int direction)
{
	t_vector	tmp;

	if (direction != 1 && direction != -1)
		return ;
	tmp.x = cube->player.pos.x + (cube->player.dir.x * direction * 5);
	tmp.y = cube->player.pos.y + (cube->player.dir.y * direction * 5);
	if (cube->map.map[(int)tmp.y / CELL][(int)tmp.x / CELL] == '1')
		return ;
	cube->player.pos.x = tmp.x;
	cube->player.pos.y = tmp.y;
}

// Function to move sideways (*5 to move faster)
// 1 = right
// -1 = left
void	move_sideways(t_cube *cube, int direction)
{
	t_vector	tmp_dir;
	t_vector	tmp_pos;

	if (direction != 1 && direction != -1)
		return ;
	tmp_dir.x = cube->player.dir.x * cos(90 * RAD_DEGREE) - cube->player.dir.y \
		* sin(90 * RAD_DEGREE);
	tmp_dir.y = cube->player.dir.x * sin(90 * RAD_DEGREE) + cube->player.dir.y \
		* cos(90 * RAD_DEGREE);
	tmp_pos.x = cube->player.pos.x + (tmp_dir.x * direction * 5);
	tmp_pos.y = cube->player.pos.y + (tmp_dir.y * direction * 5);
	if (cube->map.map[(int)tmp_pos.y / CELL][(int)tmp_pos.x / CELL] == '1')
		return ;
	cube->player.pos.x = tmp_pos.x;
	cube->player.pos.y = tmp_pos.y;
}

// Function to change the players angle (*5 to pan faster)
// 1 = pan right
// -1 = pan left
void	pan(t_cube *cube, int angle)
{
	double	tmp_x;

	tmp_x = cube->player.dir.x;
	cube->player.dir.x = cube->player.dir.x * cos(angle * (RAD_DEGREE * 5)) - \
		cube->player.dir.y * sin(angle * (RAD_DEGREE * 5));
	cube->player.dir.y = tmp_x * sin(angle * (RAD_DEGREE * 5)) + \
		cube->player.dir.y * cos(angle * (RAD_DEGREE * 5));
}

// Keypress handler
int	keypress(int key, t_cube *cube)
{
	if (key == KEY_ESC)
		destruct(cube);
	if (key == KEY_W)
		move_straight(cube, 1);
	if (key == KEY_S)
		move_straight(cube, -1);
	if (key == KEY_D)
		move_sideways(cube, 1);
	if (key == KEY_A)
		move_sideways(cube, -1);
	if (key == KEY_ARROW_RIGHT)
		pan(cube, 1);
	if (key == KEY_ARROW_LEFT)
		pan(cube, -1);
	return (0);
}
