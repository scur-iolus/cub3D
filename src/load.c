/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:52:05 by llalba            #+#    #+#             */
/*   Updated: 2022/03/07 14:25:24 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_file(t_data *data, char *map)
{
	int		fd;
	int		ret;

	fd = open_file(data, map);
	while (get_next_line(fd, &data->line) || (data->line && *data->line))
	{
		ft_parsing(data);
		free(data->line_start);
		data->line_start = NULL;
		data->line = NULL;
	}
	if (data->line)
		free(data->line);
	data->line_start = NULL;
	data->line = NULL;
	close_file(data, fd);
	load_map(data, map);
	return (SUCCESS);
}

void	load_addr(t_data *data)
{
	data->n.img.addr = mlx_get_data_addr(data->n.img.mlx_img, \
		&data->n.img.bpp, &data->n.img.len, &data->n.img.endian);
	data->s.img.addr = mlx_get_data_addr(data->s.img.mlx_img, \
		&data->s.img.bpp, &data->s.img.len, &data->s.img.endian);
	data->e.img.addr = mlx_get_data_addr(data->e.img.mlx_img, \
		&data->e.img.bpp, &data->e.img.len, &data->e.img.endian);
	data->w.img.addr = mlx_get_data_addr(data->w.img.mlx_img, \
		&data->w.img.bpp, &data->w.img.len, &data->w.img.endian);
}

void	load_textures(t_data *data)
{
	data->n.img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->no, &data->n.w, &data->n.h);
	if (!data->n.img.mlx_img)
		ft_error(data, "mlx failed\n");
	data->s.img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->so, &data->s.w, &data->s.h);
	if (!data->s.img.mlx_img)
		ft_error(data, "mlx failed\n");
	data->e.img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->ea, &data->e.w, &data->e.h);
	if (!data->e.img.mlx_img)
		ft_error(data, "mlx failed\n");
	data->w.img.mlx_img = mlx_xpm_file_to_image(data->mlx.mlx, \
		data->we, &data->w.w, &data->w.h);
	if (!data->w.img.mlx_img)
		ft_error(data, "mlx failed\n");
	load_addr(data);
}

void	load_map(t_data *data, char *map)
{
	int	fd;

	fd = open_file(data, map);
	data->map.content = (char *)ft_calloc(data->map.width * data->map.height \
		+ 1, sizeof(char));
	if (!data->map.content)
		ft_error(data, "malloc failed\n");
	while (get_next_line(fd, &data->line) || (data->line && *data->line))
	{
		data->line_start = data->line;
		if ((data->map_start--) <= 0 && data->line[0])
			get_map_content(data);
		free(data->line_start);
		data->line_start = NULL;
		data->line = NULL;
	}
	if (data->line)
		free(data->line);
	close_file(data, fd);
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
	draw_start = (WIN_H / 2 - 1) - data->line_height / 2;
	draw_end = (WIN_H / 2 - 1) + data->line_height / 2;
	render_ray(data, i, draw_start, draw_end);
}
