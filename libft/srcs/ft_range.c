/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:35:24 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/15 16:35:25 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		*ft_range(int min, int max)
{
	int	i;
	int	*rng;

	i = 0;
	if (min >= max)
		return (NULL);
	rng = (int*)malloc(sizeof(*rng) * (max - min));
	while (min < max)
	{
		rng[i] = min;
		min++;
		i++;
	}
	return (rng);
}
