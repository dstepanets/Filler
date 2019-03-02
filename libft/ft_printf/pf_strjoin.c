/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:24:19 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/07 18:24:21 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"

char	*pf_strjoin(t_pf *pf, char *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!pf->print || !s2)
		return (NULL);
	if (!(res = (char *)malloc(ft_strlen(pf->print) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	if (*pf->fmt != '{' || (*pf->fmt == '{' && *s2 == '{'))
		pf->ret += ft_strlen(s2);
	while (pf->print[j])
		res[i++] = pf->print[j++];
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	if (pf->print)
	{
		free((void *)pf->print);
		pf->print = NULL;
	}
	return (res);
}
