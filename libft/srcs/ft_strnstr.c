/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:44:44 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/03 19:44:45 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	size_t	i;
	int		j;

	if (*ndl == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i] && i < len)
	{
		j = 0;
		while (hay[i + j] == ndl[j])
		{
			if (ndl[j + 1] == '\0' && (i + j) < len)
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
