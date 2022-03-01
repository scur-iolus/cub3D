/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:49:05 by llalba            #+#    #+#             */
/*   Updated: 2022/03/01 23:10:31 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static t_bool	is_wall(t_data *data)
{
	int		block_num;
	double	tmp;

	block_num = (data->map.height - 1 - data->map_y) * \
		data->map.width + data->map_x;
	if (data->map.content[block_num] != '1')
		return (FALSE);
	if (data->side_dist_x > data->side_dist_y)
	{
		data->hit = 'S';
		if (data->step_y > 0)
			data->hit = 'N';
		data->ray_pos = modf(data->side_dist_y * data->ray_dir_x \
			/ data->dir_y + 0.5, &tmp);
	}
	else
	{
		data->hit = 'W';
		if (data->step_x > 0)
			data->hit = 'E';
		data->ray_pos = modf(data->side_dist_x * data->ray_dir_y \
			/ data->dir_x + 0.5, &tmp);
	}
	return (TRUE);
}

static void	check_hit(t_data *data, int n)
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

static void	render_ray(t_data *data, int i, int draw_start, int draw_end)
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
			y = ((double)j - (double)draw_start) / (double)draw_end;
			img_pix_put(&data->mlx.img, i, j, get_color_pix(data, y));
		}
		else if (j <= draw_start)
		{
			img_pix_put(&data->mlx.img, i, j, *(int *) \
			(unsigned char [4]){data->f.b, data->f.g, data->f.r});
		}
		else if (j >= draw_end)
		{
			img_pix_put(&data->mlx.img, i, j, *(int *) \
			(unsigned char [4]){data->c.b, data->c.g, data->c.r});
		}
	}
}

void	wall_builder(t_data *data, int i)
{
	int		draw_start;
	int		draw_end;
	double	wall_dist;

	if (data->hit == 'N' || data->hit == 'S')
		wall_dist = data->side_dist_y;
	else
		wall_dist = data->side_dist_x;
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
		check_hit(data, i);
		if (data->ray_pos < 0.)
			data->ray_pos = 1. + data->ray_pos;
		if (i == 0)
			printf("🎄 %lf %lf %lf -> %lf\n", data->side_dist_y, data->ray_dir_x, data->dir_y, data->ray_pos);
		if (i == WIN_W / 2 - 1)
			printf("🎄 %lf %lf %lf -> %lf\n", data->side_dist_y, data->ray_dir_x, data->dir_y, data->ray_pos);
		if (i == WIN_W - 1)
			printf("🎄 %lf %lf %lf -> %lf\n\n", data->side_dist_y, data->ray_dir_x, data->dir_y, data->ray_pos);
		wall_builder(data, i);
		i++;
	}
}
