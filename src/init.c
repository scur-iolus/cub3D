/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:58:24 by llalba            #+#    #+#             */
/*   Updated: 2022/02/03 14:24:40 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_color(t_data *data)
{
	data->f.not_yet = TRUE;
	data->c.not_yet = TRUE;
	data->f.r = -1;
	data->f.g = -1;
	data->f.b = -1;
	data->c.r = -1;
	data->c.g = -1;
	data->c.b = -1;
}

void	init_data(t_data *data)
{
	data->map.content = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.pos = 0;
	data->map.compass = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->color_str = NULL;
	init_color(data);
	data->line = NULL;
	data->line_start = NULL;
	data->state = 0;
	data->map_start = 0;
	data->ready = 0;
}
