/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:01:42 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 18:01:46 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t	get_coord_len(t_data *data, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	j = i;
	while (str[j])
	{
		if (str[j] != ' ')
			ft_error(data, "invalid map\n");
		j++;
	}
	return (i);
}

size_t	get_color_len(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	get_coord(t_data *data, char *coord, char **s)
{
	size_t	len;
	char	*line;

	line = data->line;
	if (!ft_cmp(coord, data->line) && !(*s))
	{
		line += 2;
		skip_spaces(&line);
		len = get_coord_len(data, line);
		*s = (char *)ft_calloc(len + 1, sizeof(char));
		if (!(*s))
			ft_error(data, "malloc failed\n");
		ft_strncpy(line, s, len);
		data->state++;
		return (1);
	}
	else if (!ft_cmp(coord, line) && *s)
		ft_error(data, "invalid map\n");
	return (0);
}

int	get_colors(t_data *data, char c, t_color *color)
{
	size_t	len;
	char	*line;

	line = data->line;
	if (line[0] == c && color->not_yet)
	{
		line++;
		skip_spaces(&(line));
		len = get_color_len(line);
		if (data->color_str)
		{
			free(data->color_str);
			data->color_str = NULL;
		}
		data->color_str = (char *)ft_calloc(len + 1, sizeof(char));
		if (!(data->color_str))
			ft_error(data, "malloc failed\n");
		ft_strncpy(line, &data->color_str, len);
		format_color(data, color);
		data->state++;
		return (SUCCESS);
	}
	else if (line[0] == c && color->not_yet)
		ft_error(data, "invalid map\n");
	return (SUCCESS);
}

void	format_color(t_data *data, t_color *color)
{
	char	**color_nb;

	if (!(data->color_str[0]) || count_comma(data->color_str) != 2)
		ft_error(data, "invalid map\n");
	color_nb = ft_split(data->color_str, ',');
	if (!color_nb)
		ft_error(data, "malloc failed\n");
	if (!(color_nb[0] && color_nb[1] && color_nb[2] && !color_nb[3]))
	{
		ft_free_split(color_nb);
		ft_error(data, "invalid map\n");
	}
	color->r = ft_atoi(color_nb[0]);
	color->g = ft_atoi(color_nb[1]);
	color->b = ft_atoi(color_nb[2]);
	ft_free_split(color_nb);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		ft_error(data, "invalid map\n");
	if (color->r > 255 || color->g > 255 || color->b > 255)
		ft_error(data, "invalid map\n");
}
