/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:59:07 by dstepane          #+#    #+#             */
/*   Updated: 2019/01/13 18:59:09 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static void	parse_convers2(t_pf *pf)
{
	char c[2];

	c[1] = '\0';
	c[0] = *pf->fmt;
	pf->print = pf_strjoin(pf, c);
}

void		parse_convers(t_pf *pf)
{
	if (*pf->fmt == '%')
		convert_percent(pf);
	else if (*pf->fmt == 'c')
		convert_c(pf);
	else if (*pf->fmt == 's')
		convert_s(pf);
	else if (*pf->fmt == 'd' || *pf->fmt == 'i' || *pf->fmt == 'D')
		convert_di(pf);
	else if (*pf->fmt == 'u' || *pf->fmt == 'U')
		convert_u(pf);
	else if (*pf->fmt == 'o' || *pf->fmt == 'O')
		convert_o(pf);
	else if (*pf->fmt == 'x' || *pf->fmt == 'X')
		convert_x(pf);
	else if (*pf->fmt == 'p')
		convert_p(pf);
	else if (*pf->fmt == 'f' || *pf->fmt == 'F')
		convert_f(pf);
	else if (*pf->fmt == 'b')
		convert_b(pf);
	else if (*pf->fmt)
		parse_convers2(pf);
}

void		parse_length(t_pf *pf)
{
	if (*pf->fmt == 'h' || *pf->fmt == 'l' || *pf->fmt == 'L' ||
		*pf->fmt == 'j' || *pf->fmt == 'z')
	{
		if (*pf->fmt == 'h' && *(pf->fmt + 1) == 'h')
		{
			pf->len = hh;
			pf->fmt++;
		}
		else if (*pf->fmt == 'h' && *(pf->fmt + 1) != 'h')
			pf->len = h;
		if (*pf->fmt == 'l' && *(pf->fmt + 1) == 'l')
		{
			pf->len = ll;
			pf->fmt++;
		}
		else if (*pf->fmt == 'l' && *(pf->fmt + 1) != 'l')
			pf->len = l;
		if (*pf->fmt == 'L')
			pf->len = L;
		if (*pf->fmt == 'j')
			pf->len = j;
		(*pf->fmt == 'z') ? pf->len = z : 0;
		pf->fmt++;
	}
	parse_convers(pf);
}

void		parse_fwid_prec(t_pf *pf)
{
	while (ft_isdigit(*pf->fmt))
		pf->width = pf->width * 10 + (*pf->fmt++ - '0');
	if (*pf->fmt == '.')
	{
		pf->fmt++;
		pf->prec = 0;
		while (ft_isdigit(*pf->fmt))
			pf->prec = pf->prec * 10 + (*pf->fmt++ - '0');
	}
	parse_length(pf);
}

void		parse_flags(t_pf *pf)
{
	while (pf->fmt && (*pf->fmt == '-' || *pf->fmt == '+' || *pf->fmt == ' ' ||
		*pf->fmt == '0' || *pf->fmt == '#'))
	{
		if (*pf->fmt == '-')
			pf->flags[0] = '-';
		else if (*pf->fmt == '+')
			pf->flags[1] = '+';
		else if (*pf->fmt == ' ')
			pf->flags[2] = ' ';
		else if (*pf->fmt == '0')
			pf->flags[3] = '0';
		else if (*pf->fmt == '#')
			pf->flags[4] = '#';
		pf->fmt++;
	}
	parse_fwid_prec(pf);
}
