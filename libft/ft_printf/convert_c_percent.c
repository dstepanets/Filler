/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 19:37:41 by dstepane          #+#    #+#             */
/*   Updated: 2019/01/26 19:37:45 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

void			convert_percent(t_pf *pf)
{
	unsigned char	res[pf->width + 2];

	if (pf->width)
	{
		res[pf->width] = '\0';
		pf->flags[3] == '0' && !pf->flags[0] ?
			ft_memset(res, '0', pf->width) :
			ft_memset(res, ' ', pf->width);
		if (pf->flags[0] == '-')
			res[0] = '%';
		else
			res[pf->width - 1] = '%';
	}
	else
	{
		res[1] = '\0';
		res[0] = '%';
	}
	pf->print = pf_strjoin(pf, (char *)res);
}

static void		null_char_helper(t_pf *pf)
{
	char	*leakfix;

	leakfix = pf->print;
	ft_putstr(pf->print);
	if (*pf->print)
		free(pf->print);
	pf->print = ft_strnew(1);
	pf->width ? pf->ret += pf->width : pf->ret++;
	if (!pf->width)
		write(1, "\0", 1);
	else if ((pf->width && !pf->flags[0]))
	{
		while (pf->width-- > 1)
			write(1, " ", 1);
		write(1, "\0", 1);
	}
	else if ((pf->width && pf->flags[0] == '-'))
	{
		write(1, "\0", 1);
		while (pf->width-- > 1)
			write(1, " ", 1);
	}
}

void			convert_c(t_pf *pf)
{
	unsigned char	res[pf->width + 2];
	va_list			args2;

	va_copy(args2, pf->args);
	if (va_arg(args2, int) == '\0')
	{
		null_char_helper(pf);
		return ;
	}
	if (pf->width)
	{
		res[pf->width] = '\0';
		pf->flags[3] == '0' && !pf->flags[0] ?
			ft_memset(res, '0', pf->width) : ft_memset(res, ' ', pf->width);
		(pf->flags[0] == '-') ? (res[0] = va_arg(pf->args, int)) :
			(res[pf->width - 1] = va_arg(pf->args, int));
	}
	else
	{
		res[1] = '\0';
		res[0] = va_arg(pf->args, int);
	}
	pf->print = pf_strjoin(pf, (char *)res);
	va_end(args2);
}
