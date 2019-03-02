/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 20:50:36 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/14 20:50:40 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrev(char *str)
{
	int		l;
	int		i;
	char	t;

	l = 0;
	i = 0;
	while (str[l])
		l++;
	l--;
	while (i < l)
	{
		t = str[l];
		str[l] = str[i];
		str[i] = t;
		i++;
		l--;
	}
	return (str);
}
