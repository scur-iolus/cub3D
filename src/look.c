/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:46:50 by llalba            #+#    #+#             */
/*   Updated: 2022/02/16 16:47:13 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	look_right(t_data *data)
{
	if (data->map.compass == 'N')
		data->map.compass = 'E';
	else if (data->map.compass == 'E')
		data->map.compass = 'S';
	else if (data->map.compass == 'S')
		data->map.compass = 'W';
	else if (data->map.compass == 'W')
		data->map.compass = 'N';
	printf("🍪   %c\n", data->map.compass);
}

void	look_left(t_data *data)
{
	if (data->map.compass == 'N')
		data->map.compass = 'W';
	else if (data->map.compass == 'W')
		data->map.compass = 'S';
	else if (data->map.compass == 'S')
		data->map.compass = 'E';
	else if (data->map.compass == 'E')
		data->map.compass = 'N';
	printf("🍪   %c\n", data->map.compass);
}
