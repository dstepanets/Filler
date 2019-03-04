/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 16:00:01 by dstepane          #+#    #+#             */
/*   Updated: 2018/12/25 16:00:09 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static void			reset_specs(t_pf *pf)
{
	ft_bzero(pf->flags, 5);
	pf->width = 0;
	pf->prec = -1;
	pf->len = no;
}

static t_pf			*init_specs(char *fmt)
{
	t_pf		*pf;

	pf = (t_pf *)malloc(sizeof(t_pf));
	pf->fmt = fmt;
	pf->print = ft_strnew(1);
	pf->ret = 0;
	ft_bzero(pf->flags, 5);
	pf->width = 0;
	pf->prec = -1;
	pf->len = no;
	return (pf);
}

static void			parse_format2(t_pf *pf)
{
	reset_specs(pf);
	pf->fmt++;
	parse_flags(pf);
}

static int			parse_format(t_pf *pf)
{
	int		i;
	char	*txt;

	while (*pf->fmt != '\0')
	{
		i = 0;
		while (pf->fmt[i] && pf->fmt[i] != '%' && pf->fmt[i] != '{')
			i++;
		txt = ft_strsub(pf->fmt, 0, i);
		pf->print = pf_strjoin(pf, txt);
		free(txt);
		pf->fmt = &pf->fmt[i];
		txt = pf->fmt;
		if (*pf->fmt == '{')
		{
			style(pf);
			(pf->fmt == txt) ? pf->print = pf_strjoin(pf, "{\0") : 0;
		}
		if (*pf->fmt == '%' && *(pf->fmt + 1))
			parse_format2(pf);
		if (*pf->fmt != '\0')
			pf->fmt++;
	}
	return (pf->ret);
}

int					ft_printf(const char *format, ...)
{
	t_pf		*pf;
	int			ret;

	if (format == NULL)
		return (-1);
	if (!ft_strchr(format, '%') && !ft_strchr(format, '{'))
	{
		ft_putstr(format);
		return (ft_strlen(format));
	}
	pf = init_specs((char *)format);
	ret = 0;
	va_start(pf->args, format);
	ret = parse_format(pf);
	va_end(pf->args);
	ft_putstr(pf->print);
	free(pf->print);
	free(pf);
	return (ret);
}
