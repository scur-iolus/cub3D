/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:44:57 by llalba            #+#    #+#             */
/*   Updated: 2022/02/16 16:54:20 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos - data->map.width;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	move_left(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos - 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	move_right(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos + 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	move_down(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos + data->map.width;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

int	key_press(int key, void *param)
{
	t_data	*data;

	data = param;
	if (key == W)
		move_up(data);
	else if (key == A)
		move_left(data);
	else if (key == D)
		move_right(data);
	else if (key == S)
		move_down(data);
	else if (key == ESC)
		ft_end_exit(data);
	else if (key == RIGHT)
		look_right(data);
	else if (key == LEFT)
		look_left(data);
	mini_map(data);
	return (0);
}
