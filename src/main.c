/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/01/31 18:02:52 by llalba           ###   ########.fr       */
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
			ft_error(data, "invalid map\n");
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
	if (data->map)
		free(data->map);
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
		return (SUCCESS);
	}
	else if (!ft_cmp(coord, line) && *s)
		ft_error(data, "invalid map\n");
	return (SUCCESS);
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
		ft_error(data, "invalid map\n");
	color_nb = ft_split(data->color_str, ',');
	if (!color_nb)
		ft_error(data, "malloc failed\n");
	if (!(color_nb[0] && color_nb[1] && color_nb[2] && !color_nb[3]))
	{
		ft_free_split(color_nb);
		ft_error(data, "invalid map\n");
	}
	color->r = ft_atoi(color_nb[0]);
	color->g = ft_atoi(color_nb[1]);
	color->b = ft_atoi(color_nb[2]);
	ft_free_split(color_nb);
	if (color->r == -1 || color->g == -1 || color->b == -1)
		ft_error(data, "invalid map\n");
	printf("%d💃\n%d💃\n%d💃\n", color->r, color->g, color->b);
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
		return (SUCCESS);
	}
	else if (line[0] == c && color->not_yet)
		ft_error(data, "invalid map\n");
	return (SUCCESS);
}

int	ft_parsing(t_data *data)
{
	if (1 || "pas_encore_dans_la_map")
	{
		skip_spaces(&(data->line));
		if (get_colors(data, 'F', &data->f))
			return (SUCCESS);
		if (get_colors(data, 'C', &data->c))
			return (SUCCESS);
		if (get_coord(data, "SO", &data->so))
			return (SUCCESS);
		if (get_coord(data, "EA", &data->ea))
			return (SUCCESS);
		if (get_coord(data, "WE", &data->we))
			return (SUCCESS);
		if (get_coord(data, "NO", &data->no))
			return (SUCCESS);
	}
	return (0);
}

int check_map(t_data *data, char *map)
{
	int		fd;

	if (map_is_valid(map))
		ft_error(data, "invalid map\n");
	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error(data, "open failed\n");
	while	(get_next_line(fd, &data->line))
	{
		printf("📌%s📌\n", data->line); // FIXME
		(void)ft_parsing(data);
	}
	// printf("💭 data->f : %s\n", data->f);
	// printf("💭 data->c : %s\n", data->c);
	// printf("💭 data->so : %s\n", data->so);
	// printf("💭 data->ea : %s\n", data->ea);
	// printf("💭 data->we : %s\n", data->we);
	// printf("💭 data->no : %s\n", data->no);

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
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->color_str = NULL;
	init_color(data);
	data->line = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;


	init_data(&data);
	if (ac != 2)
		ft_error(&data, "wrong number of arguments\n");
	check_map(&data, av[1]); // TODO renvoie FAIL si erreur -> free
	return (0);

}
