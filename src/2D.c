/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2D.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:10:06 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/14 20:06:04 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* Saved just in case
float	distance(t_player *player, float hypo_x, float hypo_y)
{
	return (sqrt((player->x - hypo_x) * (player->x - hypo_x) + \
		(player->y - hypo_y) * (player->y - hypo_y)));
} */

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

// Draws a cell on cube->screen of size CELL and color color
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

// Draws a square where the angle collides with a wall
void	draw_angle(t_cube *cube, t_vector delta, unsigned int color)
{
	t_vector	temp;

	temp.x = cube->player.pos.x + delta.x;
	temp.y = cube->player.pos.y + delta.y;
	while (cube->map.map[(int)temp.y / CELL][(int)temp.x / CELL] != '1')
	{
		temp.x += delta.x;
		temp.y += delta.y;
	}
	temp.x -= delta.x;
	temp.y -= delta.y;
	draw_square(cube, 6, temp, color);
}

// 2D representation of the users FOV
void	draw_fov(t_cube *cube)
{
	t_vector	ray;
	double		tmp_x;
	int			counter;

	counter = 0;
	tmp_x = cube->player.dir.x;
	ray.x = cube->player.dir.x;
	ray.y = cube->player.dir.y;
	while (counter++ <= FOV / 2)
	{
		ray.x = ray.x * cos(-1 * RAD_DEGREE) - ray.y * sin(-1 * RAD_DEGREE);
		ray.y = tmp_x * sin(-1 * RAD_DEGREE) + ray.y * cos(-1 * RAD_DEGREE);
		draw_angle(cube, ray, 0x0000ff00);
	}
	ray.x = cube->player.dir.x;
	ray.y = cube->player.dir.y;
	while (counter-- > 0)
	{
		ray.x = ray.x * cos(1 * RAD_DEGREE) - ray.y * sin(1 * RAD_DEGREE);
		ray.y = tmp_x * sin(1 * RAD_DEGREE) + ray.y * cos(1 * RAD_DEGREE);
		draw_angle(cube, ray, 0x0000ff00);
	}
	draw_angle(cube, cube->player.dir, 0x00ffff00);
}

// Draws a square
void	draw_square(t_cube *cube, int side, t_vector vect, unsigned int color)
{
	double	temp_x;
	double	temp_y;

	temp_y = vect.y - (side / 2);
	while (temp_y < (vect.y + (side / 2)))
	{
		temp_x = vect.x - (side / 2);
		while (temp_x < (vect.x + (side / 2)))
			mlx_pixel_put(cube->mlx, cube->window, temp_x++, temp_y, color);
		temp_y++;
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
