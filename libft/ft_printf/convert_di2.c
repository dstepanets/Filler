/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 20:46:36 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/27 20:46:37 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

int			di_num_len(intmax_t num)
{
	int			nlen;

	nlen = 1;
	while (num /= 10)
		nlen++;
	return (nlen);
}

intmax_t	int_length_mod(t_pf *pf)
{
	intmax_t	num;

	num = 0;
	*pf->fmt == 'D' ? pf->len = l : 0;
	if (pf->len == no)
		num = (int)(va_arg(pf->args, int));
	else if (pf->len == hh)
		num = (signed char)(va_arg(pf->args, int));
	else if (pf->len == h)
		num = (short)(va_arg(pf->args, int));
	else if (pf->len == l)
		num = (long)(va_arg(pf->args, long int));
	else if (pf->len == ll)
		num = (long long)(va_arg(pf->args, long long int));
	else if (pf->len == j)
		num = (intmax_t)(va_arg(pf->args, intmax_t));
	else if (pf->len == z)
		num = (size_t)(va_arg(pf->args, size_t));
	return (num);
}
