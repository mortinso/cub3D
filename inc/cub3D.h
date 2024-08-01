/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:31:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/01 17:16:30 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_W 2560
# define SCREEN_H 1440

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
// # include "../minilibx-linux/mlx.h" // For 42 pcs
# include <mlx.h> // for my pc
# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.1415926535

// v-------- 2Dview -------v
# define CELL 64 //2D
# define P_SIZE 15 //2D
# define P_COLOR 0x00ff0000
# define A_COLOR 0x00ffff00

//------------------------------------KEYS--------------------------------------
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

//-----------------------------------STRUCT-------------------------------------
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		c_ceil;
	int		c_floor;
}	t_textures;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	delta_x;
	float	delta_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		size;
}	t_map;

typedef struct s_cube
{
	void		*mlx;
	void		*window;
	t_map		map;
	t_textures	textures;
	t_img		screen;
	t_player	player;
}	t_cube;

//------------------------------------SRCS--------------------------------------
// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// 2D.c
void	draw_frame(t_cube *cube);
void	draw_player(t_cube *cube);

// events.c
int		destruct(t_cube *cube);
int		keypress(int key, t_cube *cube);

// init.c
void	init(t_cube *cube, char *map_fd);

// main.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

// utils.c
void	free_array(char **array);
int		is_all_digit(const char *str);

// +++++++++++++++ map/[.....] ++++++++++++++++++++++++++++++++++++++++++++++++
// colors.c
void	set_color(t_cube *cube, int fd, char *line);

// content_check.c
void	map_chars(t_cube *cube);
void	map_closed(t_cube *cube);

// content.c
void	get_content(t_cube *cube, char *map_fd);

// map.c
void	get_map(t_cube *cube, char *map_fd);
void	map_error(t_cube *cube, int fd, char *error_msg);

// textures.c
int		is_texture_identifier(const char *line);
void	purge_textures(t_cube *cube);
void	set_texture(t_cube *cube, int fd, char *line);

#endif