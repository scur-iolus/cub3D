/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:49:05 by llalba            #+#    #+#             */
/*   Updated: 2022/02/21 17:56:22 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	check_hit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 100000 && !data->hit)
	{
		break ;
	}
}

// printf("🧭 pos_x = %lf, pos_y = %lf, dir_x = %lf, dir_y = %lf, plane_x = %lf, plane_y = %lf\n", data->pos_x, data->pos_y, data->dir_x, data->dir_y, data->plane_x, data->plane_y); // FIXME
void	ray_casting(t_data *data)
{
	int	i;

	i = 0;
	set_dir(data);
	set_plane(data);
	while (i < WIN_W)
	{
		data->camera_x = 2. * (double)i / (double)WIN_W - 1;
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
		set_delta(data);
		set_side_dist(data);
		check_hit(data);
		i++;
	}
}
