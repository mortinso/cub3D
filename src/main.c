/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:27:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/27 11:14:26 by mortins-         ###   ########.fr       */
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

// Draws a grid with the textures and colors in the following order:
// N W S
// C E F
void	draw_frame(t_cube *cube)
{
	int	x;
	int	y;

	cube->screen.img = mlx_new_image(cube->mlx, SCREEN_W, SCREEN_H);
	cube->screen.addr = mlx_get_data_addr(cube->screen.img, &cube->screen.bpp, \
		&cube->screen.length, &cube->screen.endian);
// Colors
	y = 0;
	while (y < (SCREEN_H / 2))
	{
		x = 0;
		while (x < SCREEN_W)
			my_mlx_pixel_put(&cube->screen, x++, y, cube->textures.c_ceil);
		y++;
	}
	while (y < SCREEN_H)
	{
		x = 0;
		while (x < SCREEN_W)
			my_mlx_pixel_put(&cube->screen, x++, y, cube->textures.c_floor);
		y++;
	}
// Textures
	put_texture(cube, &cube->textures.north, 0, 0);
	put_texture(cube, &cube->textures.west, 32, 0);
	put_texture(cube, &cube->textures.south, 64, 0);
	put_texture(cube, &cube->textures.east, 96, 0);
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
	get_map(&cube, argv[1]);
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
