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
	printf("gpsl: %s\n", f->line);
	split = ft_strsplit(f->line, ' ');
	f->fig_h = ft_atoi(split[1]);
	f->fig_w = ft_atoi(split[2]);
	del_arr(split);
}

void			get_map(t_flr *f)
{
	int		i;
	
	if (!(f->map = (char **)malloc(sizeof(char *) * f->map_h) + 1))
		return ;
	i = 0;
	while (i < f->map_h)
	{
		ft_strdel(&f->line);
		get_next_line(0, &f->line);
		printf("ml: %s\n", f->line);
		f->map[i++] = ft_strsub(f->line, 4, f->map_w);
	}
	f->map[i] = NULL;
}

void			get_mapsize(t_flr *f)
{
	char	**split;

	split = NULL;
	while (get_next_line(0, &f->line) > 0)
	{	
		printf("line: %s\n", f->line);
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

	while (get_next_line(0, &f->line))
	{
		printf("line: %s\n", f->line);
		if ((ptr = ft_strstr(f->line, "[./dstepane.filler]")))
		{
			ptr -= 4;
			break ;
		}
		ft_strdel(&f->line);
	}
	f->me = (*ptr == '1') ? '0' : 'X';
	f->foe = (f->me == '0') ? 'X' : '0';
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
}

int			parser(t_flr *f)
{
	while (get_next_line(0, &f->line) > 0)
	{
		printf("line: %s\n", f->line);
		if (!ft_strncmp("    0", f->line, 5))
			get_map(f);
		else if (!ft_strncmp("Piece", f->line, 5))
			get_piece_size(f);
		else if (f->line[0] == '.' || f->line[0] == '*')
			get_piece(f);
		ft_strdel(&f->line);
	}
	return (1);
}

int			main(void)
{

	printf("I'm your God, The Machine!\n");

//	t_flr	*f;
//		FILE *fp;									/// TEST
//		fp = freopen("./feed.txt", "r", stdin); 		/// TEST
/*	if (!(f = (t_flr *)malloc(sizeof(t_flr))))
		return (-1);
	init_struct(f);
	whoiswho(f);
			printf("me: %c, foe: %c\n", f->me, f->foe);
	get_mapsize(f);
			printf("mh: %d, mw: %d\n", f->map_h, f->map_w);
	parser(f);
			for (int z = 0; z < f->map_h; z++)
				printf("%0.4d: %s\n", z, f->map[z]);
			printf("fh: %d, fw: %d\n", f->fig_h, f->fig_w);
			for (int z = 0; z < f->fig_h; z++)
				printf("%0.2d: %s\n", z, f->fig[z]);
	del_arr(f->fig);
	del_map(f);
//	del_arr(f->map);

	free((void *)f);
//		fclose(fp);											/// TEST

*/	printf("\n++++++++++++++++++++++++LEAKS++++++++++++++++++++++++++++++++++++++\n");
	system("leaks dstepane.filler");
	return (0);
}


//	./filler_vm -f maps/map00 -p1 players/champely.filler -p2 ./dstepane.filler
//	./filler_vm -f maps/map00 -p1 players/abanlin.filler -p2 ./players/grati.filler
/*
./filler_vm -f maps/map00 -p1 players/champely.filler -p2 ./dstepane.filler
# -------------- VM  version 1.1 ------------- #
#                                              #
# 42 / filler VM Developped by: Hcao - Abanlin #
#                                              #
# -------------------------------------------- #
launched players/champely.filler
$$$ exec p1 : [players/champely.filler]
launched ./dstepane.filler
$$$ exec p2 : [./dstepane.filler]
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 3:
**.
.**
Player with O: error on input
Piece 2 2:
*.
*.
1 1
Player with X: error on input
== O fin: 0
== X fin: 0

*/