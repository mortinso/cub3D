/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:23:00 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:56 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Locates the first occurrence of the string 'lil' in the string 'big'
//	No more than 'n' characters are searched

char	*ft_strnstr(const char *big, const char *lil, size_t n)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (!lil[0])
		return ((char *)big);
	if ((int)n < 0)
		n = ft_strlen(big);
	while (b < n && big[b])
	{
		l = 0;
		while (big[b] && big[b] != lil[l])
			b++;
		while (big[b + l] && big[b + l] == lil[l] && b + l < n)
		{
			if (lil[l + 1] == '\0')
				return ((char *)big + (b));
			l++;
		}
		b++;
	}
	return (0);
}
