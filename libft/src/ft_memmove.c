/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:57:16 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:41 by mortins-         ###   ########.fr       */
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
