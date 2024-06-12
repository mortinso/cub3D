/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:45:13 by mortins-          #+#    #+#             */
/*   Updated: 2024/06/12 16:14:48 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Converts the initial portion of the string 's' to int

int	ft_atoi(const char *s)
{
	int	num;
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	num = 0;
	while ((s[i] >= '\t' && s[i] <= '\r') || s[i] == ' ')
		i++;
	if (s[i] == '-')
		neg = -1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		num = (num * 10) + (s[i] - '0');
		i++;
	}
	return (num * neg);
}
