/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:48:16 by llalba            #+#    #+#             */
/*   Updated: 2022/02/02 15:50:40 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char)s2[i]);
}

void	ft_strncpy(char *s, char **d, int n)
{
	int	i;

	i = -1;
	//TODO suppose que s pas NULL + d existe et >n
	while (++i < n)
		(*d)[i] = s[i];
}

int	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && s2[i] != ' ')
		i++;
	if (!s1[i] && s2[i] == ' ')
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_cpy(void *dst, const void *src, int n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}
