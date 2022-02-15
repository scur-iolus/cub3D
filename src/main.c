/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/02/15 15:56:00 by llalba           ###   ########.fr       */
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
	x_player = (MM_W_MAX - MM_W_MIN) / 2 + MM_W_MIN;
	y_player = (MM_H_MAX - MM_H_MIN) / 2 + MM_H_MIN;
	diff_x = (x - x_player) / data->map.block_w;
	if (diff_x < 0 && diff_x < -(pp % data->map.width))
		return ('0');
	if (diff_x > 0 && diff_x + (pp % data->map.width) >= data->map.width)
		return ('0');
	diff_y = (y - y_player) / data->map.block_h * data->map.width;
	if (diff_x == 0 && diff_y == 0)
		return ('P');
	if (pp + diff_x + diff_y < 0 || \
	pp + diff_x + diff_y >= data->map.width * data->map.height)
		return ('0');
	return (data->map.content[pp + diff_x + diff_y]);
}

void	design_mm(t_data *data)
{ 
	int			i;
	int			j;
	char		c;

	data->map.block_w = (MM_W_MAX - MM_W_MIN) / 25;
	data->map.block_h = (MM_H_MAX - MM_H_MIN) / 17;
	j = MM_H_MIN + 1;
	printf("🐹 %d %d \n", data->map.block_w, data->map.block_h); //FIXME
	while (j < MM_H_MAX - 1)
	{
		i = MM_W_MIN + 1;
		while (i < MM_W_MAX - 1)
		{
			// if ((i - MM_W_MIN) % data->map.block_w == 0 \
			// && (j - MM_H_MIN) % data->map.block_h == 0)
			c = pixel_to_char(data, i, j);
			if (c == 'P')
				img_pix_put(&data->mlx.img, i, j, 0x00ff5733);
			else if (c == '1')
				img_pix_put(&data->mlx.img, i, j, 0x00a3e4d7); 
			i++;
		}
		j++;
	}
}

void	mini_map(t_data *data)
{
	outline_mm(data);
	design_mm(data);
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
