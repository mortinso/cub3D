/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/28 07:46:20 by mortins-         ###   ########.fr       */
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

void	move(t_cube *cube, float x, float y)
{
	draw_player(cube, cube->player.x, cube->player.y, (unsigned int)cube->textures.c_floor);
	cube->player.x += x;
	cube->player.y += y;
	draw_player(cube, cube->player.x, cube->player.y, 0x00ff0000);
}

int	keypress(int key, t_cube *cube)
{
	if (key == KEY_ESC)
		destruct(cube);
	if (key == KEY_W)
		move(cube, 0, -1);
	if (key == KEY_S)
		move(cube, 0, 1);
	if (key == KEY_A)
		move(cube, -1, 0);
	if (key == KEY_D)
		move(cube, 1, 0);
	return (0);
}
