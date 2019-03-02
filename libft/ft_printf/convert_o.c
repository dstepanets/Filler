/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 19:30:45 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/13 19:30:46 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int			res_len(t_pf *pf, char *str)
{
	int			rlen;

	if (str[0] == '0' && !str[1])
	{
		(pf->flags[4] || pf->prec == 0) ? (str[0] = '\0') : 0;
		str[1] = '\0';
	}
	rlen = ft_strlen(str);
	if (pf->flags[4] == '#' && rlen >= pf->width && rlen >= pf->prec)
		rlen++;
	else if (pf->width > rlen && pf->width > pf->prec)
		rlen = pf->width;
	else if (pf->prec > rlen && pf->prec >= pf->width)
		rlen = pf->prec;
	return (rlen);
}

static void			apply_specs(t_pf *pf, char *str, char *res, int rlen)
{
	int			i;
	int			z;
	int			nlen;

	i = 0;
	z = 0;
	nlen = ft_strlen(str);
	(pf->flags[0] == '-' || pf->prec != -1) ? pf->flags[3] = '\0' : 0;
	(pf->flags[3]) ? ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	if (pf->flags[4] == '#' && !pf->flags[3])
	{
		pf->flags[0] ? (res[0] = '0') :
			(res[rlen - nlen - 1] = '0');
		z = 1;
	}
	if (pf->prec <= nlen && nlen)
		i = pf->flags[0] ? (i + z) : (rlen - nlen);
	else if (pf->prec > nlen)
	{
		i = pf->flags[0] ? 0 : (rlen - pf->prec);
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	while (*str)
		res[i++] = *(str++);
}

void				convert_o(t_pf *pf)
{
	uintmax_t	num;
	char		*str;
	char		*res;
	int			rlen;

	num = uint_length_mod(pf);
	str = pf_itoa_base(num, 8, pf);
	rlen = res_len(pf, str);
	if (!(res = (char *)malloc(sizeof(char) * rlen + 1)))
		return ;
	res[rlen] = '\0';
	apply_specs(pf, str, res, rlen);
	pf->print = pf_strjoin(pf, res);
	free(str);
	free(res);
}
