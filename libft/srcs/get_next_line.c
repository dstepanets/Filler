/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dstepane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 18:32:29 by dstepane          #+#    #+#             */
/*   Updated: 2018/11/22 19:35:51 by dstepane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static	int		check_nl(char **arr, const int fd, char **line)
{
	char	*tmp;
	int		len;

	if (ft_strchr(arr[fd], '\n'))
	{
		len = 0;
		while (arr[fd][len] != '\n')
			len++;
		*line = ft_strsub(arr[fd], 0, len);
		tmp = ft_strdup(arr[fd] + len + 1);
		free(arr[fd]);
		arr[fd] = tmp;
		return (1);
	}
	return (0);
}

static	int		buf_leftover(char **arr, const int fd, char **line)
{
	while (arr[fd])
	{
		if (check_nl(arr, fd, line))
			return (1);
		else
		{
			*line = ft_strdup(arr[fd]);
			ft_strdel(&arr[fd]);
			return (1);
		}
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*arr[4864];
	char			buf[BUFF_SIZE + 1];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	ret = 0;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (!arr[fd])
			arr[fd] = ft_strnew(1);
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
		if (check_nl(arr, fd, line))
			return (1);
	}
	if (ret < 0)
		return (-1);
	if (ret == 0 && (!arr[fd] || arr[fd][0] == '\0'))
		return (0);
	return (buf_leftover(arr, fd, line));
}
