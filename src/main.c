/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/03/02 18:12:19 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_parsing(t_data *data)
{
	data->line_start = data->line;
	if (data->state < 6)
	{
		data->map_start++;
		skip_spaces(&(data->line));
		if (get_colors(data, 'F', &data->f) || get_colors(data, 'C', &data->c))
			return ;
		if (get_coord(data, "SO", &data->so) || \
			get_coord(data, "EA", &data->ea) || \
			get_coord(data, "WE", &data->we) || \
			get_coord(data, "NO", &data->no))
			return ;
		if (is_not_in_set(data))
			ft_error(data, "invalid map\n");
	}
	else
	{
		get_map_size(data);
		data->state++;
	}
}

t_bool	is_wall(t_data *data)
{
	int		block_num;

	block_num = (data->map.height - 1 - data->map_y) * \
		data->map.width + data->map_x;
	if (data->map.content[block_num] != '1')
		return (FALSE);
	if (data->side_dist_x > data->side_dist_y)
	{
		data->hit = 'S';
		if (data->step_y > 0)
			data->hit = 'N';
	}
	else
	{
		data->hit = 'W';
		if (data->step_x > 0)
			data->hit = 'E';
	}
	return (TRUE);
}

char	pixel_to_char(t_data *data, int x, int y)
{
	int	x_player;
	int	y_player;
	int	diff_x;
	int	diff_y;
	int	pp;

	pp = data->map.pos;
	x += data->map.block_w / 2;
	y += data->map.block_h / 2;
	x_player = (MM_W_MAX - MM_W_MIN) / 2 + MM_W_MIN;
	y_player = (MM_H_MAX - MM_H_MIN) / 2 + MM_H_MIN;
	diff_x = (x - x_player) / data->map.block_w;
	if (diff_x < 0 && diff_x < -(pp % data->map.width))
		return ('0');
	if (diff_x > 0 && diff_x + (pp % data->map.width) >= data->map.width)
		return ('0');
	diff_y = (y - y_player) / data->map.block_h * data->map.width;
	if (pp + diff_x + diff_y < 0 || \
	pp + diff_x + diff_y >= data->map.width * data->map.height)
		return ('0');
	return (data->map.content[pp + diff_x + diff_y]);
}

void	launch_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		ft_error(data, "could not init MLX\n");
	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!data->mlx.mlx_win)
		ft_error(data, "could not create a new window\n");
	data->mlx.img.mlx_img = mlx_new_image(data->mlx.mlx, WIN_W, WIN_H);
	if (!data->mlx.img.mlx_img)
		ft_error(data, "could not create a new image\n");
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.mlx_img, \
		&data->mlx.img.bpp, &data->mlx.img.len, &data->mlx.img.endian);
	load_textures(data);
	ray_casting(data);
	mini_map(data);
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.mlx_win, 17, 0L, free_n_exit, data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.img.mlx_img, 0, 0);
	mlx_loop(data->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	if (map_is_valid(av[1]))
		ft_error(&data, "invalid map\n");
	load_file(&data, av[1]);
	set_map(&data);
	launch_mlx(&data);
	return (0);
}
