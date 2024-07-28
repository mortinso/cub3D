/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/28 07:23:54 by mortins-         ###   ########.fr       */
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

// int	move(t_cube *cube, float x, float y)
// {
// 	int	temp_x;
// 	int	temp_y;

// 	temp_x = cube->player.x;
// 	temp_y = cube->player.y;
	
// }

int	keypress(int key, t_cube *cube)
{
	if (key == KEY_ESC)
		destruct(cube);
	// if (key == KEY_W)
	// 	move(cube, 0, 1);
	// if (key == KEY_S)
	// 	move(cube, 0, -1);
	return (0);
}
