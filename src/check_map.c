/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 13:59:36 by llalba            #+#    #+#             */
/*   Updated: 2022/03/07 15:51:08 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_bool	check_line(t_data *data, int i, char *content)
{
	int	j;

	j = i - 1;
	if (i == (i / data->map.width) * data->map.width || \
		i == (i / data->map.width + 1) * data->map.width)
		return (FALSE);
	while (j >= (i / data->map.width) * data->map.width)
	{
		if (content[j] == '1')
			break ;
		if (content[j] == ' ' || content[j] == '\0')
			return (FALSE);
		j--;
	}
	if (j == (i / data->map.width) * data->map.width && content[j] != '1')
		return (FALSE);
	j = i;
	while (++j < (i / data->map.width + 1) * data->map.width)
	{
		if (content[j] == '1')
			return (TRUE);
		if (content[j] == ' ' || content[j] == '\0')
			return (FALSE);
	}
	return (FALSE);
}

static t_bool	check_column_up(t_data *data, int i, char *content)
{
	int	w;
	int	h;
	int	line_i;
	int	col_i;
	int	j;

	w = data->map.width;
	h = data->map.height;
	line_i = i / w;
	col_i = i - line_i * w;
	j = line_i -1;
	while (j >= 0)
	{
		if (content[j * w + col_i] == '1')
			return (TRUE);
		if (content[j * w + col_i] == ' ' || content[j * w + col_i] == '\0')
			return (FALSE);
		j--;
	}
	return (FALSE);
}

static t_bool	check_column_down(t_data *data, int i, char *content)
{
	int	w;
	int	h;
	int	line_i;
	int	col_i;
	int	j;

	w = data->map.width;
	h = data->map.height;
	line_i = i / w;
	col_i = i - line_i * w;
	j = line_i + 1;
	while (j < h)
	{
		if (content[j * w + col_i] == '1')
			return (TRUE);
		if (content[j * w + col_i] == ' ' || content[j * w + col_i] == '\0')
			return (FALSE);
		j++;
	}
	return (FALSE);
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
			ft_error(data, "invalid map\n");
	}
	i = -1;
	while (++i < w * h)
	{
		if (data->map.content[i] == ' ')
			data->map.content[i] = '1';
	}
}
