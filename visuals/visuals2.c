/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:44:02 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/17 19:44:03 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visuals.h"

void			winner(t_flrvis *fv)
{
	printf("\e[1m");
	if (fv->oscore > fv->xscore)
	{
		printf("			\e[100m\e[34m Angels");
		printf("\e[33m outdrunk \e[31mDevils\e[33m! \e[49m\n");
		printf("\n				😇🍷\n");
	}
	else if (fv->oscore < fv->xscore)
	{
		printf("			\e[100m\e[31m Devils");
		printf("\e[33m outdrunk \e[34mAngels\e[33m! \e[49m\n");
		printf("\n				😈🍷\n");
	}
	else if (fv->oscore == fv->xscore && fv->oscore > 0)
	{
		printf("			\e[100m\e[96m There was enough wine for all!");
		printf("\e[39m \e[49m\n");
		printf("\n				   😇🍷😈\n");
	}
	else
	{
		printf("			\e[100m\e[33m Something wrong!\e[39m \e[49m\n");
		printf("\n				🙀\n");
	}
	printf("\e[0m\n\n\n\n\n");
}

void			print_score(t_flrvis *fv)
{
	printf("\n		\e[4mscore 🍷:\e[0m	\e[1m\e[34m");
	printf("😇: %d		\e[31m😈: %d\e[39m\e[0m\n", fv->oscore, fv->xscore);
}

void			print_border(t_flrvis *fv)
{
	int		i;

	printf("\t\t🌳");
	i = 0;
	while (i++ <= fv->map_w)
		printf("🌳");
	printf("\n");
}
