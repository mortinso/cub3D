/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:14:48 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/28 18:38:44 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Errors if the map has any forbidden characters and empty lines or a wrong
// number of player starting positions
void	map_chars(t_cube *cube)
{
	int	player;
	int	i;
	int	j;

	i = 0;
	player = 0;
	while (i < cube->map.size)
	{
		j = 0;
		if (!cube->map.map[i][j])
			map_error(cube, -1, "Empty line found in the middle of the map");
		while (j < (int)ft_strlen(cube->map.map[i]))
		{
			if (!ft_strchr("01NSEW ", cube->map.map[i][j]))
				map_error(cube, -1, "Invalid character in map content");
			if (ft_strchr("NSEW", cube->map.map[i][j++]))
				player++;
		}
		i++;
	}
	if (player == 0)
		map_error(cube, -1, "No player starting position in map");
	if (player > 1)
		map_error(cube, -1, "Multiple player starting positions found");
}
