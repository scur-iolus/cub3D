/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:58:24 by llalba            #+#    #+#             */
/*   Updated: 2022/02/24 14:16:39 by llalba           ###   ########.fr       */
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

static void	mlx_init_struct(t_data *data)
{
	data->mlx.mlx = NULL;
	data->mlx.mlx_win = NULL;
	data->mlx.img_h = 0;
	data->mlx.img_w = 0;
	data->mlx.img.mlx_img = NULL;
	data->mlx.img.addr = NULL;
	data->mlx.img.bpp = 0;
	data->mlx.img.line_len = 0;
	data->mlx.img.endian = 0;
}

void	init_vectors(t_data *data)
{
	data->pos_x = 0.;
	data->pos_y = 0.;
	data->dir_x = 0.;
	data->dir_y = 0.;
	data->plane_x = 0.;
	data->plane_y = 0.;
	data->camera_x = 0.;
	data->ray_dir_x = 0.;
	data->ray_dir_y = 0.;
	data->side_dist_x = 0.;
	data->side_dist_y = 0.;
	data->delta_dist_x = 0.;
	data->delta_dist_y = 0.;
	data->line_height = 0;
	data->step_x = 0;
	data->step_y = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->hit = 0;
}

void	init_data(t_data *data)
{
	data->map.content = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->map.pos = 0;
	data->map.block_w = 0;
	data->map.block_h = 0;
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
	init_vectors(data);
	mlx_init_struct(data);
}
