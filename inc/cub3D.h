/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:31:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/07/27 11:08:14 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_W 1280
# define SCREEN_H 720

//----------------------------------INCLUDES------------------------------------
// # include "../minilibx-linux/mlx.h" // For 42 pcs
# include <mlx.h> // for my pc
# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define PI 3.1415926535

# define GRID_CELL 16 //for 2D view
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
} t_player;

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
}	t_cube;

//------------------------------------SRCS--------------------------------------
// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// events.c
int		destruct(t_cube *cube);
int		keypress(int key, t_cube *cube);

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