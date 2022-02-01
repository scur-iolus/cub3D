/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/02/01 18:25:53 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

size_t	get_coord_len(t_data *data, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str && str[i] && str[i] != ' ')
		i++;
	j = i;
	while (str[j])
	{
		if (str[j] != ' ')
			ft_error(data, "2invalid map\n");
		j++;
	}
	return (i);
}

size_t	get_color_len(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	free_data(t_data *data)
{
	// if (data->map)
	// 	free(data->map);
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

int	get_coord(t_data *data, char *coord, char **s)
{
	size_t	len;
	char	*line;

	line = data->line;
	if (!ft_cmp(coord, data->line) && !(*s))
	{
		line += 2;
		skip_spaces(&line);
		len = get_coord_len(data, line);
		*s = (char *)ft_calloc(len + 1, sizeof(char));
		if (!(*s))
			ft_error(data, "malloc failed\n");
		ft_strncpy(line, s, len);
		data->state++;
		//printf("💭 data->so : %s\n", data->so);//FIXME
		return (1);
	}
	else if (!ft_cmp(coord, line) && *s)
		ft_error(data, "invalid map1\n");
	return (0);
}

int	count_comma(char *color_str)
{
	int i;

	i = 0;
	while (*color_str && i < 4)
	{
		if (*color_str == ',')
			i++;
		color_str++;
	}
	return (i);
}

void	format_color(t_data *data, t_color *color)
{
	char	**color_nb;

	if (!(data->color_str[0]) || count_comma(data->color_str) != 2)
		ft_error(data, "3invalid map\n");
	color_nb = ft_split(data->color_str, ',');
	if (!color_nb)
		ft_error(data, "malloc failed\n");
	if (!(color_nb[0] && color_nb[1] && color_nb[2] && !color_nb[3]))
	{
		ft_free_split(color_nb);
		ft_error(data, "4invalid map\n");
	}
	color->r = ft_atoi(color_nb[0]);
	color->g = ft_atoi(color_nb[1]);
	color->b = ft_atoi(color_nb[2]);
	ft_free_split(color_nb);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		ft_error(data, "5invalid map\n");
}


int	get_colors(t_data *data, char c, t_color *color)
{
	size_t	len;
	char	*line;

	line = data->line;
	if (line[0] == c && color->not_yet)
	{
		line++;
		skip_spaces(&(line));
		len = get_color_len(line);
		data->color_str = (char *)ft_calloc(len + 1, sizeof(char));
		if (!(data->color_str))
			ft_error(data, "malloc failed\n");
		ft_strncpy(line, &data->color_str, len);
		format_color(data, color);
		data->state++;
		return (SUCCESS);
	}
	else if (line[0] == c && color->not_yet)
		ft_error(data, "6invalid map\n");
	return (SUCCESS);
}

t_bool	is_not_in_set(t_data *data)
{
	if (data->line[0] != 'F' && data->line[0] != 'C' \
		&& ft_cmp(data->line, "NO") && ft_cmp(data->line, "SO") \
		&& ft_cmp(data->line, "WE") && ft_cmp(data->line, "EA") \
		&& data->line[0] != 0)
		return (TRUE);
	return (FALSE);
}

void	get_map_size(t_data *data)
{
	char			*line;
	int				width;
	static t_bool	end = FALSE;

	line = data->line;
	if (*line == 0)
	{
		if (data->map.width != 0)
			end = TRUE;
		else
			data->map_start++;
		return ;
	}
	data->map.height++;
	width = 0;
	while (*line)
	{
		if (end == TRUE || (*line != '1' && *line != '0' && *line != ' ' \
		&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W'))
			ft_error(data, "invalid map9\n");
		width++;
		line++;
	}
	if (width > data->map.width)
		data->map.width = width;
}

void	get_map_content(t_data *data)
{
	printf("🧚%s🧚\n", data->line); // FIXME
}

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
	data->map.content = (char *)ft_calloc(data->map.width * data->map.height, \
		sizeof(char)); // MARQUE-PAGE
	while	(get_next_line(fd, &data->line))
	{
		if ((data->map_start--) <= 0 && data->line[0])
			get_map_content(data);
	}
	ret = close(fd);
	if (ret)
		ft_error(data, "close failed\n");
	printf("💭 data->f : %d %d %d\n", data->f.r, data->f.g, data->f.b);
	printf("💭 data->c : %d %d %d\n", data->c.r, data->c.g, data->c.b);
	printf("💭 data->so : %s\n", data->so);
	printf("💭 data->ea : %s\n", data->ea);
	printf("💭 data->no : %s\n", data->no);
	printf("💭 data->we : %s\n", data->we);
	printf("💭 data->map w x h : %d x %d\n", data->map.width, data->map.height);


	return (SUCCESS);
}

void	init_color(t_data *data)
{
	data->f.not_yet = TRUE;
	data->c.not_yet = TRUE;
	data->f.r = -1;
	data->f.g = -1;
	data->f.b = -1;
	data->c.r = -1;
	data->c.g = -1;
	data->c.b = -1;
}

void	init_data(t_data *data)
{
	data->map.content = NULL;
	data->map.width = 0;
	data->map.height = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->color_str = NULL;
	init_color(data);
	data->line = NULL;
	data->state = 0;
	data->map_start = 0;
	data->ready = 0;
}

int	main(int ac, char **av)
{
	t_data	data;


	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	load_map(&data, av[1]); // TODO renvoie FAIL si erreur -> free
	return (0);

}
