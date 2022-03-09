/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:44:57 by llalba            #+#    #+#             */
/*   Updated: 2022/03/09 15:54:53 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	step_forward(t_data *data)
{
	int	next_pos;

	if (data->map.compass == 'N')
		next_pos = data->map.pos - data->map.width;
	else if (data->map.compass == 'E')
		next_pos = data->map.pos + 1;
	else if (data->map.compass == 'S')
		next_pos = data->map.pos + data->map.width;
	else if (data->map.compass == 'W')
		next_pos = data->map.pos - 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	move_left(t_data *data)
{
	int	next_pos;

	if (data->map.compass == 'N')
		next_pos = data->map.pos - 1;
	else if (data->map.compass == 'E')
		next_pos = data->map.pos - data->map.width;
	else if (data->map.compass == 'S')
		next_pos = data->map.pos + 1;
	else if (data->map.compass == 'W')
		next_pos = data->map.pos + data->map.width;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	move_right(t_data *data)
{
	int	next_pos;

	if (data->map.compass == 'N')
		next_pos = data->map.pos + 1;
	else if (data->map.compass == 'E')
		next_pos = data->map.pos + data->map.width;
	else if (data->map.compass == 'S')
		next_pos = data->map.pos - 1;
	else if (data->map.compass == 'W')
		next_pos = data->map.pos - data->map.width;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	step_backwards(t_data *data)
{
	int	next_pos;

	if (data->map.compass == 'N')
		next_pos = data->map.pos + data->map.width;
	else if (data->map.compass == 'E')
		next_pos = data->map.pos - 1;
	else if (data->map.compass == 'S')
		next_pos = data->map.pos - data->map.width;
	else if (data->map.compass == 'W')
		next_pos = data->map.pos + 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

int	key_press(int k, void *param)
{
	t_data	*data;

	data = param;
	if (k == W)
		step_forward(data);
	else if (k == A)
		move_left(data);
	else if (k == D)
		move_right(data);
	else if (k == S)
		step_backwards(data);
	else if (k == ESC)
		free_n_exit(data);
	else if (k == RIGHT)
		look_right(data);
	else if (k == LEFT)
		look_left(data);
	if (k == W || k == A || k == D || k == S || k == RIGHT || k == LEFT)
	{
		ray_casting(data);
		mini_map(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
			data->mlx.img.mlx_img, 0, 0);
	}
	return (0);
}
