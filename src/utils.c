/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:20:53 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/14 16:48:19 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

// Returns the size of an array
size_t	array_size(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

// Frees an array
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

// Uses ft_isdigit()on all members of a char* in order to check if its only
// comprised of digits
int	is_all_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (0);
	}
	return (1);
}
