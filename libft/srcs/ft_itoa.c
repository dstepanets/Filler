/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:02:15 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/09 14:02:17 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_negative(int *n, int *neg)
{
	if (*n < 0)
	{
		*neg = 1;
		*n = -*n;
	}
}

char		*ft_itoa(int n)
{
	int		nbr;
	int		len;
	int		neg;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = n;
	len = 1;
	while (nbr /= 10)
		len++;
	neg = 0;
	ft_negative(&n, &neg);
	len += neg;
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len] = '\0';
	while (len--)
	{
		res[len] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
