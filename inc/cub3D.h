/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:31:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/28 17:26:34 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//----------------------------------INCLUDES------------------------------------
// # include "../minilibx-linux/mlx.h" // For 42 pcs
# include <mlx.h> // for my pc
# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <fcntl.h>

//------------------------------------KEYS--------------------------------------
# define KEY_ESC 65307

//-----------------------------------STRUCT-------------------------------------
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures {
	t_img	north;
	t_img	south;
	t_img	east;
	t_img	west;
	int		c_ceil;
	int		c_floor;
}	t_textures;

typedef struct s_map {
	char	**map;
	int		size;
}	t_map;

typedef struct s_cube {
	void		*mlx;
	void		*window;
	t_map		map;
	t_textures	textures;
	t_img		screen;
}	t_cube;

//------------------------------------SRCS--------------------------------------
// +++++++++++++++ ./[.....] ++++++++++++++++++++++++++++++++++++++++++++++++++
// events.c
int				destruct(t_cube *cube);
int				keypress(int key, t_cube *cube);

// utils.c
void			free_array(char **array);
int				is_all_digit(const char *str);

// +++++++++++++++ map/[.....] ++++++++++++++++++++++++++++++++++++++++++++++++
// map_colors.c
void			set_color(t_cube *cube, int fd, char *line);

// map_content.c
void			get_content(t_cube *cube, char *map_fd);

// map_textures
int				is_texture_identifier(const char *line);
void			purge_textures(t_cube *cube);
void			set_texture(t_cube *cube, int fd, char *line);

// map.c
void			get_map(t_cube *cube, char *map_fd);
void			map_error(t_cube *cube, int fd, char *error_msg);

#endif