/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 18:33:52 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

size_t	ft_cut(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != ' ')
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
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
	if (data->line)
		free(data->line);
}

int	get_coord(t_data *data, char *coord, char **s)
{
	size_t	len;

	if (!ft_cmp(coord, data->line) && !(*s))
	{
		(data->line) += 2;
		skip_spaces(&(data->line));
		len = ft_cut(data->line);
		*s = (char *)ft_calloc(len, sizeof(char));
		if (!(*s))
			ft_error(data, "malloc failed\n");
		ft_strncpy(data->line, s, len);
		return (SUCCESS);
	}
	else if (!ft_cmp(coord, data->line) && *s)
		ft_error(data, "invalid map\n");
	return (SUCCESS);
}

int	get_colors(t_data *data, char c, char **s)
{
	size_t	len;

	if (data->line[0] == c && !(*s))
	{
		(data->line)++;
		skip_spaces(&(data->line));
		len = ft_cut(data->line);
		*s = (char *)ft_calloc(len, sizeof(char));
		if (!(*s))
			ft_error(data, "malloc failed\n");
		ft_strncpy(data->line, s, len);
		return (SUCCESS);
	}
	else if (data->line[0] == c && *s)
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
		// else if (*line == 'C')
		// {

		// }
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
	printf("💭 data->f : %s\n", data->f);
	printf("💭 data->c : %s\n", data->c);
	printf("💭 data->so : %s\n", data->so);
	printf("💭 data->ea : %s\n", data->ea);
	printf("💭 data->we : %s\n", data->we);
	printf("💭 data->no : %s\n", data->no);

	return (SUCCESS);
}

void	init_data(t_data *data)
{
	data->map = NULL;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->f = NULL;
	data->c = NULL;
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
