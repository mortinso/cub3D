/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:27:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 18:32:27 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	main(int argc, char **argv)
{
	t_cube	cube;
	int		x;
	int		y;

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
	cube.window = mlx_new_window(cube.mlx, 1920, 1080, "cub3D");
	if (!cube.window)
	{
		free(cube.mlx);
		ft_printf("Window failed\n");
		exit (1);
	}

	// V -------------- Puts ceiling and floor colors on screen -------------- V
	cube.screen.img = mlx_new_image(cube.mlx, 1920, 1080);
	cube.screen.addr = mlx_get_data_addr(cube.screen.img, &cube.screen.bpp, \
		&cube.screen.length, &cube.screen.endian);
	// Floor tile
	x = 0;
	while (x < 960)
	{
		y = 0;
		while (y < 1080)
			my_mlx_pixel_put(&cube.screen, x, y++, cube.textures.c_floor);
		x++;
	}
	// Ceiling tile
	while (x < 1920)
	{
		y = 0;
		while (y < 1080)
			my_mlx_pixel_put(&cube.screen, x, y++, cube.textures.c_ceil);
		x++;
	}
	mlx_put_image_to_window(cube.mlx, cube.window, cube.screen.img, 0, 0);

	mlx_hook(cube.window, 17, 0L, destruct, &cube);
	mlx_loop(cube.mlx);
}
//Handle exits properly
