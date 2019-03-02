/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:59:04 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/25 16:59:06 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	FORMATTING:
**	{0} - Normal Text - Reset all attributes
**	{b} - Bold/Bright
**	{d} - Dim
**	{u} - Underlined
** 	{i} - italic
** 	{I} - inverted
**
**	TEXT COLORS:
**	{-}	- default
**	{red}
**	{blue}
**	{green}
**	{yellow}
**	{magenta}
**	{cyan}
**	{black}
**	{white}
**	{lightgray}
**	{darkgray}
**
**	BACKGROUND COLORS:
**	{_}	- default
**	{_*}		- where * is the same as text colors.
*/

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static void		style2(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{u}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[4m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{i}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[3m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{I}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[7m\0");
		pf->fmt += 2;
		return ;
	}
	else
		text_colors(pf);
}

void			style(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{0}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[0m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{b}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[1m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{d}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[2m\0");
		pf->fmt += 2;
		return ;
	}
	else
		style2(pf);
}
