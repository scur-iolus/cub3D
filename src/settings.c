/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:52:35 by llalba            #+#    #+#             */
/*   Updated: 2022/02/24 12:03:33 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_dir(t_data *data)
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
	else
	{
		data->dir_x = -1.;
		data->dir_y = 0.;
	}
}

void	set_plane(t_data *data)
{
	if (data->map.compass == 'N')
	{
		data->plane_x = 0.66;
		data->plane_y = 0.;
	}
	else if (data->map.compass == 'E')
	{
		data->plane_x = 0.;
		data->plane_y = -0.66;
	}
	else if (data->map.compass == 'S')
	{
		data->plane_x = -0.66;
		data->plane_y = 0.;
	}
	else
	{
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
}

void	set_delta(t_data *data)
{
	if (data->ray_dir_x != 0.0)
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
	else
		data->delta_dist_x = 1e30;
	if (data->ray_dir_y != 0.0)
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
	else
		data->delta_dist_y = 1e30;
}

void	set_side_dist(t_data *data)
{
	data->map_x = data->pos_x;
	data->map_y = data->pos_y;
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->pos_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1. - data->pos_x) \
			* data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->pos_x - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1. - data->pos_y) \
			* data->delta_dist_y;
	}
}

void	set_pos_xy(t_data *data)
{
	data->pos_x = data->map.pos % data->map.width;
	data->pos_y = data->map.pos - data->pos_x;
	data->pos_y = data->map.height - 1 - data->pos_y / data->map.width;
}
