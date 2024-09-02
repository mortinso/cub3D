/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:27:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/02 20:22:25 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Puts a pixel to an image, while mlx's version puts pixels to a window
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

// Function that draws to the window
int	render_frame(t_cube *cube)
{
	/* mlx_put_image_to_window(cube->mlx, cube->window_2, cube->minimap.img, 0, 0);
	draw_square(cube, P_SIZE, cube->player.pos, P_COLOR); */
	mlx_put_image_to_window(cube->mlx, cube->game_window, cube->game.img, 0, 0);
	//draw_fov(cube);
	return (0);
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
	cube.game_window = mlx_new_window(cube.mlx, SCREEN_W, SCREEN_H, "cub3D");
	if (!cube.game_window)
	{
		free(cube.mlx);
		ft_printf("Window failed\n");
		exit (1);
	}
	raycasting(&cube, &cube.raycast, cube.player.dir);
	/* cube.window_2 = mlx_new_window(cube.mlx, SCREEN_W, SCREEN_H, "minimap");
	if (!cube.window_2)
	{
		mlx_clear_window(cube.mlx, cube.game_window);
		mlx_destroy_window(cube.mlx, cube.game_window);
		mlx_destroy_display(cube.mlx);
		free(cube.mlx);
		ft_printf("Window failed\n");
		exit (1);
	} */
	mlx_hook(cube.game_window, 2, 1L << 0, keypress, &cube);
	mlx_hook(cube.game_window, 17, 0L, destruct, &cube);
	// mlx_hook(cube.window_2, 17, 0L, destruct, &cube);
	mlx_loop_hook(cube.mlx, render_frame, &cube);
	mlx_loop(cube.mlx);
}
//Handle exits properly
//Write error messages to STDERR
//Further test error cases
