/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:46:50 by llalba            #+#    #+#             */
/*   Updated: 2022/03/01 22:27:54 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	update_plane(t_data *data)
{
	if (data->map.compass == 'N')
	{
		data->plane_x = VIEW_W;
		data->plane_y = 0.;
	}
	else if (data->map.compass == 'E')
	{
		data->plane_x = 0.;
		data->plane_y = -VIEW_W;
	}
	else if (data->map.compass == 'S')
	{
		data->plane_x = -VIEW_W;
		data->plane_y = 0.;
	}
	else if (data->map.compass == 'W')
	{
		data->plane_x = 0.;
		data->plane_y = VIEW_W;
	}
}

static void	update_dir(t_data *data)
{
	if (data->map.compass == 'N')
	{
		data->dir_x = 0.;
		data->dir_y = 1.;
	}
	else if (data->map.compass == 'E')
	{
		data->dir_x = 1.;
		data->dir_y = 0.;
	}
	else if (data->map.compass == 'S')
	{
		data->dir_x = 0.;
		data->dir_y = -1.;
	}
	else if (data->map.compass == 'W')
	{
		data->dir_x = -1.;
		data->dir_y = 0.;
	}
}

void	look_right(t_data *data)
{
	if (data->map.compass == 'N')
		data->map.compass = 'E';
	else if (data->map.compass == 'E')
		data->map.compass = 'S';
	else if (data->map.compass == 'S')
		data->map.compass = 'W';
	else if (data->map.compass == 'W')
		data->map.compass = 'N';
	update_dir(data);
	update_plane(data);
}

void	look_left(t_data *data)
{
	if (data->map.compass == 'N')
		data->map.compass = 'W';
	else if (data->map.compass == 'W')
		data->map.compass = 'S';
	else if (data->map.compass == 'S')
		data->map.compass = 'E';
	else if (data->map.compass == 'E')
		data->map.compass = 'N';
	update_dir(data);
	update_plane(data);
}
