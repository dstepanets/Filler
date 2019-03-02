/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 17:57:00 by dstepane          #+#    #+#             */
/*   Updated: 2018/10/27 17:57:02 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*buf;
	size_t			i;

	i = 0;
	buf = (unsigned char *)s;
	if (n == 0)
		return ;
	while (i < n)
		buf[i++] = '\0';
}
