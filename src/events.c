/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:13:14 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 18:15:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	destruct(t_cube *cube)
{
	purge_textures(cube);
	mlx_destroy_image(cube->mlx, cube->screen.img);
	mlx_clear_window(cube->mlx, cube->window);
	mlx_destroy_window(cube->mlx, cube->window);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	exit (0);
	return (0);
}
