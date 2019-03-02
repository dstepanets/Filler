/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:16:25 by dstepane          #+#    #+#             */
/*   Updated: 2019/02/18 15:16:27 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

static char			*get_fraction(t_pf *pf, t_fl *fl, long double num)
{
	int			pr;

	num = num - (intmax_t)num;
	pr = pf->prec;
	if (!(fl->right = (char *)malloc(sizeof(char) * pr + 1)))
		return (NULL);
	fl->right[pr] = '\0';
	if (num == 0 || fl->num == 0.0 || fl->num == -0.0)
	{
		ft_memset(fl->right, '0', pr);
		return (fl->right);
	}
	pr = 0;
	while (pr < pf->prec)
	{
		num *= 10;
		fl->right[pr++] = (int)num + '0';
		num -= (int)num;
	}
	return (fl->right);
}

static char			*get_int(t_fl *fl, intmax_t num)
{
	intmax_t	n;
	int			nlen;

	num = num < 0 ? -num : num;
	n = num;
	nlen = 1;
	while (n /= 10)
		nlen++;
	if (!(fl->left = (char *)malloc(sizeof(char) * nlen + 1)))
		return (NULL);
	fl->left[nlen] = '\0';
	(num == 0 || fl->num == -0.0 || fl->num == 0.0) ? fl->left[0] = '0' : 0;
	while (num)
	{
		fl->left[--nlen] = (num % 10) + '0';
		num /= 10;
	}
	if ((double)fl->num == LONG_MIN)
	{
		free(fl->left);
		fl->left = ft_strdup("9223372036854775808");
	}
	return (fl->left);
}

static void			put_sign(t_pf *pf, t_fl *fl)
{
	int					i;
	unsigned long long	*n;
	double				d;

	if (fl->num != fl->num)
		return ;
	d = fl->num;
	n = (unsigned long long *)&d;
	if (pf->flags[0] == '-' || pf->flags[3] == '0')
		i = 0;
	else
		i = fl->rlen - fl->nlen - 1;
	if (fl->num < 0.0 || (*n >> 63 & 1))
		fl->res[i] = '-';
	else if (pf->flags[1] == '+')
		fl->res[i] = '+';
	else if (pf->flags[2] == ' ')
		fl->res[i] = ' ';
}

static void			apply_specs(t_pf *pf, t_fl *fl)
{
	int					i;
	int					s;
	unsigned long long	*n;
	double				d;

	(pf->flags[0] == '-') ? pf->flags[3] = '\0' : 0;
	(pf->flags[1] == '+') ? pf->flags[2] = '\0' : 0;
	(pf->flags[3] == '0') ? ft_memset(fl->res, '0', fl->rlen) :
		ft_memset(fl->res, ' ', fl->rlen);
	i = 0;
	s = 0;
	d = fl->num;
	n = (unsigned long long *)&d;
	if (fl->num < 0.0 || pf->flags[2] == ' ' || pf->flags[1] == '+' ||
		((*n >> 63 & 1) && fl->num == fl->num))
	{
		put_sign(pf, fl);
		s = 1;
	}
	(pf->flags[0] == '-') ? (i += s) : (i = (fl->rlen - fl->nlen));
	while (*fl->left)
		fl->res[i++] = *fl->left++;
	(pf->prec != 0 || pf->flags[4] == '#') ? fl->res[i++] = '.' : 0;
	while (*fl->right)
		fl->res[i++] = *fl->right++;
}

void				convert_f(t_pf *pf)
{
	t_fl		*fl;
	char		*leak1;
	char		*leak2;

	fl = (t_fl *)malloc(sizeof(t_fl));
	(pf->len == L) ? (fl->num = (long double)(va_arg(pf->args, long double))) :
		(fl->num = (double)(va_arg(pf->args, double)));
	pf->prec == -1 ? pf->prec = 6 : 0;
	fl->roun = fl_round_num(pf->prec, fl->num);
	leak1 = get_int(fl, fl->roun);
	leak2 = get_fraction(pf, fl, fl->roun);
	infnan(pf, fl) ? leak1 = fl->left : 0;
	fl_res_len(pf, fl);
	if (!(fl->res = (char *)malloc(sizeof(char) * fl->rlen + 1)))
		return ;
	fl->res[fl->rlen] = '\0';
	apply_specs(pf, fl);
	pf->print = pf_strjoin(pf, fl->res);
	free(leak1);
	free(leak2);
	free(fl->res);
	free(fl);
	fl = NULL;
}
