/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:26:55 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/25 18:26:57 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int			res_len(t_pf *pf, char *str)
{
	int			rlen;
	int			nlen;

	nlen = ft_strlen(str);
	rlen = nlen;
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

static void			apply_specs(t_pf *pf, char *str, char *res, int rlen)
{
	int			i;
	int			nlen;

	i = 0;
	nlen = ft_strlen(str);
	(pf->flags[0] == '-' || pf->prec != -1) ? pf->flags[3] = '\0' : 0;
	(pf->flags[3]) ? ft_memset(res, '0', rlen) : ft_memset(res, ' ', rlen);
	if (pf->prec <= nlen && nlen)
		i = pf->flags[0] ? 0 : (rlen - nlen);
	else if (pf->prec > nlen)
	{
		i = pf->flags[0] ? 0 : (rlen - pf->prec);
		while (pf->prec-- > nlen)
			res[i++] = '0';
	}
	while (*str)
		res[i++] = *(str++);
}

void				convert_b(t_pf *pf)
{
	uintmax_t	num;
	char		*str;
	char		*res;
	int			rlen;

	num = uint_length_mod(pf);
	str = pf_itoa_base(num, 2, pf);
	rlen = res_len(pf, str);
	if (!(res = (char *)malloc(sizeof(char) * rlen + 1)))
		return ;
	res[rlen] = '\0';
	apply_specs(pf, str, res, rlen);
	pf->print = pf_strjoin(pf, res);
	free(str);
	free(res);
}
