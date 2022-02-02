/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:59:36 by llalba            #+#    #+#             */
/*   Updated: 2022/02/02 14:13:46 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_bool	check_line(t_data *data, int i, char *content)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (content[j] == '1')
			break ;
		j++;
	}
	if (j == i)
		return (FALSE);
	j = data->map.width - 1;
	while (j > i)
	{
		if (content[j] == '1')
			break ;
		j--;
	}
	if (j == i)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_column_up(t_data *data, int i, char *content)
{
	int	w;
	int	h;
	int	nb_line;
	int	j;

	w = data->map.width;
	h = data->map.height;
	nb_line = i / w;
	j = 0;
	while (j < i)
	{
		if (content[j] == '1')
			break ;
		j++;
	}
	if (j == i)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_column_down(t_data *data, int i, char *content)
{
	int	j;
	int	w;
	int	h;

	w = data->map.width;
	h = data->map.height;
	j = w - 1;
	while (j > i)
	{
		if (content[j] == '1')
			break ;
		j--;
	}
	if (j == i)
		return (FALSE);
	return (TRUE);
}

void	check_frame(t_data *data)
{
	int		i;
	int		w;
	int		h;

	i = -1;
	w = data->map.width;
	h = data->map.height;
	while (++i < w * h)
	{
		if (data->map.content[i] != '0')
			continue ;
		if (!check_line(data, i, data->map.content) || \
			!check_column_up(data, i, data->map.content) || \
			!check_column_down(data, i, data->map.content))
			ft_error(data, "invalid map13\n");
	}
}
