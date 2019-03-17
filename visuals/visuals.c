/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 11:44:43 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/16 11:44:44 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visuals.h"

static void			convert_line(t_flrvis *fv)
{
	int		i;

	printf("\t\t🌳");
	i = 4;
	while (fv->line[i])
	{
		if (fv->line[i] == '.')
			printf("%lc", L'🍷');
		else if (fv->line[i] == 'O' || fv->line[i] == 'o')
		{
			fv->oscore++;
			printf("%lc", L'😇');
		}
		else if (fv->line[i] == 'X' || fv->line[i] == 'x')
		{
			fv->xscore++;
			printf("%lc", L'😈');
		}
		i++;
	}
	printf("🌳\n");
	ft_strdel(&fv->line);
}

static void			map_printer(t_flrvis *fv)
{
	int		y;

	y = 0;
	fv->oscore = 0;
	fv->xscore = 0;
	get_next_line(0, &fv->line);
	ft_strdel(&fv->line);
	if (fv->map_h < 50)
		while (y++ < 50)
			ft_putchar('\n');
	print_border(fv);
	y = 0;
	while (y++ < fv->map_h)
	{
		get_next_line(0, &fv->line);
		convert_line(fv);
		ft_strdel(&fv->line);
	}
	print_border(fv);
	print_score(fv);
	if (fv->map_h < 50)
	{
		printf("\n\n\n\n\n");
		usleep(5000);
	}
}

static void			mapsize(t_flrvis *fv)
{
	char	**split;

	split = NULL;
	split = ft_strsplit(fv->line, ' ');
	fv->map_h = ft_atoi(split[1]);
	fv->map_w = ft_atoi(split[2]);
	del_arr(split);
}

static void			init_struct(t_flrvis *fv)
{
	fv->line = NULL;
	fv->map_h = -1;
	fv->map_w = -1;
	fv->oscore = 0;
	fv->xscore = 0;
}

int					main(void)
{
	t_flrvis	*fv;

	fv = NULL;
	if (!(fv = (t_flrvis *)malloc(sizeof(t_flrvis))))
		return (-1);
	init_struct(fv);
	setlocale(LC_ALL, "");
	while (get_next_line(0, &fv->line) > 0)
	{
		if (!ft_strncmp(fv->line, "Plateau", 7))
		{
			if (fv->map_h == -1)
				mapsize(fv);
			ft_strdel(&fv->line);
			map_printer(fv);
		}
		ft_strdel(&fv->line);
	}
	winner(fv);
	free((void *)fv);
	return (0);
}
