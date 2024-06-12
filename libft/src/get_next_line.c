/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:18:57 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 18:05:00 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*get_strjoin(char *line, const char *box)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(box) + 1));
	if (!new)
		return (NULL);
	while (line && line[i])
	{
		new[i] = line[i];
		i++;
	}
	while (*box)
	{
		new[i++] = *box;
		if (*box++ == '\n')
			break ;
	}
	new[i] = 0;
	free (line);
	return (new);
}

int	check_newline(char *box)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (box[i])
	{
		if (n)
			box[j++] = box[i];
		if (box[i] == '\n')
			n = 1;
		box[i++] = 0;
	}
	return (n);
}

char	*get_next_line(int fd)
{
	static char	box[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	if (read(fd, NULL, 0) < 0)
	{
		while (box[i])
			box[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (box[0] || read(fd, box, BUFFER_SIZE))
	{
		line = get_strjoin(line, box);
		if (check_newline(box))
			break ;
	}
	return (line);
}
