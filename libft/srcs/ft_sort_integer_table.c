/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:46:20 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/15 15:46:21 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_sort_integer_table(int *tab, int size)
{
	int i;
	int t;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			t = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = t;
			i = 0;
		}
		else
			i++;
	}
}
