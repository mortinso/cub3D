/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:31:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/09/02 20:21:14 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_W 1920
# define SCREEN_H 1080

//----------------------------------INCLUDES------------------------------------
# include <stdio.h>
// # include "../minilibx-linux/mlx.h" // For 42 pcs
# include <mlx.h> // for my pc
# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.1415926535
# define RAD_DEGREE 0.0174533
# define CELL 64

// v-------- 2Dview -------v
# define FOV 90
# define P_SIZE 15 //2D
# define P_COLOR 0x00ff0000
# define A_COLOR 0x00ffff00

//------------------------------------KEYS--------------------------------------
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ARROW_LEFT 65361
# define KEY_ARROW_RIGHT 65363

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

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_textures
{
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		c_ceil;
	int		c_floor;
}	t_textures;

typedef struct s_raycast
{
	t_vector	line_dist;
	t_vector	delta_dist;
	t_vector	ray_dir;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			orientation;
	double		wall_dist;
	double		win_x;
}	t_raycast;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		size;
}	t_map;

typedef struct s_cube
{
	void		*mlx;
	void		*game_window;
	void		*window_2;
	t_map		map;
	t_textures	textures;
	t_img		game;
	t_img		minimap;
	t_raycast	raycast;
	t_player	player;
}	t_cube;

//------------------------------------SRCS--------------------------------------
// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// minimap.c
void	put_texture(t_cube *cube, t_img *texture, int screen_x, int screen_y);
void	draw_cell(t_cube *cube, int x, int y, unsigned int color);
void	draw_square(t_cube *cube, int side, t_vector vect, unsigned int color);
void	draw_angle(t_cube *cube, t_vector delta, unsigned int color);
void	draw_fov(t_cube *cube);

// events.c
int		destruct(t_cube *cube);
int		keypress(int key, t_cube *cube);

// init.c
void	init(t_cube *cube, char *map_fd);

// main.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

// utils.c
size_t	array_size(char **array);
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

// +++++++++++++++ raycasting/[.....] +++++++++++++++++++++++++++++++++++++++++
// drawing.c
void	draw_wall(t_cube *cube, t_raycast *cast, int x);
void	draw_floor(t_cube *cube);

// raycasting.c
void	raycasting(t_cube *cube, t_raycast *cast, t_vector dir);

#endif