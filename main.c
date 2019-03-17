/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 16:46:58 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/02 16:46:59 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		get_mapsize(t_flr *f)
{
	char	**split;

	split = NULL;
	while (get_next_line(0, &f->line) > 0)
	{
		if (!ft_strncmp(f->line, "Plateau", 7))
		{
			split = ft_strsplit(f->line, ' ');
			f->map_h = ft_atoi(split[1]);
			f->map_w = ft_atoi(split[2]);
			break ;
		}
		ft_strdel(&f->line);
	}
	del_arr(split);
	ft_strdel(&f->line);
}

static void		whoiswho(t_flr *f)
{
	char	*ptr;

	ptr = NULL;
	while (get_next_line(0, &f->line))
	{
		if ((ptr = ft_strstr(f->line, "[./dstepane.filler]")))
		{
			ptr -= 4;
			break ;
		}
		ft_strdel(&f->line);
	}
	if (ptr)
	{
		f->me = (*ptr == '1') ? 'O' : 'X';
		f->foe = (f->me == 'O') ? 'X' : 'O';
	}
	ft_strdel(&f->line);
}

static void		init_struct(t_flr *f)
{
	f->line = NULL;
	f->me = '\0';
	f->foe = '\0';
	f->map_h = 0;
	f->map_w = 0;
	f->map = NULL;
	f->fig_h = 0;
	f->fig_w = 0;
	f->fig = NULL;
	f->hm = NULL;
	whoiswho(f);
	get_mapsize(f);
}

int				main(void)
{
	t_flr	*f;
	t_plc	*p;
//		FILE *fp;									/// TEST
//		fp = freopen("./feed1.txt", "r", stdin);
	if (!(f = (t_flr *)malloc(sizeof(t_flr))))
		return (-1);
	init_struct(f);
	while (get_next_line(0, &f->line) > 0)
	{
		if (parser(f))
		{
			if (create_heatmap(f) == -1)
				return (-1);
			fill_heatmap(f);
			p = find_homeland(f);
				print_heatmap(f);  ///
			ft_printf("%d %d\n", p->by, p->bx);
			del_piece(f);
			del_map(f);
			del_heatmap(f);
			free((void *)p);
			p = NULL;
		}
		ft_strdel(&f->line);
	}
	free((void *)f);
//	fclose(fp);
//	system("leaks -q dstepane.filler");
	return (0);
}

//	./filler_vm -f maps/map01 -p1 ./dstepane.filler -p2 ./players/carli.filler | visuals/visualizer