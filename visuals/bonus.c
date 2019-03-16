/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppolozhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:28:27 by ppolozhe          #+#    #+#             */
/*   Updated: 2019/03/06 19:30:22 by ppolozhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "../libft/includes/libft.h"
#include "../libft/includes/get_next_line.h"
#include "wchar.h"
#include "locale.h"

static void	usa_win(void)
{
	printf("\e[1;34m #####  #   #    ###  #  #        #####   #####   ###   ##"
		"	   ##        #      ####    #####  ###   ##\e[0m\n");
	printf("\e[1;31m #      #   #   ##    # #         ##  #   ##      ## #  ##"
		"	   ##       #  #    ##  ##  ##     ## #  ##\e[0m\n");
	printf("\e[1;34m ####   #   #   #     ##          ######  #####   ##  # ##"
		"	   ##      ##  ##   ##   #  #####  ##  # ##\e[0m\n");
	printf("\e[1;31m #      #   #   ##    # #         ##  ##  ##      ##   ###"
		"	   #####   ######   ##  ##  ##     ##   ###\e[0m\n");
	printf("\e[1;34m #       ###     ###  #  #        ######  ######  ##    ##"
		"	   #####  ##    ##  #####   #####  ##    ##\e[0m\n");
}

static void	print_winner(char *buff)
{
	int		ben;
	int		anti;

	anti = ft_atoi(buff + 9);
	get_next_line(0, &buff);
	ben = ft_atoi(buff + 9);
	free(buff);
	printf("\e[1;34mUSA == %d\n\e[3;33mAL-QAEDA == %d\e[0m\n", anti, ben);
	if (ben > anti)
	{
		printf("\e[33m     &      &&          &&&&&&        &     "
			" &&&&&  &&&&&       &    \e[0m\n");
		printf("\e[33m    & &     &&          &&  &&       & &    "
			" &&     &&  &&     & &   \e[0m\n");
		printf("\e[33m   && &&    &&     &&&  &&  &&      && &&   "
		" &&&&&  &&  &&    && &&  \e[0m\n");
		printf("\e[33m  &&&&&&&   &&&&&       &&  &      &&&&&&&  "
		" &&     &&  &&   &&&&&&& \e[0m\n");
		printf("\e[33m &&     &&  &&&&&&      &&&& &&&  &&     && "
			" &&&&&  &&&&&   &&     &&\e[0m\n");
	}
	else
		usa_win();
}

static void	print_line(char *line)
{
	int				i;
	static wchar_t	ben = L'؈';
	static wchar_t	anti = L'✡';
	static wchar_t	space = L'⚘';
	static wchar_t	board = L'☭';

	i = 0;
	printf("\e[31m%lc\e[0m", board);
	while (line[i])
	{
		if (line[i] == 'X' || line[i] == 'x')
			printf("\e[1;33m%lc\e[0m", ben);
		if (line[i] == 'O' || line[i] == 'o')
			printf("\e[1;31m%lc\e[0m", anti);
		if (line[i] == '.')
			printf("\e[30m%lc\e[0m", space);
		i++;
	}
	printf("\e[31m%lc\n\e[0m", board);
	free(line);
}

static void	read_map(int size[2])
{
	char		*buff;
	int			j;

	j = -1;
	get_next_line(0, &buff);
	free(buff);
	for (int i = 0; i < 50; i++)
		printf("\n");
	while (++j < size[0])
	{
		get_next_line(0, &buff);
		print_line(ft_strdup(buff + 4));
		free(buff);
	}
}

int			main(void)
{
	char	*buff;
	int		size[2];

	buff = NULL;
	size[0] = -1;
	setlocale(LC_ALL, "");
	while (get_next_line(0, &buff))
	{
		if (buff[1] == 'l')
		{
			if (size[0] == -1)
			{
				size[0] = ft_atoi(buff + 8);
				size[1] = ft_atoi(buff + 10);
			}
			usleep(10000);
			read_map(size);
		}
		else if (buff[1] == '=')
			print_winner(buff);
		free(buff);
	}
	return (0);
}
