/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:49:30 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:16:49 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Outputs the character 'c' to the given file descriptor

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
