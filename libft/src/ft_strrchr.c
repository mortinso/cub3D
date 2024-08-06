/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:59:04 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:55 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Returns a pointer to the last occurrence of the character 'c'
//	in the string 's'

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen(s);
	while (a >= 0)
	{
		if (s[a] == (char)c)
			return ((char *)s + a);
		a--;
	}
	return (NULL);
}
