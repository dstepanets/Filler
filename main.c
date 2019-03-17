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

void			get_piece(t_flr *f)
{
	int		i;

	if (f->fig)
		del_piece(f);
	if (!(f->fig = ft_memalloc(sizeof(char *) * f->fig_h + 1)))
		return ;
	f->fig = ft_memalloc(sizeof(char *) * f->fig_h + 1);
	i = 0;
	while (i < f->fig_h)
	{
//			dprintf(2, "gp_line: %s\n", f->line);   // 
		f->fig[i++] = ft_strdup(f->line);
		ft_strdel(&f->line);
		if (i < f->fig_h)
			get_next_line(0, &f->line);
	}
	f->fig[i] = NULL;
}

void			get_piece_size(t_flr *f)
{
	char	**split;

	split = ft_strsplit(f->line, ' ');
	f->fig_h = ft_atoi(split[1]);
	f->fig_w = ft_atoi(split[2]);
	del_arr(split);
}

void			get_map(t_flr *f)
{
	int		i;
	
	if (f->map)
		del_map(f);
	if (!(f->map = ft_memalloc(sizeof(char *) * f->map_h + 1)))
		return ;
	i = 0;
//		usleep(1000); ////
	while (i < f->map_h)
	{
//			dprintf(2, "> gmap_line: %s\n", f->line);   // 
		ft_strdel(&f->line);
		get_next_line(0, &f->line);
		f->map[i++] = ft_strdup(f->line + 4);
	}
	f->map[i] = NULL;
}

void			get_mapsize(t_flr *f)
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

void			whoiswho(t_flr *f)
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

void 		init_struct(t_flr *f)
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
}

int			parser(t_flr *f)
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

int			main(void)
{
	t_flr	*f;
	t_plc	*p;

	if (!(f = (t_flr *)malloc(sizeof(t_flr))))
		return (-1);
	ft_bzero(f, sizeof(t_flr));
	init_struct(f);
	whoiswho(f);
	get_mapsize(f);
	while (get_next_line(0, &f->line) > 0)
	{
		if (parser(f))
		{
			if (create_heatmap(f) == -1)
				return (-1);
			fill_heatmap(f);
			p = find_homeland(f);
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
	return (0);
}

//	./filler_vm -f maps/map01 -p1 dstepane.filler -p2 players/carli.filler | visuals/visualizer