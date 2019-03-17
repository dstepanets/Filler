/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:56:25 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/17 16:56:26 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		get_piece(t_flr *f)
{
	int		i;

	if (f->fig)
		del_piece(f);
	if (!(f->fig = ft_memalloc(sizeof(char *) * f->fig_h + 1)))
		return ;
	i = 0;
	while (i < f->fig_h)
	{
		f->fig[i++] = ft_strdup(f->line);
		ft_strdel(&f->line);
		if (i < f->fig_h)
			get_next_line(0, &f->line);
	}
	f->fig[i] = NULL;
}

static void		get_piece_size(t_flr *f)
{
	char	**split;

	split = ft_strsplit(f->line, ' ');
	f->fig_h = ft_atoi(split[1]);
	f->fig_w = ft_atoi(split[2]);
	del_arr(split);
}

static void		get_map(t_flr *f)
{
	int		i;

	if (f->map)
		del_map(f);
	if (!(f->map = ft_memalloc(sizeof(char *) * f->map_h + 1)))
		return ;
	i = 0;
	while (i < f->map_h)
	{
		ft_strdel(&f->line);
		get_next_line(0, &f->line);
		f->map[i++] = ft_strdup(f->line + 4);
	}
	f->map[i] = NULL;
}

int				parser(t_flr *f)
{
	if (!ft_strncmp("    0", f->line, 5))
		get_map(f);
	if (!ft_strncmp("Piece", f->line, 5))
		get_piece_size(f);
	if (f->line[0] == '.' || f->line[0] == '*')
		get_piece(f);
	if (f->map && f->fig)
		return (1);
	return (0);
}
