/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:01:10 by llalba            #+#    #+#             */
/*   Updated: 2022/02/02 12:01:29 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_data(t_data *data)
{
	if (data->map.content)
		free(data->map.content);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	// if (data->f)
	// 	free(data->f);
	// if (data->c)
	// 	free(data->c);
	if (data->color_str)
		free(data->color_str);
	if (data->line)
		free(data->line);
}

