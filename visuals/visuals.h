/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visuals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:32:41 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/16 12:32:42 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALS_H
# define VISUALS_H

# include "../libft/includes/libft.h"
# include <wchar.h>
# include <locale.h>

typedef struct			s_flrvis
{
	char				*line;
	int					map_h;
	int					map_w;
	int					oscore;
	int					xscore;
}						t_flrvis;

void					del_arr(char **arr);
void					print_border(t_flrvis *fv);
void					print_score(t_flrvis *fv);
void					winner(t_flrvis *fv);

#endif
