/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:28:10 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/02 17:28:12 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./libft/includes/libft.h"
//# include "mem.h"

typedef struct			s_flr
{
	char				*line;
	char				me;
	char				foe;
	int					map_h;
	int					map_w;
	char				**map;
	int					fig_h;
	int					fig_w;
	char				**fig;
	int					**hm;
	
} 						t_flr;

typedef struct			s_plc
{
	int					i;
	int					j;
	
	int					y;
	int					x;
	int					val;

	int					by;
	int					bx;
	int					bval;

}						t_plc;


void					del_arr(char **arr);
void					del_map(t_flr *f);
void					del_heatmap(t_flr *f);

int						create_heatmap(t_flr *f);
void					make_heatmap(t_flr *f);

t_plc					*find_homeland(t_flr *f);



#endif