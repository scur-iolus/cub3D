/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:52 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 18:32:03 by llalba           ###   ########.fr       */
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

void	ft_error(t_data *data, char *str)
{
	write(2, "Error: \n", 8);
	write(2, str, ft_strlen(str));
	if (data)
		free_data(data);
	exit (EXIT_FAILURE);
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

void	ft_strncpy(char *s, char **d, int n)
{
	int i;

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
