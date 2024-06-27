/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:19:27 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/27 18:01:56 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// Function that returns the number of the line where the map starts
int	find_map(t_cube *cube, char *map_fd)
{
	char	*line;
	int		pos;
	int		fd;

	fd = open(map_fd, O_RDONLY);
	if (fd < 0)
		map_error(cube, -1, "Failed to open map file");
	pos = 0;
	line = get_next_line(fd);
	if (!line)
		map_error(cube, fd, "Map file is empty");
	while (line)
	{
		if (!is_texture_identifier(line) && ft_strchr("01NSEW ", line[0]))
			break ;
		pos++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (pos);
}

void	map_dup(t_cube *cube, int fd, int pos)
{
	char	*line; // Could this be replaceable with cube->map[i]?
	int		i;

	if (fd < 0)
		map_error(cube, -1, "Failed to open map file");
	i = 0;
	line = get_next_line(fd);
	if (!line)
		map_error(cube, fd, "Map file is empty");
	while (line)
	{
		if (i >= pos)
			cube->map[i - pos] = ft_strdup(line);
		if (i >= pos && cube->map[i - pos][ft_strlen(cube->map[i - pos]) - 1] == '\n')
			cube->map[i - pos][ft_strlen(cube->map[i - pos]) - 1] = 0;
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cube->map[i - pos] = NULL;
}

// Allocates to the struct, a char** where the map will be stored
void	alloc_map(t_cube *cube, char *map_fd, int map_pos)
{
	char	*line;
	int		i;
	int		fd;

	fd = open(map_fd, O_RDONLY);
	if (fd < 0)
		map_error(cube, -1, "Failed to open map file");
	i = 0;
	line = get_next_line(fd);
	if (!line)
		map_error(cube, fd, "Map file is empty");
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	cube->map = (char **)malloc(sizeof(char *) * (i - map_pos + 1));
	if (!cube->map)
		map_error(cube, fd, "Malloc error");
	cube->map_size = i - map_pos;
	close(fd);
}


void	save_map(t_cube *cube, char *map_fd)
{
	int	fd;
	int	map_pos;

	map_pos = find_map(cube, map_fd);
	alloc_map(cube, map_fd, map_pos);
	fd = open(map_fd, O_RDONLY);
	map_dup(cube, fd, map_pos);
	close(fd);
	//Missing all checks


	// Debug:
	int i = 0;
	ft_printf("Map:\n");
	while (i < cube->map_size)
		ft_printf("%s\n", cube->map[i++]);
}
