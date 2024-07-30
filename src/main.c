/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:27:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/30 12:48:36 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

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

int	render_frame(t_cube *cube)
{
	mlx_put_image_to_window(cube->mlx, cube->window, cube->screen.img, 0, 0);
	return (0);
}

void	draw_cell(t_cube *cube, int x, int y, unsigned int color)
{
	int	temp_x;
	int	temp_y;

	temp_y = 0;
	while (++temp_y < CELL)
	{
		temp_x = 0;
		while (++temp_x < CELL)
			my_mlx_pixel_put(&cube->screen, x + temp_x, y + temp_y, color);
	}
}

void	draw_player(t_cube *cube, unsigned int color, int draw_angle)
{
	float	temp_x;
	float	temp_y;

	temp_y = (P_SIZE / 2) * -1;
	while (temp_y < P_SIZE / 2)
	{
		temp_x = (P_SIZE / 2) * -1;
		while (temp_x < P_SIZE / 2)
		{
			my_mlx_pixel_put(&cube->screen, cube->player.x + temp_x, cube->player.y + temp_y, color);
			temp_x++;
		}
		temp_y++;
	}
	if (draw_angle)
	{
		temp_y = cube->player.y;
		temp_x = cube->player.x;
		while (temp_x > 0 && temp_y > 0 && (temp_x < SCREEN_W - 1) && (temp_y < SCREEN_H - 1))
		{
			my_mlx_pixel_put(&cube->screen, temp_x, temp_y, 0x00000000);
			temp_x += (cube->player.delta_x / 5); // Dividing for the multiplied value so the line is congruent
			temp_y += (cube->player.delta_y / 5); // Dividing for the multiplied value so the line is congruent
		}
	}
}

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
				draw_cell(cube, x * CELL, y * CELL, 0x00ffffff);
			if (ft_strchr("nsewO", cube->map.map[y][x]))
				draw_cell(cube, x * CELL, y * CELL, cube->textures.c_floor);
			x++;
		}
		y++;
	}
	draw_player(cube, 0x00ff0000, 0);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	if (argc != 2)
	{
		ft_printf("Wrong number of arguments.\nUsage: ./cub3D <path_to_map>\n");
		return (1);
	}
	cube.mlx = mlx_init();
	if (!cube.mlx)
	{
		ft_printf("MLX failed\n");
		exit (1);
	}
	init(&cube, argv[1]);
	draw_frame(&cube);
	cube.window = mlx_new_window(cube.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!cube.window)
	{
		free(cube.mlx);
		ft_printf("Window failed\n");
		exit (1);
	}
	mlx_hook(cube.window, 2, 1L << 0, keypress, &cube);
	mlx_hook(cube.window, 17, 0L, destruct, &cube);
	mlx_loop_hook(cube.mlx, render_frame, &cube);
	mlx_loop(cube.mlx);
}
//Handle exits properly
//Write error messages to STDERR
