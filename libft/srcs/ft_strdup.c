/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:25:13 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/01 20:25:26 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	i = 0;
	while (s1[i])
		i++;
	cpy = (char *)malloc(i + 1);
	if (cpy == 0)
		return (0);
	cpy[i] = '\0';
	while (i >= 0)
	{
		cpy[i] = s1[i];
		i--;
	}
	return (cpy);
}
