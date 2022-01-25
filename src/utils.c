/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:52 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 15:23:58 by llalba           ###   ########.fr       */
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

int	ft_error(char *str)
{
	write(2, "Error: \n", 8);
	write(2, str, ft_strlen(str));
	return (EXIT_FAILURE);
}


int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char)s2[i]);
}

int	map_is_valid(char *cub)
{
	int	len;

	len = ft_strlen(cub);
	if (cub == 0)
		return (FAIL);
	if (len < 5)
		return (FAIL);
	if (ft_strcmp(cub + len - 4, ".cub"))
		return (FAIL);
	return (SUCCESS);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
