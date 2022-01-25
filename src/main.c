/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llalba <llalba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:26:55 by llalba            #+#    #+#             */
/*   Updated: 2022/01/25 16:19:32 by llalba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void skip_spaces(char **line)
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

int get_f(t_data *data, char **line)
{
	if (**line == 'F' && !data->f)
	{
		(*line)++;
		skip_spaces(line);
		data->f = ;
		return (SUCCESS);
	}
	else
		return (ft_error("invalid map\n"));
	return (SUCCESS);
}

int	ft_parsing(t_data *data, char *line)
{
	if (1 || "pas_encore_dans_la_map")
	{
		skip_spaces(&line);
		get_f(data, &line);
		else if (*line == 'C')
		{

		}
		else
	}
	return (0);
}

int check_map(t_data *data, char *map)
{
	int		fd;
	char	*line;

	if (map_is_valid(map))
		return (ft_error("invalid map\n"));
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_error("open failed\n"));
	while	(get_next_line(fd, &line))
	{
		printf("📌%s📌\n", line); // FIXME
		(void)ft_parsing(data, line);
	}

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
}

int	main(int ac, char **av)
{
	t_data	*data;


	if (ac != 2)
		return (ft_error("wrong number of arguments\n"));
	init_data(data);
	check_map(data, av[1]); // TODO renvoie FAIL si erreur -> free
	return (0);

}
