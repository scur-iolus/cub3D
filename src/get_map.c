/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:04:19 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 18:14:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_map_size(t_data *data)
{
	char			*line;
	int				width;
	static t_bool	end = FALSE;

	line = data->line;
	if (*line == 0)
	{
		if (data->map.width != 0)
			end = TRUE;
		else
			data->map_start++;
		return ;
	}
	data->map.height++;
	width = 0;
	while (*line)
	{
		if (end == TRUE || (*line != '1' && *line != '0' && *line != ' ' \
		&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W'))
			ft_error(data, "invalid map\n");
		width++;
		line++;
	}
	if (width > data->map.width)
		data->map.width = width;
}

void	get_map_content(t_data *data)
{
	int			len_l;
	static int	current = 0;
	char		*begin;

	len_l = ft_strlen(data->line);
	begin = data->map.content + (current * data->map.width);
	begin = ft_cpy(begin, data->line, len_l);
	current++;
}

void	check_path(t_data *data)
{
	int	fd;

	fd = open_file(data, data->no);
	close_file(data, fd);
	fd = open_file(data, data->so);
	close_file(data, fd);
	fd = open_file(data, data->ea);
	close_file(data, fd);
	fd = open_file(data, data->we);
	close_file(data, fd);
}

void	set_map(t_data *data)
{
	int		i;
	char	c;

	i = -1;
	check_frame(data);
	while (++i < data->map.width * data->map.height)
	{
		c = data->map.content[i];
		if (c == ' ')
			data->map.content[i] = '1';
		if (!data->map.pos && (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		{
			data->map.compass = c;
			data->map.pos = i;
			data->map.content[i] = '0';
		}
		else if (data->map.pos && (c == 'N' || c == 'S' \
			|| c == 'E' || c == 'W'))
			ft_error(data, "invalid map\n");
	}
	if (!data->map.pos)
		ft_error(data, "invalid map\n");
	check_path(data);
}
