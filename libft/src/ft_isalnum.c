/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:58:40 by mortins-          #+#    #+#             */
/*   Updated: 2024/08/06 20:32:25 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

//	Checks if it was given an alphanumeric character

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
