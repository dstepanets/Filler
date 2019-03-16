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

# include "visuals.h"

static void			winner(t_flrvis *fv)
{
	printf("\e[1m");
	if (fv->oscore > fv->xscore)
	{
		printf("			\e[100m\e[34m Angels\e[39m outdrunk \e[31mDevils\e[39m! \e[49m\n");
		printf("\n				😇🍷\n");
	}
	else if (fv->oscore < fv->xscore)
	{
		printf("			\e[100m\e[31m Devils\e[39m outdrunk \e[34mAngels\e[39m! \e[49m\n");
		printf("\n				😈🍷\n");
	}
	else
	{
		printf("			\e[100m\e[96 mWine was enough for all!\e[39m \e[49m\n");
		printf("\n				   🍷\n");
	}
	printf("\e[0m");
	printf("\n\n\n\n\n");
}

static void			print_score(t_flrvis *fv)
{
	printf("\n		\e[4mscore 🍷:\e[0m	\e[1m\e[34m😇: %d		\e[31m😈: %d\e[39m\e[0m\n", fv->oscore, fv->xscore);

}

static void			print_border(t_flrvis *fv)
{
	int 	i;
	printf("\t\t🌳");
	i = 0;
	while (i++ <= fv->map_w)
		printf("🌳");
	printf("\n");
}

static void			convert_line(t_flrvis *fv)
{
	int		i;
	
	printf("\t\t🌳");
	i = 4;
	while (fv->line[i])
	{
		if (fv->line[i] == '.')
			printf("%lc", L'🍷');
		else if (fv->line[i] == 'O'|| fv->line[i] == 'o')
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

static void			scanner(t_flrvis *fv)
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
//			printf("\nMAPSIZE: %d, %d\n", fv->map_h, fv->map_w);
			scanner(fv);

		}
		ft_strdel(&fv->line);
	}
	winner(fv);
	free((void *)fv);
	return (0);
}