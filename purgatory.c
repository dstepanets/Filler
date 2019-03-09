/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purgatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:50:40 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/06 18:50:43 by dstepane         ###   ########.fr       */
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

void			del_map(t_flr *f)
{
	int		i;

	i = 0;
	while (i < f->map_h)
		ft_strdel(&f->map[i++]);
	free(f->map);
}
