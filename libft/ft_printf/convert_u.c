/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 16:51:30 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/13 16:51:31 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

uintmax_t		uint_length_mod(t_pf *pf)
{
	uintmax_t	num;

	num = 0;
	(*pf->fmt == 'U' || *pf->fmt == 'O') ? pf->len = l : 0;
	if (pf->len == no)
		num = (unsigned int)(va_arg(pf->args, unsigned int));
	else if (pf->len == hh)
		num = (unsigned char)(va_arg(pf->args, unsigned int));
	else if (pf->len == h)
		num = (unsigned short)(va_arg(pf->args, unsigned int));
	else if (pf->len == l)
		num = (unsigned long)(va_arg(pf->args, unsigned long int));
	else if (pf->len == ll)
		num = (unsigned long long)(va_arg(pf->args, unsigned long long int));
	else if (pf->len == j)
		num = (uintmax_t)(va_arg(pf->args, uintmax_t));
	else if (pf->len == z)
		num = (size_t)(va_arg(pf->args, size_t));
	return (num);
}

static int		num_len(uintmax_t num)
{
	int			nlen;

	nlen = 1;
	while (num /= 10)
		nlen++;
	return (nlen);
}

static int		res_len(t_pf *pf, uintmax_t num)
{
	int			rlen;

	(num == 0 && pf->prec == 0) ? rlen = 0 :
		(rlen = num_len(num));
	if (pf->width > rlen && pf->width > pf->prec)
		rlen = pf->width;
	else if (pf->prec > rlen && pf->prec >= pf->width)
		rlen = pf->prec;
	return (rlen);
}

static void		apply_specs(t_pf *pf, uintmax_t num, char *res, int rlen)
{
	int			nlen;
	int			i;

	(num == 0 && pf->prec == 0) ? (nlen = 0) :
		(nlen = num_len(num));
	i = 0;
	(pf->flags[3] == '0' && !pf->flags[0] && pf->prec == -1) ?
		ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	if (pf->prec <= nlen && nlen)
		(pf->flags[0] == '-') ? (i = 0) :
			(i = (rlen - nlen));
	else if (pf->prec > nlen && nlen)
	{
		(pf->flags[0] == '-') ? (i = 0) :
			(i = (rlen - pf->prec));
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	while (nlen--)
	{
		res[i + nlen] = (num % 10) + '0';
		num /= 10;
	}
}

void			convert_u(t_pf *pf)
{
	uintmax_t	num;
	char		*res;
	int			rlen;

	num = uint_length_mod(pf);
	rlen = res_len(pf, num);
	if (!(res = (char *)malloc(sizeof(char) * rlen + 1)))
		return ;
	res[rlen] = '\0';
	apply_specs(pf, num, res, rlen);
	pf->print = pf_strjoin(pf, res);
	free(res);
}
