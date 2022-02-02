/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/02/02 13:40:05 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_parsing(t_data *data)
{
	printf("🐣%s🐣\n", data->line); // FIXME
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
			ft_error(data, "7invalid map\n");
	}
	else
	{
		get_map_size(data);
		data->state++;
	}
}

int	open_file(t_data *data, char *map)
{
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error(data, "open failed\n");
	return (fd);
}

int load_map(t_data *data, char *map)
{
	int		fd;
	int		ret;

	fd = open_file(data, map);
	if (map_is_valid(map))
		ft_error(data, "8invalid map\n");
	while	(get_next_line(fd, &data->line))
		ft_parsing(data);
	ret = close(fd);
	if (ret)
		ft_error(data, "close failed\n");
	fd = open_file(data, map);
	data->map.content = (char *)ft_calloc(data->map.width * data->map.height \
		+ 1, sizeof(char)); // MARQUE-PAGE
	if (!data->map.content)
		ft_error(data, "malloc failed\n");
	while	(get_next_line(fd, &data->line))
	{
		if ((data->map_start--) <= 0 && data->line[0])
			get_map_content(data);
	}
	ret = close(fd);
	if (ret)
		ft_error(data, "close failed\n");
	// FIXME ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	printf("💭 data->f : %d %d %d\n", data->f.r, data->f.g, data->f.b);
	printf("💭 data->c : %d %d %d\n", data->c.r, data->c.g, data->c.b);
	printf("💭 data->so : %s\n", data->so);
	printf("💭 data->ea : %s\n", data->ea);
	printf("💭 data->no : %s\n", data->no);
	printf("💭 data->we : %s\n", data->we);
	printf("💭 data->map w x h : %d x %d\n", data->map.width, data->map.height);
	// int	coucou = data->map.height;
	// int koukou = 0;
	// //printf("🧱 %s\n", data->map.content);
	// while (koukou < coucou)
	// {
	// 	printf("%.*s\n", data->map.width, data->map.content + koukou * data->map.width);
	// 	koukou++;
	// }
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;


	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	load_map(&data, av[1]); // TODO renvoie FAIL si erreur -> free
	set_map(&data);
	int	coucou = data.map.height;
	int koukou = 0;
	while (koukou < coucou)
	{
		printf("%.*s\n", data.map.width, data.map.content + koukou * data.map.width);
		koukou++;
	}
	printf("%d %c\n", data.map.pos, data.map.compass);
	return (0);

}
