/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:31:01 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/19 17:25:01 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
}	t_img;

typedef struct s_textures {
	t_img			north;
	t_img			south;
	t_img			east;
	t_img			west;
	unsigned int	c_ceil;
	unsigned int	c_floor;
}	t_textures;

typedef struct s_cube {
	void		*mlx;
	void		*window;
	t_textures	textures;
	t_img		screen;
}	t_cube;

void	get_map(t_cube *cube, char *fd_map);

// utils.c
void	free_array(char **array);
int		is_all_digit(const char *str);

#endif