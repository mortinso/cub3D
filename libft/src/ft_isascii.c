/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:15:17 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:15:22 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Checks if it was given a char value that fits in the ASCII character set

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
