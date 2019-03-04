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

void			del_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void			get_piece(t_flr *f)
{
	char	*line;
	char	**split;

	get_next_line(0, &line);
	split = ft_strsplit(line, ' ');
	f->fig_h = ft_atoi(split[1]);
	f->fig_w = ft_atoi(split[2]);
	del_arr(split);
	ft_strdel(&line);
}

void			get_map(t_flr *f)
{
	char	*line;
	int		i;
	
	if (!(f->map = (char **)malloc(sizeof(char *) * f->map_h)))
		return ;
	get_next_line(0, &line);
	ft_strdel(&line);
	i = 0;
	while (i < f->map_h)
	{
		get_next_line(0, &line);
		f->map[i] = ft_strsub(line, 4, f->map_w);
		ft_strdel(&line);
		i++;
	}
}

void			get_mapsize(t_flr *f)
{
	char	*line;
	char	**split;

	split = NULL;
	while (get_next_line(0, &line))
	{	
		if (!ft_strncmp(line, "Plateau", 7))
		{
			split = ft_strsplit(line, ' ');
			f->map_h = ft_atoi(split[1]);
			f->map_w = ft_atoi(split[2]);
			break ;
		}
		ft_strdel(&line);
	}
	del_arr(split);
	ft_strdel(&line);
}

void			whoiswho(t_flr *f)
{
	char	*line;
	char	*ptr;

	while (get_next_line(0, &line))
	{
//		printf("line: %s\n", line);
		if ((ptr = ft_strstr(line, "[./dstepane.filler]")))
		{
			ptr -= 4;
			break ;
		}
		ft_strdel(&line);
	}
	f->me = (*ptr == '1') ? '0' : 'X';
	f->foe = (f->me == '0') ? 'X' : '0';
	ft_strdel(&line);
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

int			main(void)
{
	t_flr	*f;
	
	if (!(f = (t_flr *)malloc(sizeof(t_flr *))))
		return (-1);
	init_struct(f);
	whoiswho(f);
	get_mapsize(f);
	get_map(f);
	get_piece(f);
	for (int z = 0; z < f->map_h; z++)
		printf("%0.3d: %s\n", z, f->map[z]);
//	printf("me: %c, foe: %c\n", f->me, f->foe);
//	printf("mh: %d, mw: %d\n", f->map_h, f->map_w);
//	printf("fh: %d, fw: %d\n", f->fig_h, f->fig_w);
	ft_putstr_fd("1 1\n", 2);
	free((void *)f);

//	printf("\n++++++++++++++++++++++++LEAKS++++++++++++++++++++++++++++++++++++++\n");
//	system("leaks dstepane.filler");
	return (0);
}


//	./filler_vm -f maps/map00 -p1 players/champely.filler -p2 ./dstepane.filler

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