/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/02/16 16:15:01 by llalba           ###   ########.fr       */
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

int	load_map(t_data *data, char *map)
{
	int		fd;
	int		ret;

	if (map_is_valid(map))
		ft_error(data, "invalid map\n");
	fd = open_file(data, map);
	while (get_next_line(fd, &data->line))
		ft_parsing(data);
	close_file(data, fd);
	fd = open_file(data, map);
	data->map.content = (char *)ft_calloc(data->map.width * data->map.height \
		+ 1, sizeof(char));
	if (!data->map.content)
		ft_error(data, "malloc failed\n");
	while (get_next_line(fd, &data->line))
	{
		data->line_start = data->line;
		if ((data->map_start--) <= 0 && data->line[0])
			get_map_content(data);
	}
	close_file(data, fd);
	return (SUCCESS);
}

static void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	draw_player(t_data *data)
{
	int	x_player;
	int	y_player;
	int	diam_player;
	int	i;
	int	j;

	diam_player = data->map.block_w;
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
}

void	go_up(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos - data->map.width;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	go_left(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos - 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	go_right(t_data *data)
{
	int	next_pos;

	next_pos = data->map.pos + 1;
	if (next_pos >= 0 && next_pos < data->map.width * data->map.height \
		&& data->map.content[next_pos] == '0')
		data->map.pos = next_pos;
}

void	go_down(t_data *data)
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
		go_up(data);
	else if (key == A)
		go_left(data);
	else if (key == D)
		go_right(data);
	else if (key == S)
		go_down(data);
	else if (key == ESC)
		ft_end_exit(data);
	mini_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.img.mlx_img, 0, 0);
	return (0);
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
		&data->mlx.img.bpp, &data->mlx.img.line_len, &data->mlx.img.endian);
	// data->mlx.img = mlx_xpm_file_to_image(data->mlx.mlx, \
	// 	"./textures/no.xpm", &data->mlx.img_w, &data->mlx.img_h);
	mini_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, \
		data->mlx.img.mlx_img, 0, 0);
	mlx_hook(data->mlx.mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx.mlx_win, 17, 0L, ft_end_exit, data);
	mlx_loop(data->mlx.mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	load_map(&data, av[1]);
	set_map(&data);
	launch_mlx(&data);

	return (0);
}
