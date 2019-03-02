/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 16:57:43 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/07 16:57:45 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s)
	{
		if (!(sub = (char *)malloc(len + 1)))
			return (NULL);
		i = 0;
		while (s[start] && i < len)
		{
			sub[i] = s[start];
			i++;
			start++;
		}
		sub[len] = '\0';
		return (sub);
	}
	return (NULL);
}
