/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:13:57 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/10 17:14:01 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int			res_len(t_pf *pf, intmax_t num)
{
	int			rlen;

	(num == 0 && pf->prec == 0) ? (rlen = 0) :
		(rlen = di_num_len(num));
	if (pf->width || pf->prec > -1)
	{
		if (pf->width > rlen && pf->width > pf->prec)
			rlen = pf->width;
		else if (pf->prec > rlen && pf->prec >= pf->width)
		{
			rlen = pf->prec;
			(num < 0 || pf->flags[2] == ' ' || pf->flags[1]) ? rlen++ : 0;
		}
		else
			(num < 0 || pf->flags[2] || pf->flags[1] == '+') ? rlen++ : 0;
	}
	else
		(num < 0 || pf->flags[2] == ' ' || pf->flags[1] == '+') ? rlen++ : 0;
	return (rlen);
}

static void			write_num(char *res, intmax_t num, int nlen, int i)
{
	num < 0 ? num *= -1 : 0;
	while (nlen--)
	{
		res[i + nlen] = (num % 10) + '0';
		num /= 10;
	}
}

static void			apply_sign(t_pf *pf, char *res, intmax_t num, int rlen)
{
	int			nlen;
	int			i;

	(num == 0 && pf->prec == 0) ? (nlen = 0) :
		(nlen = di_num_len(num));
	if (pf->flags[0] || (pf->flags[3] && pf->prec <= nlen))
		i = 0;
	else if (!pf->flags[0] && pf->prec <= nlen)
		i = rlen - nlen - 1;
	else if (!pf->flags[0] && pf->prec > nlen)
		i = rlen - pf->prec - 1;
	if (num < 0)
		res[i] = '-';
	else if (pf->flags[1] == '+')
		res[i] = '+';
	else if (pf->flags[2] == ' ')
		res[i] = ' ';
}

static void			apply_specs(t_pf *pf, intmax_t num, char *res, int rlen)
{
	int			nlen;
	int			i;
	int			s;

	(num == 0 && pf->prec == 0) ? (nlen = 0) :
		(nlen = di_num_len(num));
	i = 0;
	s = 0;
	(pf->flags[0] == '-' || pf->prec != -1) ? pf->flags[3] = '\0' : 0;
	(pf->flags[3]) ? ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	if (num < 0 || pf->flags[2] == ' ' || pf->flags[1] == '+')
	{
		apply_sign(pf, res, num, rlen);
		s = 1;
	}
	if (pf->prec <= nlen)
		(pf->flags[0] == '-') ? (i += s) : (i = (rlen - nlen));
	else if (pf->prec > nlen)
	{
		(pf->flags[0] == '-') ? (i += s) : (i = (rlen - pf->prec));
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	write_num(res, num, nlen, i);
}

void				convert_di(t_pf *pf)
{
	intmax_t	num;
	char		*res;
	int			rlen;

	num = int_length_mod(pf);
	if (num == LONG_MIN)
	{
		pf->print = pf_strjoin(pf, ft_strdup("-9223372036854775808"));
		return ;
	}
	rlen = res_len(pf, num);
	if (!(res = (char *)malloc(sizeof(char) * rlen + 1)))
		return ;
	res[rlen] = '\0';
	apply_specs(pf, num, res, rlen);
	pf->print = pf_strjoin(pf, res);
	free(res);
}
