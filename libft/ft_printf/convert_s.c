/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:20:50 by dstepane          #+#    #+#             */
/*   Updated: 2019/01/25 19:20:53 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static int	s_position_crutch(int width, int len)
{
	return ((width - len) > 0 ? (width - len) : 0);
}

void		convert_s(t_pf *pf)
{
	char	*str;
	char	*res;
	int		len;

	str = va_arg(pf->args, char*);
	if (str == NULL)
		str = "(null)";
	(pf->prec > -1 && pf->prec < (int)ft_strlen(str)) ? (len = pf->prec) :
		(len = ft_strlen(str));
	pf->width > len ? (res = ft_strnew(pf->width)) :
		(res = ft_strnew(len));
	if (pf->width)
	{
		(pf->flags[3] == '0' && !pf->flags[0]) ?
			ft_memset(res, '0', pf->width) : ft_memset(res, ' ', pf->width);
		pf->flags[0] == '-' ? ft_memmove(res, str, len) :
			ft_strncpy(&res[s_position_crutch(pf->width, len)], str, len);
		pf->print = pf_strjoin(pf, res);
	}
	else
	{
		ft_strncpy(res, str, len);
		pf->print = pf_strjoin(pf, res);
	}
	free(res);
}
