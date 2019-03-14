/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purgatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:40 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/06 18:50:43 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			del_heatmap(t_flr *f)
{
	int		i;

	i = 0;
	if (f->hm)
	{
		while (i < f->map_h)
		{
			ft_bzero(f->hm[i], f->map_w);
			free(f->hm[i++]);
		}
		ft_memdel((void **)&f->hm[i]);
		ft_memdel((void **)&f->hm);
		free(f->hm);
		f->hm = NULL;
	}
}

void			del_arr(char **arr)
{
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
//		free(arr);
		ft_memdel((void **)&arr);
//		arr = NULL;
	}
}

void			del_piece(t_flr *f)
{
	int		i;

	i = 0;
	f->fig_h = 0;
	f->fig_w = 0;
	if (f->fig)
	{
		while (i < f->fig_h + 1)
		{
			ft_bzero(f->fig[i], f->fig_w);
			ft_strdel(&f->fig[i++]);
		}
		ft_strdel(&f->fig[i]);
	//	free(f->fig);
	//	f->fig = NULL;
		ft_memdel((void **)&f->fig);
	}
}

void			del_map(t_flr *f)
{
	int		i;

	i = 0;
	if (f->map)
	{
		while (i < f->map_h)
		{
			ft_bzero(f->map[i], f->map_w);
			ft_strdel(&f->map[i++]);
		}
		ft_strdel(&f->map[i]);
		free(f->map);
		f->map = NULL;
	}
}
