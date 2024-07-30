/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:10:06 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/30 14:13:27 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Copies an image, pixel by pixel, to `cube->screen`
void	put_texture(t_cube *cube, t_img *texture, int screen_x, int screen_y)
{
	char	*color;
	int		img_x;
	int		img_y;

	img_y = 0;
	while (img_y < texture->height)
	{
		img_x = 0;
		while (img_x < texture->width)
		{
			color = texture->addr + (img_y * texture->length + img_x * \
				(texture->bpp / 8));
			my_mlx_pixel_put(&cube->screen, screen_x + img_x, screen_y \
				+ img_y, *(unsigned int *)color);
			img_x++;
		}
		img_y++;
	}
}

// Draws a cell on cube->screen of color color
void	draw_cell(t_cube *cube, int x, int y, unsigned int color)
{
	int	temp_x;
	int	temp_y;

	temp_y = 0;
	while (temp_y < CELL)
	{
		temp_x = 0;
		while (temp_x < CELL)
		{
			my_mlx_pixel_put(&cube->screen, x + temp_x, y + temp_y, color);
			temp_x++;
		}
		temp_y++;
	}
}

// Draws the player and a representation of its view angle on the window
void	draw_player(t_cube *cube)
{
	float	temp_x;
	float	temp_y;

	temp_y = cube->player.y - (P_SIZE / 2);
	while (temp_y < (cube->player.y + (P_SIZE / 2)))
	{
		temp_x = cube->player.x - (P_SIZE / 2);
		while (temp_x < (cube->player.x + (P_SIZE / 2)))
			mlx_pixel_put(cube->mlx, cube->window, temp_x++, temp_y, P_COLOR);
		temp_y++;
	}
	temp_y = cube->player.y + cube->player.delta_y;
	temp_x = cube->player.x + cube->player.delta_x;
	while (temp_x > 0 && temp_y > 0 && (temp_x < SCREEN_W - 1) && (temp_y < SCREEN_H - 1))
	{
		mlx_pixel_put(cube->mlx, cube->window, temp_x, temp_y, A_COLOR);
		temp_x += (cube->player.delta_x / 5); // Dividing for the multiplied value so the line is congruent
		temp_y += (cube->player.delta_y / 5); // Dividing for the multiplied value so the line is congruent
	}
}

// Draws the map
void	draw_frame(t_cube *cube)
{
	int	x;
	int	y;

	cube->screen.img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
	cube->screen.addr = mlx_get_data_addr(cube->screen.img, &cube->screen.bpp, \
		&cube->screen.length, &cube->screen.endian);

	y = 0;
	while (cube->map.map[y])
	{
		x = 0;
		while (cube->map.map[y][x])
		{
			if (cube->map.map[y][x] == '1')
				put_texture(cube, &cube->textures.north, x * CELL, y * CELL);
			if (ft_strchr("nsewO", cube->map.map[y][x]))
				draw_cell(cube, x * CELL, y * CELL, cube->textures.c_floor);
			x++;
		}
		y++;
	}
}