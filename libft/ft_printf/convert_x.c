/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 15:01:49 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/15 15:01:50 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int			res_len(t_pf *pf, char *str)
{
	int		rlen;
	int		nlen;

	nlen = ft_strlen(str);
	rlen = nlen;
	if (pf->flags[4] == '#' && !(str[0] == '0' && !str[1]))
		rlen = nlen + 2;
	if (pf->prec > nlen)
		rlen += (pf->prec - nlen);
	if (pf->width > rlen)
		rlen = pf->width;
	if (str[0] == '0' && !str[1] && pf->prec == 0)
	{
		(str[0] = '\0');
		if (!pf->width)
			return (0);
		else
			return (rlen);
	}
	return (rlen);
}

static void			apply_zerox(t_pf *pf, char *res, int i, int nlen)
{
	int			rlen;

	rlen = ft_strlen(res);
	if (nlen == 0)
		return ;
	if (!pf->flags[0] && pf->prec > nlen)
		i = (rlen - pf->prec - 2);
	else if (!pf->flags[0] && !pf->flags[3] && rlen > (nlen + 2))
		i = (rlen - nlen - 2);
	else
		i = 0;
	res[i++] = '0';
	res[i] = (*pf->fmt == 'X') ? 'X' : 'x';
}

static void			apply_specs(t_pf *pf, char *str, char *res, int rlen)
{
	int		i;
	int		z;
	int		nlen;

	i = 0;
	z = 0;
	nlen = ft_strlen(str);
	(pf->flags[0] == '-' || pf->prec != -1) ? pf->flags[3] = '\0' : 0;
	(pf->flags[3]) ? ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	if (pf->flags[4] == '#' && !(str[0] == '0' && !str[1]))
	{
		apply_zerox(pf, res, i, nlen);
		z = 2;
	}
	if (pf->prec <= nlen && nlen)
		(pf->flags[0] == '-') ? (i += z) : (i = (rlen - nlen));
	else if (pf->prec > nlen)
	{
		(pf->flags[0] == '-') ? i += z : (i = (rlen - pf->prec));
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	while (*str)
		res[i++] = *(str++);
}

void				convert_x(t_pf *pf)
{
	uintmax_t	num;
	char		*str;
	char		*res;
	int			rlen;

	num = uint_length_mod(pf);
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
