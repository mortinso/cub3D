/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:20:39 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:14:58 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Erases the data in the first 'n' bytes of the memory starting at the
//	location pointed to by 's'

void	ft_bzero(void *s, size_t n)
{
	char	*buff;

	buff = (char *)s;
	while (n--)
		buff[n] = 0;
}
