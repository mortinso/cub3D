/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:03:55 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:41 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Compares the first 'n' bytes of the memory areas 's1' and 's2'

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (st1[i] == st2[i] && i < (n - 1))
		i++;
	return (st1[i] - st2[i]);
}
