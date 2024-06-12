/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:40:31 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:17:14 by mortins-         ###   ########.fr       */
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
