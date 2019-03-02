/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 18:40:59 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/03 18:41:01 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *hay, const char *ndl)
{
	int i;
	int j;

	if (*ndl == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == ndl[j])
		{
			if (ndl[j + 1] == '\0')
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
