/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:28:34 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/08 13:28:36 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_word_count(const char *s, char c)
{
	int		i;
	int		nw;

	nw = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if ((s[i] != c && s[i - 1] == c && s[i]) || (s[i] != c && i == 0))
			nw++;
		i++;
	}
	return (nw);
}

static int	ft_word_len(const char *s, char c)
{
	int	l;

	l = 0;
	while (*s && *s != c)
	{
		l++;
		s++;
	}
	return (l);
}

static char	*ft_getword(const char *s, char c)
{
	char	*word;
	int		i;

	if (!(word = (char *)malloc(ft_word_len(s, c) + 1)))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		k;
	char	**res;
	int		wrds;

	i = 0;
	k = 0;
	if (!s || !c ||
		!(res = (char **)malloc(sizeof(char *) * ft_word_count(s, c) + 1)))
		return (NULL);
	wrds = ft_word_count(s, c);
	while (s[k] && wrds--)
	{
		while (s[k] == c)
			k++;
		if (s[k] != c && s[k] != '\0')
		{
			res[i] = ft_getword(&s[k], c);
			k += ft_word_len(&s[k], c);
			i++;
		}
		k++;
	}
	res[i] = NULL;
	return (res);
}
