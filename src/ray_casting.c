/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:49:05 by llalba            #+#    #+#             */
/*   Updated: 2022/02/24 17:23:01 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_bool	is_wall(t_data *data)
{
	int	block_num;

	block_num = (data->map.height - 1 - data->pos_y - data->map_y) * \
		data->map.width + data->map_x + data->pos_x;
	if (data->map.content[block_num] != '1')
		return (FALSE);
	if (data->side_dist_x < data->side_dist_y)
	{
		data->hit = 'S';
		if (data->step_y > 0)
			data->hit = 'N';
	}
	else
	{
		data->hit = 'W';
		if (data->step_x > 0)
			data->hit = 'E';
	}
	return (TRUE);
}

static void	check_hit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 100000)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
		}
		if (is_wall(data))
			break ;
	}
}

static void	render_ray(t_data *data, int i, int draw_start, int draw_end)
{
	int	j;

	j = -1;
	while (++j < WIN_H)
	{
		if (i >= MM_W_MIN && i <= MM_W_MAX && j >= MM_H_MIN && j <= MM_H_MAX)
			j = MM_H_MAX + 1;
		if (j > draw_start && j < draw_end && \
			(data->hit == 'N' || data->hit == 'S'))
			img_pix_put(&data->mlx.img, i, j, 0x00ec5658);
		else if (j > draw_start && j < draw_end && \
			(data->hit == 'E' || data->hit == 'W'))
			img_pix_put(&data->mlx.img, i, j, 0x00f1888a);
		else
			img_pix_put(&data->mlx.img, i, j, 0x00000000);
	}
}

void	wall_builder(t_data *data, int i)
{
	int		draw_start;
	int		draw_end;
	double	wall_dist;

	if (data->hit == 'E' || data->hit == 'W')
		wall_dist = (data->side_dist_x - data->delta_dist_x);
	else
		wall_dist = (data->side_dist_y - data->delta_dist_y);

	if (wall_dist == 0.)
		return ; // ft_error(data, "something went wrong!\n");
	data->line_height = (WIN_H / wall_dist);
	draw_start = fmax(0, WIN_H / 2 - data->line_height / 2);
	draw_end = fmin(WIN_H, WIN_H / 2 + data->line_height / 2);
	render_ray(data, i, draw_start, draw_end);
}

void	ray_casting(t_data *data)
{
	int	i;

	i = 0;
	set_pos_xy(data);
	set_dir(data);
	set_plane(data);
	while (i < WIN_W)
	{
		data->hit = 0;
		data->camera_x = 2. * (double)i / (double)WIN_W - 1;
		data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
		data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
		set_delta(data);
		set_side_dist(data);
		check_hit(data);
		wall_builder(data, i);
		i++;
	}
}
