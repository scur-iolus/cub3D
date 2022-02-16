/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:50:52 by llalba            #+#    #+#             */
/*   Updated: 2022/02/16 16:53:07 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_player(t_data *data)
{
	int	x_player;
	int	y_player;
	int	diam_player;
	int	i;
	int	j;

	diam_player = data->map.block_w - 4;
	x_player = (MM_W_MAX - MM_W_MIN) / 2 + MM_W_MIN;
	y_player = (MM_H_MAX - MM_H_MIN) / 2 + MM_H_MIN;
	j = y_player - diam_player / 2;
	while (j < y_player + diam_player / 2)
	{
		i = x_player - diam_player / 2;
		while (i < x_player + diam_player / 2)
		{
			if ((sqrtf(powf((float)i - (float)x_player, 2.) \
			+ powf((float)j - (float)y_player, 2.))) < (float)diam_player / 2.)
				img_pix_put(&data->mlx.img, i, j, 0x0025be69);
			i++;
		}
		j++;
	}
}

void	outline_mm(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < WIN_H)
	{
		i = 0;
		while (i < WIN_W)
		{
			if ((i > MM_W_MIN && i < MM_W_MAX && j == MM_H_MIN) \
			|| (i > MM_W_MIN && i < MM_W_MAX && j == MM_H_MAX) \
			|| (i == MM_W_MIN && j > MM_H_MIN && j < MM_H_MAX) \
			|| (i == MM_W_MAX && j > MM_H_MIN && j < MM_H_MAX))
				img_pix_put(&data->mlx.img, i, j, 0x00a3e4d7);
			i++;
		}
		j++;
	}
}

void	color_block(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map.block_w)
	{
		j = 0;
		while (j < data->map.block_h)
		{
			img_pix_put(&data->mlx.img, x + i, y + j, color);
			j++;
		}
		i++;
	}
	img_pix_put(&data->mlx.img, x, y, 0x00ec5658);
}

void	design_mm(t_data *data)
{
	int			i;
	int			j;
	char		c;

	data->map.block_w = (MM_W_MAX - MM_W_MIN) / 25;
	data->map.block_h = (MM_H_MAX - MM_H_MIN) / 17;

	j = MM_H_MIN;
	while (j < MM_H_MAX)
	{
		i = MM_W_MIN;
		while (i < MM_W_MAX)
		{
			c = pixel_to_char(data, i, j);
			if (c == '1')
				color_block(data, i, j, 0x00a3e4d7);
			else
				color_block(data, i, j, 0x00000000);
			i += data->map.block_w;
		}
		j += data->map.block_h;
	}
}

void	mini_map(t_data *data)
{
	design_mm(data);
	outline_mm(data);
	draw_player(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.img.mlx_img, 0, 0);
}
