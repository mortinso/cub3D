/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Returns a pointer to a new string duplicated from the string 's'

char	*ft_strdup(const char *s)
{
	char	*buff;

	buff = (char *) malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!buff)
		return (NULL);
	ft_strlcpy(buff, s, ft_strlen(s) + 1);
	return (buff);
}
