/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:25:02 by dstepane          #+#    #+#             */
/*   Updated: 2019/03/15 17:25:07 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static char		*ft_cut_line(char *str, char **line)
{
	char	*leak;
	size_t	i;

	i = 0;
	leak = NULL;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_strsub(str, 0, i);
	if (ft_strchr(str, '\n'))
	{
		leak = str;
		str = ft_strchr(str, '\n');
		str++;
		str = ft_strdup(str);
		free(leak);
	}
	else
	{
		leak = str;
		str = ft_strdup("");
		free(leak);
	}
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static char		*arr[4864];
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*leak;

	if ((read(fd, buf, 0) < 0) || fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	ret = 0;
	if (arr[fd] == NULL)
		arr[fd] = ft_strdup("");
	while (!(ft_strchr(arr[fd], '\n')))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		leak = arr[fd];
		arr[fd] = ft_strjoin(arr[fd], buf);
		free(leak);
	}
	if (ret == 0 && (!arr[fd] || arr[fd][0] == '\0'))
		return (0);
	arr[fd] = ft_cut_line(arr[fd], line);
	return (1);
}
