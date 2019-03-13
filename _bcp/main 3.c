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
	
	if (!(f->fig = (char **)malloc(sizeof(char *) * f->fig_h + 1)))
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

void			get_piece_size(t_flr *f)
{
	char	**split;
//	printf("gpsl: %s\n", f->line);
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
	while (i < f->map_h)
	{
		ft_strdel(&f->line);
		get_next_line(0, &f->line);
//		printf("ml: %s\n", f->line);
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
//		printf("line: %s\n", f->line);
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
//		printf("line: %s\n", f->line);
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
	while (get_next_line(0, &f->line) > 0)
	{
//		printf("ln: %s\n", f->line);
		if (!ft_strncmp("    0", f->line, 5))
			get_map(f);
		else if (!ft_strncmp("Piece", f->line, 5))
			get_piece_size(f);
		else if (f->line[0] == '.' || f->line[0] == '*')
			get_piece(f);
		ft_strdel(&f->line);
		if (f->fig)
			return (1);
	}
	return (0);
}

int			main(void)
{
	t_flr	*f = NULL;
	t_plc	*p = NULL;
//		FILE *fp;									/// TEST
//		fp = freopen("./feed1.txt", "r", stdin); 		/// TEST

	if (!f && !p) 
	{
		if (!(f = (t_flr *)malloc(sizeof(t_flr))))
			return (-1);
//		dprintf(1, "8 2\n");
//		return (0);
		ft_bzero(f, sizeof(t_flr));
		p = NULL;
		init_struct(f);
		whoiswho(f);
//			printf("me: %c, foe: %c\n", f->me, f->foe);
		get_mapsize(f);
//			printf("mh: %d, mw: %d\n", f->map_h, f->map_w);
	}
	if (parser(f))
	{
		if (create_heatmap(f) == -1)
			return (-1);
		make_heatmap(f);
		p = find_homeland(f);
		ft_printf("%d %d\n", p->by, p->bx);		//"Y X\n" - right order!
	}
/*			for (int i = 0; i < f->map_h; i++)
				printf("%0.4d: %s\n", i, f->map[i]);
			printf("fh: %d, fw: %d\n", f->fig_h, f->fig_w);
			for (int i = 0; i < f->fig_h; i++)
				printf("%0.2d: %s\n", i, f->fig[i]);
*/
/*			int	y = 0;
			while (y < f->map_h)								///////TEMP
			{
				for (int x = 0; x < f->map_w; x++)
					printf("|%2d ", f->hm[y][x]);
				printf("|\n");
				y++;
			}
*/	
	del_arr(f->fig);
	del_map(f);
	del_heatmap(f);
	ft_strdel(&f->line);
	free((void *)f);
	free((void *)p);

//		fclose(fp);											/// TEST
//	printf("\n++++++++++++++++++++++++LEAKS++++++++++++++++++++++++++++++++++++++\n");
//	system("leaks -q dstepane.filler");
	return (0);
}


//	./filler_vm -f maps/map00 -p1 ./dstepane.filler -p2 players/champely.filler 
//	./filler_vm -f maps/map00 -p1 ./dstepane.filler -p2 players/abanlin.filler

//	./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 ./players/grati.filler
