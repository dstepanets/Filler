/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:59:18 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/25 16:59:20 by dstepane         ###   ########.fr       */
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

static void		background_colors4(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{_lightgray}", 12))
	{
		pf->print = pf_strjoin(pf, "\x1B[47m\0");
		pf->fmt += 11;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_darkgray}", 11))
	{
		pf->print = pf_strjoin(pf, "\x1B[100m\0");
		pf->fmt += 10;
		return ;
	}
	return ;
}

static void		background_colors3(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{_cyan}", 7))
	{
		pf->print = pf_strjoin(pf, "\x1B[46m\0");
		pf->fmt += 6;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_black}", 8))
	{
		pf->print = pf_strjoin(pf, "\x1B[40m\0");
		pf->fmt += 7;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_white}", 8))
	{
		pf->print = pf_strjoin(pf, "\x1B[107m\0");
		pf->fmt += 7;
		return ;
	}
	else
		background_colors4(pf);
}

static void		background_colors2(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{_green}", 8))
	{
		pf->print = pf_strjoin(pf, "\x1B[42m\0");
		pf->fmt += 7;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_yellow}", 9))
	{
		pf->print = pf_strjoin(pf, "\x1B[43m\0");
		pf->fmt += 8;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_magenta}", 10))
	{
		pf->print = pf_strjoin(pf, "\x1B[45m\0");
		pf->fmt += 9;
		return ;
	}
	else
		background_colors3(pf);
}

void			background_colors(t_pf *pf)
{
	if (!ft_strncmp(pf->fmt, "{_}", 3))
	{
		pf->print = pf_strjoin(pf, "\x1B[49m\0");
		pf->fmt += 2;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_red}", 6))
	{
		pf->print = pf_strjoin(pf, "\x1B[41m\0");
		pf->fmt += 5;
		return ;
	}
	else if (!ft_strncmp(pf->fmt, "{_blue}", 7))
	{
		pf->print = pf_strjoin(pf, "\x1B[44m\0");
		pf->fmt += 6;
		return ;
	}
	else
		background_colors2(pf);
}
