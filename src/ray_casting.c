/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:49:05 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 18:00:30 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_ray_pos(t_data *data, int i)
{
	double	tmp;
	double	ray_dir;

	if (data->side_dist_x > data->side_dist_y)
		data->ray_pos = modf(data->side_dist_y * data->ray_dir_x + 0.5, &tmp);
	else
		data->ray_pos = modf(data->side_dist_x * data->ray_dir_y + 0.5, &tmp);
	if (data->ray_pos < 0.)
		data->ray_pos += 1.;
	if (data->hit == 'S' || data->hit == 'E')
		data->ray_pos = 1. - data->ray_pos;
}

static void	check_hit(t_data *data)
{
	int	i;
	int	block_num;

	i = -1;
	while (++i < 100000)
	{
		if (is_wall(data))
			break ;
		if (data->side_dist_x < data->side_dist_y)
		{
			data->map_x += data->step_x;
			block_num = (data->map.height - 1 - data->map_y) * \
			data->map.width + data->map_x;
			if (data->map.content[block_num] != '1')
				data->side_dist_x += data->delta_dist_x;
		}
		else
		{
			data->map_y += data->step_y;
			block_num = (data->map.height - 1 - data->map_y) * \
			data->map.width + data->map_x;
			if (data->map.content[block_num] != '1')
				data->side_dist_y += data->delta_dist_y;
		}
	}
}

static int	get_color_pix(t_data *data, double y)
{
	char	*p;
	t_text	*t;
	int		pix_x;
	int		pix_y;

	if (data->hit == 'N')
		t = &data->n;
	else if (data->hit == 'S')
		t = &data->s;
	else if (data->hit == 'E')
		t = &data->e;
	else if (data->hit == 'W')
		t = &data->w;
	pix_y = y * t->h;
	pix_x = data->ray_pos * t->w;
	p = t->img.addr + (pix_y * t->img.len + pix_x * (t->img.bpp / 8));
	return (*(int *)p);
}

void	render_ray(t_data *data, int i, int draw_start, int draw_end)
{
	int		j;
	double	y;

	j = -1;
	while (++j < WIN_H)
	{
		if (i >= MM_W_MIN && i <= MM_W_MAX && j >= MM_H_MIN && j <= MM_H_MAX)
			j = MM_H_MAX + 1;
		if (j > draw_start && j < draw_end)
		{
			y = (double)(j - draw_start) / (double)(draw_end - draw_start);
			img_pix_put(&data->mlx.img, i, j, get_color_pix(data, y));
		}
		else if (j <= draw_start)
		{
			img_pix_put(&data->mlx.img, i, j, *(int *) \
			(unsigned char [4]){data->c.b, data->c.g, data->c.r});
		}
		else if (j >= draw_end)
		{
			img_pix_put(&data->mlx.img, i, j, *(int *) \
			(unsigned char [4]){data->f.b, data->f.g, data->f.r});
		}
	}
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
		set_ray_pos(data, i);
		wall_builder(data, i);
		i++;
	}
}
