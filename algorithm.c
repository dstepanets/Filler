/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 19:50:48 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/10 19:50:50 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void 		init_struct_place(t_plc *p)
{
	p->i = 0;
	p->j = 0;
	p->y = 0;
	p->x = 0;
	p->val = 0;
	p->by = 0;
	p->bx = 0;
	p->bval = 0;
}

void			remember_position(t_plc *p)
{
	p->by = p->y;
	p->bx = p->x;
	p->bval = p->val;
//	printf("p->by: %d, p->bx: %d\n", p->by, p->bx);
//	printf("p->bval: %d\n", p->bval);
}

int				try_place(t_flr *f, t_plc *p)
{
	int		touch;

	touch = 0;
	p->i = 0;
	p->j = 0;
	p->val = 0;
	while (p->i < f->fig_h)
	{
		while (p->j < f->fig_w)
		{
			if (f->fig[p->i][p->j] == '*')
			{
				if ((p->y + p->i >= f->map_h) || (p->x + p->j >= f->map_w))
					return (0);
				else if (f->map[p->y + p->i][p->x + p->j] == ft_toupper(f->me))
				{
					touch++;
					if (touch > 1)
						return (0);
				}
				else if (f->map[p->y + p->i][p->x + p->j] == '.')
					p->val += f->hm[p->y + p->i][p->x + p->j];
				else
					return (0);
			}
			p->j++;
		}
		p->j = 0;
		p->i++;
	}
	if (touch != 1)
		return (0);
	return (1);
}

void			find_places(t_flr *f, t_plc *p)
{
	while (p->y < f->map_h)
	{
		while (p->x < f->map_w)
		{
			if (try_place(f, p) && (!p->bval || p->val < p->bval))
				remember_position(p);
			p->x++;
		}
		p->x = 0;
		p->y++;
	}
}

void			offset(t_flr *f, t_plc *p)
{
	p->y -= f->fig_h;
	p->x -= f->fig_w;
	while (p->y < 0)
		p->y++;
	while (p->x < 0)
		p->x++;
	find_places(f, p);
}

t_plc			*find_homeland(t_flr *f)
{
	t_plc		*p;

	if (!(p = (t_plc *)malloc(sizeof(t_plc))))
		return (NULL);
	init_struct_place(p);
	while (p->y < f->map_h)
	{
		while (p->x < f->map_w && p->y < f->map_h)
		{
			if (f->map[p->y][p->x] == ft_toupper(f->me))
				offset(f, p);
			p->x++;
		}
		p->x = 0;
		p->y++;
	}
	return (p);
}
