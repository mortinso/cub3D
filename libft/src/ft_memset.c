/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:32:18 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:42 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Fills the first 'n' bytes of the memory area 's' with 'c'

void	*ft_memset(void *s, int c, size_t n)
{
	char	*buff;

	buff = (char *)s;
	while (n--)
		buff[n] = c;
	return (s);
}
