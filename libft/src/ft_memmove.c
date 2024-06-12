/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:57:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:16:31 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Copies 'n' bytes from memory area 'src' to memory area 'dest'
//	The memory areas may overlap

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src < dest)
	{
		while (n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
