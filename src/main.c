/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/02/14 15:12:34 by llalba           ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_data	data;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*relative_path = "./test.xpm";
	int		img_width;
	int		img_height;

	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	load_map(&data, av[1]);
	set_map(&data);
	// FIXME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	printf("EA %s\n", data.ea);
	printf("NO %s\n", data.no);
	printf("SO %s\n", data.so);
	printf("WE %s\n", data.we);
	printf("C %d,%d,%d\n", data.c.r, data.c.g, data.c.b);
	printf("F %d,%d,%d\n", data.f.r, data.f.g, data.f.b);
	// printf("w x h : %d x %d\n", data->map.width, data->map.height);
	int	coucou = data.map.height;
	int koukou = 0;
	while (koukou < coucou)
	{
		printf("%.*s\n", data.map.width, data.map.content + koukou * data.map.width);
		koukou++;
	}
	// printf("%d %c\n", data.map.pos, data.map.compass);
	// FIXME
	// mlx = mlx_init();
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	// img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	// mlx_put_image_to_window(mlx, mlx_win, img, 200, 200);
	// mlx_loop(mlx);
	return (0);
}
