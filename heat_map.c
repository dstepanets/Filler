/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heat_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 16:14:04 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/10 16:14:06 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		assign_heat(t_flr *f, intmax_t i, int x, int y)
{
	f->map_h--;
	f->map_w--;
	if ((x + 1 < f->map_w && f->hm[y][x + 1] == i) ||
		(y + 1 < f->map_h && f->hm[y + 1][x] == i) ||
		(y + 1 < f->map_h && x + 1 < f->map_w && f->hm[y + 1][x + 1] == i) ||
		(y - 1 >= 0 && x + 1 < f->map_w && f->hm[y - 1][x + 1] == i) ||
		(y - 1 >= 0 && f->hm[y - 1][x] == i) ||
		(y - 1 >= 0 && x - 1 >= 0 && f->hm[y - 1][x - 1] == i) ||
		(x - 1 >= 0 && f->hm[y][x - 1] == i) ||
		(y < f->map_h && x - 1 >= 0 && f->hm[y + 1][x - 1] == i))
		{
			f->hm[y][x] = i + 1;
			f->map_h++;
			f->map_w++;
			return (1);
		}
	f->map_h++;
	f->map_w++;
	return (0);
}

static void			fill_heatmap2(t_flr *f, intmax_t i, intmax_t *done)
{
	int		x;
	int		y;

	y = 0;
	while (y < f->map_h)
	{
		while (x < f->map_w)
		{
			if (f->hm[y][x] == 99)
			{
				if (assign_heat(f, i, x, y))
					(*done)++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void			fill_heatmap(t_flr *f)
{
	intmax_t		i;
	intmax_t		done;
	intmax_t		save;

	i = 0;
	done = 0;
	save = -1;
	while (done > save)
	{
		save = done;
		fill_heatmap2(f, i, &done);
//		print_heatmap(f);
//		print_map(f);
		i++;
	}
}



static void		create_heatmap2(t_flr *f, int *y)
{
	int		x;

	x = 0;
	while (x < f->map_w)
	{
		if (f->map[*y][x] == '.')
			f->hm[*y][x] = 99;
		else if (f->map[*y][x] == f->foe || f->map[*y][x] == (f->foe - 32))
			f->hm[*y][x] = 0;
		else if (f->map[*y][x] == f->me || f->map[*y][x] == (f->me - 32))
			f->hm[*y][x] = -1;
		x++;
	}
	(*y)++;
}


int				create_heatmap(t_flr *f)
{
	int		y;

	y = 0;
	if (!(f->hm = (int **)malloc(sizeof(int *) * f->map_h + 1)))
		return (-1);
	while (y < f->map_h)
	{
		f->hm[y] = (int *)malloc(sizeof(int *) * f->map_w);
		if (!f->hm[y])
		{
			while (y > 0)
				free(f->hm[--y]);
			free(f->hm);
			return (-1);
		}
		create_heatmap2(f, &y);
	}
	f->hm[y] = NULL;
	return (0);
}		
