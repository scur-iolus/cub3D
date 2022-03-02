/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 12:01:10 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 17:45:02 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	free_n_exit(void *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	free_texture(t_data *data)
{
	if (data->n.img.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->n.img.mlx_img);
	if (data->s.img.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->s.img.mlx_img);
	if (data->e.img.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->e.img.mlx_img);
	if (data->w.img.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->w.img.mlx_img);
}

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
	if (data->color_str)
		free(data->color_str);
	if (data->line_start)
		free(data->line_start);
	free_texture(data);
	if (data->mlx.img.mlx_img)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img.mlx_img);
	if (data->mlx.mlx_win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.mlx_win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
}

void	ft_free_split(char **ptr)
{
	int	i;

	i = 0;
	if (ptr == NULL)
		return ;
	while (ptr[i])
	{
		free (ptr[i]);
		i++;
	}
	free(ptr);
}
