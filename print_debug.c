/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 11:55:04 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/16 11:55:05 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	print_piece(t_flr *f)
{
	usleep(1000);
	dprintf(2, ">> PIECE:\n");
	for (int i = 0; i < f->fig_h; i++)
		dprintf(2, "%s\n", f->fig[i]);
	dprintf(2, "__________________\n");
}

void	print_map(t_flr *f)
{
	dprintf(2, "map  ");
	int j = 0;
	for (int i = 0; i < f->map_w; i++)
	{
		dprintf(2, "%d", j++);
		j == 10 ? j = 0 : 0;
	}
	dprintf(2, "\n");
	for (int i = 0; i < f->map_h; i++)
		dprintf(2, "%0.3d: %s\n", i, f->map[i]);
	dprintf(2, "=====================================================================\n");
}

void	print_heatmap(t_flr *f)
{
	dprintf(2, "\n");
	dprintf(2, "heat ");
	for (int i = 0; i < f->map_w; i++)
		dprintf(2, "|%2d ", i);
	dprintf(2, "|\n");
	int	y = 0;
	while (y < f->map_h)								
	{
		dprintf(2, "%03d: ", y);
		for (int x = 0; x < f->map_w; x++)
			dprintf(2, "|%2d ", f->hm[y][x]);
		dprintf(2, "|\n");
		y++;
	}
	dprintf(2, "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}
