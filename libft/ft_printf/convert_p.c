/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 13:05:56 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/16 13:05:58 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int			res_len(t_pf *pf, char *str)
{
	int			rlen;

	rlen = ft_strlen(str);
	rlen += 2;
	if (pf->width > rlen && pf->width > pf->prec)
		rlen = pf->width;
	else if (pf->prec > rlen && pf->prec >= pf->width)
		rlen = pf->prec + 2;
	if (str[0] == '0' && !str[1] && pf->prec == 0)
	{
		if (!pf->width)
			return (2);
		else
			return (rlen);
	}
	return (rlen);
}

static void			apply_zerox(t_pf *pf, char *res, int *i, char *str)
{
	int			rlen;
	int			nlen;

	rlen = ft_strlen(res);
	nlen = ft_strlen(str);
	if (nlen == 0)
		return ;
	if (!pf->flags[0] && pf->prec > nlen)
		*i = (rlen - pf->prec - 2);
	else if (!pf->flags[0] && !pf->flags[3] && rlen > (nlen + 2))
		*i = (rlen - nlen - 2);
	else
		*i = 0;
	res[(*i)++] = '0';
	res[(*i)++] = (*pf->fmt == 'X') ? 'X' : 'x';
}

static void			apply_specs(t_pf *pf, char *str, char *res, int rlen)
{
	int			i;
	int			nlen;

	i = 0;
	nlen = ft_strlen(str);
	(pf->flags[3] == '0' && !pf->flags[0] && pf->prec == -1) ?
		ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	apply_zerox(pf, res, &i, str);
	if (!pf->prec && str[0] == '0' && !str[1])
		return ;
	if (pf->prec <= nlen && nlen)
		(pf->flags[0] == '-') ? 0 : (i = (rlen - nlen));
	else if (pf->prec > nlen)
	{
		(pf->flags[0] == '-') ? 0 : (i = (rlen - pf->prec));
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	while (*str)
		res[i++] = *(str++);
}

void				convert_p(t_pf *pf)
{
	uintmax_t	num;
	char		*str;
	char		*res;
	int			rlen;

	num = (unsigned long)(va_arg(pf->args, unsigned long int));
	str = pf_itoa_base(num, 16, pf);
	rlen = res_len(pf, str);
	if (!(res = (char *)malloc(sizeof(char) * rlen + 1)))
		return ;
	res[rlen] = '\0';
	apply_specs(pf, str, res, rlen);
	pf->print = pf_strjoin(pf, res);
	free(str);
	free(res);
}
