/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 15:34:45 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	clean_free(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		length;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (length + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	while (*s2)
		dest[i++] = *s2++;
	dest[i] = '\0';
	clean_free(&s1);
	return (dest);
}

static int	clean_and_return(char **string, int error)
{
	clean_free(string);
	return (error);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;

	dest = s;
	while (n > 0)
	{
		*dest = 0;
		dest++;
		n--;
	}
}

int	get_next_line(int fd, char **line)
{
	char	*buf;
	int		ret;

	buf = ft_calloc(2, sizeof(char));
	if (!buf)
		return (-1);
	*line = ft_calloc(1, sizeof(char));
	if (!line || (read(fd, buf, 0) < 0))
		return (clean_and_return(&buf, -1));
	ret = 1;
	while (ret != 0 && buf[0] != '\n')
	{
		ret = read(fd, buf, 1);
		if (ret < 0)
			return (clean_and_return(&buf, -1));
		if (buf[0] == '\n' || buf[0] == 13)
			continue ;
		buf[ret] = 0;
		*line = ft_strjoin(*line, buf);
	}
	clean_free(&buf);
	return (ret);
}
