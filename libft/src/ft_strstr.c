/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:54:47 by wiferrei          #+#    #+#             */
/*   Updated: 2024/09/04 15:55:15 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strstr(const char *str, const char *cmp)
{
	size_t	i;
	size_t	j;

	if (!*cmp)
		return ((char *)str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == cmp[j] && cmp[j])
			j++;
		if (!cmp[j])
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
