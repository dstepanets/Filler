/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:54:36 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/07 18:54:38 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*cpy;
	int		i;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	len = ft_strlen(s) - 1;
	while (len > i && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	if (!(cpy = (char *)malloc(len - i + 2)))
		return (NULL);
	j = 0;
	while (i <= len)
		cpy[j++] = s[i++];
	cpy[j] = '\0';
	return (cpy);
}
