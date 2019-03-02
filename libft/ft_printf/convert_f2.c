/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:09:20 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/28 15:09:21 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

long double		fl_round_num(intmax_t i, long double num)
{
	long double	roun;
	long double	pr;

	num = num < 0 ? -num : num;
	if (num == 0.0)
		return (0.0);
	pr = 1;
	while (i--)
		pr *= 10;
	roun = (num * pr + 0.5);
	roun /= pr;
	return (roun);
}

void			fl_res_len(t_pf *pf, t_fl *fl)
{
	fl->nlen = ft_strlen(fl->left) + pf->prec;
	(pf->prec != 0 || pf->flags[4] == '#') ? fl->nlen++ : 0;
	fl->rlen = fl->nlen;
	(fl->num < 0 || pf->flags[2] == ' ' || pf->flags[1] == '+') ?
		fl->rlen++ : 0;
	(pf->width > fl->rlen) ? fl->rlen = pf->width : 0;
}

int				infnan(t_pf *pf, t_fl *fl)
{
	if ((fl->num == 1.0 / 0.0) || (fl->num == -1.0 / 0.0) ||
		(fl->num != fl->num))
	{
		free(fl->left);
		if ((fl->num == 1.0 / 0.0) || (fl->num == -1.0 / 0.0))
			(*pf->fmt == 'F') ? (fl->left = ft_strdup("INF")) :
				(fl->left = ft_strdup("inf"));
		else if (fl->num != fl->num)
		{
			(*pf->fmt == 'F') ? (fl->left = ft_strdup("NAN")) :
				(fl->left = ft_strdup("nan"));
			pf->flags[1] = '\0';
			pf->flags[2] = '\0';
		}
		ft_bzero(fl->right, pf->prec);
		pf->prec = 0;
		pf->flags[3] = '\0';
		pf->flags[4] = '\0';
		return (1);
	}
	return (0);
}
