/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:53:47 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 17:57:41 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	purge_textures(t_cube *cube)
{
	if (cube->textures.east.addr)
		mlx_destroy_image(cube->mlx, cube->textures.east.img);
	if (cube->textures.west.addr)
		mlx_destroy_image(cube->mlx, cube->textures.west.img);
	if (cube->textures.south.addr)
		mlx_destroy_image(cube->mlx, cube->textures.south.img);
	if (cube->textures.north.addr)
		mlx_destroy_image(cube->mlx, cube->textures.north.img);
}
