/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:44:57 by llalba            #+#    #+#             */
/*   Updated: 2022/02/24 16:34:57 by llalba           ###   ########.fr       */
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

int	key_press(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == W)
		step_forward(data);
	else if (key == A)
		move_left(data);
	else if (key == D)
		move_right(data);
	else if (key == S)
		step_backwards(data);
	else if (key == ESC)
		free_n_exit(data);
	else if (key == RIGHT)
		look_right(data);
	else if (key == LEFT)
		look_left(data);
	ray_casting(data);
	mini_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.img.mlx_img, 0, 0);
	return (0);
}
