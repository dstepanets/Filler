/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:59:10 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/25 16:59:12 by dstepane         ###   ########.fr       */
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

static void		text_colors4(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{lightgray}", 11))
	{
		pf->print = pf_strjoin(pf, "\x1B[37m\0");
		pf->fmt += 10;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{darkgray}", 10))
	{
		pf->print = pf_strjoin(pf, "\x1B[90m\0");
		pf->fmt += 9;
		return ;
	}
	else
		background_colors(pf);
}

static void		text_colors3(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{cyan}", 6))
	{
		pf->print = pf_strjoin(pf, "\x1B[36m\0");
		pf->fmt += 5;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{black}", 7))
	{
		pf->print = pf_strjoin(pf, "\x1B[30m\0");
		pf->fmt += 6;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{white}", 7))
	{
		pf->print = pf_strjoin(pf, "\x1B[97m\0");
		pf->fmt += 6;
		return ;
	}
	else
		text_colors4(pf);
}

static void		text_colors2(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{green}", 7))
	{
		pf->print = pf_strjoin(pf, "\x1B[32m\0");
		pf->fmt += 6;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{yellow}", 8))
	{
		pf->print = pf_strjoin(pf, "\x1B[33m\0");
		pf->fmt += 7;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{magenta}", 9))
	{
		pf->print = pf_strjoin(pf, "\x1B[35m\0");
		pf->fmt += 8;
		return ;
	}
	else
		text_colors3(pf);
}

void			text_colors(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{-}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[39m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{red}", 5))
	{
		pf->print = pf_strjoin(pf, "\x1B[31m\0");
		pf->fmt += 4;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{blue}", 6))
	{
		pf->print = pf_strjoin(pf, "\x1B[34m\0");
		pf->fmt += 5;
		return ;
	}
	else
		text_colors2(pf);
}
